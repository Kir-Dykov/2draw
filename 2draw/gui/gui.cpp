#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include "GL/glut.h"

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

int Width = 720, Height = 720;

int x_start = Width / 2, y_start = Height / 2, x_shifted = 0, y_shifted = 0;

extern vector<CommandLine> commands;
bool editing_a_command;
bool moving_a_point;
CommandLine* command_to_edit;
bool moving_screen;
bool zooming_screen;

string prev_command = "";
UndoStack<Action> undo_stack;

void glNormalView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Width, 0, Height, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glDisplacedView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x_shifted, Width + x_shifted, y_shifted, Height + y_shifted, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void push_action() {
	if (prev_command != command_to_edit->command) {
		undo_stack.push_back(Action(command_to_edit->index, prev_command, command_to_edit->command));
	}
}

void Display(void) {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	

	glDisplacedView();

	//drawing objects
	for (size_t i = commands.size()-1; i < commands.size(); i--) {
		if (commands[i].obj != nullptr) {
			commands[i].obj->Draw();
		};
	}

	glNormalView();

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
	//cout << (int)key;

	if (key == 26) { //ctrl+Z
		if (editing_a_command && command_to_edit->command != prev_command) {
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

void SpecialInput(int key, int, int) {
	//cout << key << endl;
	if (editing_a_command) {
		if (key == GLUT_KEY_UP) {
			command_to_edit->Compile();
			push_action();
			command_to_edit = &commands[((command_to_edit->index) - 1 + commands.size()) % commands.size()];
			command_to_edit->b = 192;
			prev_command = command_to_edit->command;
		} else if (key == GLUT_KEY_DOWN) {
			command_to_edit->Compile();
			push_action();
			command_to_edit = &commands[((command_to_edit->index) + 1) % commands.size()];
			command_to_edit->b = 192;
			prev_command = command_to_edit->command;
		}
	}
	else {
		if (key == GLUT_KEY_UP) {
			command_to_edit = &commands[commands.size()-1];
			command_to_edit->b = 192;
			prev_command = command_to_edit->command;
			editing_a_command = true;
		}
		else if (key == GLUT_KEY_DOWN) {
			command_to_edit = &commands[0];
			command_to_edit->b = 192;
			prev_command = command_to_edit->command;
			editing_a_command = true;
		}
	}

	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y)
{
	y = Height - y;
	cout << button << " " << state << " " << x << " " << y << endl;

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

					goto break_all;
				}
			}
			
			if (editing_a_command) {
				command_to_edit->Compile();
				push_action();
				editing_a_command = false;
			}


			for (size_t i = 0; i < commands.size(); i++) {
				if (commands[i].type == "point" && distance((*(Point*)commands[i].obj), Point(x + x_shifted, y + y_shifted)) < 4)
				{
					moving_a_point = true;
					command_to_edit = &(commands[i]);
					prev_command = command_to_edit->command;
					goto break_all;
				}
			}

			/*gluOrtho2D shenanigans*/
			if (!editing_a_command && !moving_a_point && !moving_screen) {
				moving_screen = true;
				x_start = x + x_shifted;
				y_start = y + y_shifted;
			}

			break_all:
			glutPostRedisplay();
		}
		else {
			if (moving_a_point) {
				push_action();
				moving_a_point = false;
				command_to_edit = nullptr;
			}
			if (moving_screen) moving_screen = false;
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON) {
		
		if (state == GLUT_DOWN) {
			
			for (size_t i = 0; i < commands.size(); i++) {
				bool in_ = 0;
				if (commands[i].type == "triangle")
					in_ = ((Triangle*)(commands[i].obj))->is_in(Point(x + x_shifted, y + y_shifted));
				else if (commands[i].type == "circle")
					in_ = ((Circle*)(commands[i].obj))->is_in(Point(x + x_shifted, y + y_shifted));
				else if (commands[i].type == "polygon")
					in_ = ((Polygon*)(commands[i].obj))->is_in(Point(x + x_shifted, y + y_shifted));

				if (in_) {
					commands[i].filled = !(commands[i].filled);
					commands[i].obj->filled = commands[i].filled;
					glutPostRedisplay();
				}

			}
		}
	}
	if (button == 3) {
		cout << "YEAS" << endl;
		x_shifted /= 1.1; y_shifted /= 1.1;
		Width /= 1.1; Height /= 1.1;
		glutPostRedisplay();
	}
	if (button == 4) {
		x_shifted *= 1.1; y_shifted *= 1.1;
		Width *= 1.1; Height *= 1.1;
		glutPostRedisplay();
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
		if (command_to_edit->symbol != "")
			command_to_edit->command = command_to_edit->symbol + " " + "point" + " " + to_string(x + x_shifted) + " " + to_string(y + y_shifted);
		else
			command_to_edit->command = static_cast<string>("point ") + to_string(x + x_shifted) + " " + to_string(y + y_shifted);
		
		command_to_edit->Compile();
		glutPostRedisplay();
	}
	if (moving_screen) {

		x_shifted = x_start - x; y_shifted = y_start - y;

		//glViewport(0, 0, Width, Height);
		

		//cout << endl << x_shifted << "   " << y_shifted;
		glutPostRedisplay();
		
	}
}


void PassiveMotionFunc(int x, int y) {
	//cout << "Passive motion " << x << " " << y << endl;
	//glutPostRedisplay();
}


/* the main */
int gui_main() {

	//creating 20 command lines to work with
	commands.push_back(CommandLine(10, 10));
	for (size_t i = 0; i < 19; i++) {
		commands.push_back(CommandLine(10, commands[i].y + 30));
	}

	int argc;
	char* c = new char;
	*c = '\0';

	glutInit(&argc, &c);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("2draw");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	//glutTimerFunc(DELAY, Loop, 1);
	glutMouseFunc(MouseFunc);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialInput);
	glutMotionFunc(MotionFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);

	glutMainLoop();

	return 0;
}
