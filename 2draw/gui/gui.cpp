#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include "glut.h"

#include "gui.h"
#include "../point.h"
#include "../circle.h"
#include "../triangle.h"
#include "../polygon.h"

#include "command_line.h"
#include "undo_stack.h"
#include "action.h"

using namespace std;

//const int DELAY = 20;

GLint Width = 720, Height = 720;

extern vector<CommandLine> commands;
bool editing_a_command;
bool moving_a_point;
CommandLine* command_to_edit;
CommandLine* point_to_move;

string prev_command = "";
UndoStack<Action> undo_stack;

void push_action() {
	if (prev_command != command_to_edit->command) {
		undo_stack.push_back(Action(command_to_edit->index, prev_command, command_to_edit->command));
	}
	
}

void Display(void) {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//drawing objects
	for (size_t i = 0; i < commands.size(); i++) {
		if (commands[i].obj != nullptr) {
			commands[i].obj->Draw();

			cout << endl << endl;
			cout << commands[i].symbol << " (" << commands[i].index << ") is drawn" << endl;

			cout << "dependencies:" << endl;
			cout << "\t";
			for (size_t j = 0; j < commands[i].dependencies.size(); j++){
				cout << commands[i].dependencies[j] << " ";
			}
			cout << endl;
			cout << "dependent_from_this:" << endl;
			cout << "\t";
			for (size_t j = 0; j < commands[i].dependent_from_this.size(); j++) {
				cout << commands[i].dependent_from_this[j] << " ";
			}
			cout << endl;
		};
	}

	//drawing command lines
	for (size_t i = 0; i < commands.size(); i++) {
		commands[i].Draw();
	}

	glFinish();
}

/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h) {
	Width = w;
	Height = h;
	/* устанавливаем размеры области отображения */
	glViewport(0, 0, w, h);
	/* ортографическая проекция */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int, int) {
	cout << (int)key;
	if (key == 26) { //ctrl+Z
		if (editing_a_command) {
			command_to_edit->command = prev_command;
		}
		else {
			Action a = undo_stack.undo();
			commands[a.index].command = a.prev_command;
			commands[a.index].Compile();
		}
		
		glutPostRedisplay();
	}
	else if (key == 25) { //ctrl+Y
		Action a = undo_stack.redo();
		commands[a.index].command = a.new_command;
		commands[a.index].Compile();
		glutPostRedisplay();
	} else if (editing_a_command) {
		
		//backspace key
		if (key == 8 && command_to_edit->command.length() > 0) {
			command_to_edit->command.resize(command_to_edit->command.length() - 1);
		}
		//enter key
		else if (key == 13) { 
			command_to_edit->Compile();
			push_action();
			command_to_edit = &commands[((command_to_edit->index)+1)%commands.size()];
			command_to_edit->b = 192;
			prev_command = command_to_edit->command;
		}
		//typing in symbols
		else {
			command_to_edit->command.append(1, key);
		}
		glutPostRedisplay();
	}
}

void MouseFunc(int button, int state, int x, int y)
{
	y = Height - y;
	//cout << button << " " << state << " " << x << " " << y << endl;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) {

			//checks if clicked on some command line
			//makes it editable by typing on keyboard
			for (size_t i = 0; i < commands.size(); i++) {
				if (commands[i].is_in(x, y)) {
					editing_a_command = true;
					if (command_to_edit != nullptr) {
						command_to_edit->Compile();
						push_action();
					}

					
					command_to_edit = &(commands[i]);
					command_to_edit->b = 192;
					prev_command = command_to_edit->command;
					cout << "editing a command!" << endl;
					goto break_all; //no need to check wether user clicked on some object before exiting
				}
			}
			
			if (editing_a_command) {
				command_to_edit->Compile();
				push_action();
				editing_a_command = false;
			}
			

			for (size_t i = 0; i < commands.size(); i++) {
				if (commands[i].type == "point" && distance((*(Point*)commands[i].obj), Point(x, y)) < 4)
				{
					moving_a_point = true;
					point_to_move = &(commands[i]);
					goto break_all;
				}
			}

			break_all:
			glutPostRedisplay();
		}
		else {
			if (moving_a_point) {
				moving_a_point = false;
				point_to_move = nullptr;
			}
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON) {
		
		if (state == GLUT_DOWN) {
			
			for (size_t i = 0; i < commands.size(); i++) {
				bool in_ = 0;
				if (commands[i].type == "triangle")
					in_ = ((Triangle*)(commands[i].obj))->is_in(Point(x, y));
				else if (commands[i].type == "circle")
					in_ = ((Circle*)(commands[i].obj))->is_in(Point(x, y));
				else if (commands[i].type == "polygon")
					in_ = ((Polygon*)(commands[i].obj))->is_in(Point(x, y));

				if (in_) {
					commands[i].filled = !(commands[i].filled);
					commands[i].obj->filled = commands[i].filled;
					glutPostRedisplay();
				}

			}
		}
	}

	
}


/*
void Loop(int) {
	glutPostRedisplay();
	glutTimerFunc(DELAY, Loop, 1);
}
*/

void MotionFunc(int x, int y) {
	y = Height - y;
	if (moving_a_point) {
		if (point_to_move->symbol != "")
			point_to_move->command = point_to_move->symbol + " " + "point" + " " + to_string(x) + " " + to_string(y);
		else
			point_to_move->command = static_cast<string>("point ") + to_string(x) + " " + to_string(y);
		
		point_to_move->Compile();
		glutPostRedisplay();
	}
}


void PassiveMotionFunc(int x, int y) {
	//cout << "Passive motion " << x << " " << y << endl;
	//glutPostRedisplay();
}


/* the main */
int gui_main() {
	
	undo_stack.push_back(Action()); //add empty action

	//creating 20 command lines to work with
	commands.push_back(CommandLine(10, 10));
	for (size_t i = 0; i < 19; i++) {
		commands.push_back(CommandLine(10, commands[i].y + 30));
	}

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("2draw");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	//glutTimerFunc(DELAY, Loop, 1);
	glutMouseFunc(MouseFunc);
	glutKeyboardFunc(Keyboard);

	glutMotionFunc(MotionFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);

	glutMainLoop();

	return 0;
}
