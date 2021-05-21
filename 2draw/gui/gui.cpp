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

int Width = 1080, Height = 720;

int x_start = Width / 2, y_start = Height / 2, x_shifted = -Width / 2, y_shifted = -Height / 2;
double scale_factor = 1;

extern vector<CommandLine> commands;
bool editing_a_command;
bool moving_a_point;
CommandLine* command_to_edit;
bool moving_screen;
bool zooming_screen;

string prev_command = "";
UndoStack<Action> undo_stack;

Line x_axis(Point(0, 0), Point(1000, 0));
Line y_axis(Point(0, 0), Point(0, 1000));

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
	glOrtho(x_shifted*scale_factor, (Width + x_shifted)* scale_factor, y_shifted * scale_factor, (Height + y_shifted) * scale_factor, -1.0, 1.0);
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
	x_axis.Draw();
	y_axis.Draw();

	// the order is reversed so that objects that are written later are drawn on the top
	for (size_t i = commands.size()-1; i < commands.size(); i--) {
		if (commands[i].obj != nullptr) {
			commands[i].obj->Draw();
			/*cout << commands[i].symbol << endl;
			cout << "dependencies:\n";
			for (size_t j = 0; j < commands[i].dependencies.size(); j++) {
				cout << commands[commands[i].dependencies[j]].symbol << " ";
			}
			cout << endl;
			cout << "dependent_from_this:\n";
			for (size_t j = 0; j < commands[i].dependent_from_this.size(); j++) {
				cout << commands[commands[i].dependent_from_this[j]].symbol << " ";
			}
			cout << endl << endl << endl;*/ //debug output
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
	if (key == 1) { //F1
		for (size_t i = 0; i < commands.size(); i++) {
			commands[i].command = "";
		}
		commands[0].command = "p1 point";
		commands[1].command = "p2 point";
		commands[2].command = "p3 point";
		commands[3].command = "t1 triangle p1 p2 p3";
		commands[4].command = "c1 incircle t1";
		commands[5].command = "c2 circumcircle t1";
		commands[6].command = "p4 point";
		commands[7].command = "p5 point";
		commands[8].command = "l1 line p4 p5";
		commands[9].command = "p6 point";
		commands[10].command = "p7 point";
		commands[11].command = "l2 line p6 p7";
		commands[12].command = "p_int intersection l1 l2";
		commands[13].command = "pg convex_hull p1 p2 p3 p4 p5 p6 p7 p_int";
		for (size_t i = 0; i < commands.size(); i++) {
			commands[i].Compile();
		}
	}
	else if (key == 2) { //F2
		for (size_t i = 0; i < commands.size(); i++) {
			commands[i].command = "";
		}
		commands[0].command = "p1 point";
		commands[1].command = "p2 point";
		commands[2].command = "p3 point";
		commands[3].command = "t1 triangle p1 p2 p3";
		commands[4].command = "c1 incircle t1";
		commands[5].command = "c2 circumcircle t1";
		commands[6].command = "c3 circle p1 p2";
		commands[7].command = "c4 circle p2 20";
		commands[8].command = "c5 circle 0 0 40";
		commands[9].command = "l1 line p2 p3";
		commands[10].command = "l2 line p3 p1";
		commands[11].command = "p4 intersection l1 l2";
		commands[12].command = "p5 center c2";
		commands[13].command = "p6 incenter t1";
		commands[14].command = "p7 centroid t1";
		commands[15].command = "p8 orthocenter t1";
		commands[16].command = "c6 excircle t1 p1";
		commands[17].command = "l3 altitude t1 p2";
		commands[18].command = "l4 midline t1 p3";
		commands[19].command = "l5 perpbis t1 p1";
		commands[20].command = "l6 bisectrix t1 p2";
		commands[21].command = "pg1 polygon p1 p2 p3 p4 p5 p6 p7";
		commands[22].command = "pg2 convex_hull p1 p2 p3 p4 p5 p6 p7";
		commands[23].command = "l7 parallel l1 p4";
		commands[24].command = "l8 perpendicular l2 p4";
		for (size_t i = 0; i < commands.size(); i++) {
			commands[i].Compile();
		}
	} else if (key == 5) { //F5
		for (size_t i = 0; i < commands.size(); i++) {
			commands[i].command = "";
			commands[i].Compile();
		}
	}
	else if (editing_a_command) {
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

					goto break_all;
				}
			}
			
			if (editing_a_command) {
				command_to_edit->Compile();
				push_action();
				editing_a_command = false;
			}


			for (size_t i = 0; i < commands.size(); i++) {
				if (commands[i].type == "point" && commands[i].dependencies.size() == 0 && distance((*(Point*)commands[i].obj), Point((x + x_shifted)*scale_factor, (y + y_shifted) * scale_factor)) < 4) {
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
					in_ = ((Triangle*)(commands[i].obj))->is_in(Point((x + x_shifted) * scale_factor, (y + y_shifted) * scale_factor));
				else if (commands[i].type == "circle")
					in_ = ((Circle*)(commands[i].obj))->is_in(Point((x + x_shifted) * scale_factor, (y + y_shifted) * scale_factor));
				else if (commands[i].type == "polygon")
					in_ = ((Polygon*)(commands[i].obj))->is_in(Point((x + x_shifted) * scale_factor, (y + y_shifted) * scale_factor));

				if (in_) {
					commands[i].filled = !(commands[i].filled);
					commands[i].obj->filled = commands[i].filled;
					glutPostRedisplay();
				}

			}
		}
	}
	if (button == 3) {
		scale_factor /= 1.1;
		glutPostRedisplay();
	}
	if (button == 4) {
		scale_factor *= 1.1;
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
			command_to_edit->command = command_to_edit->symbol + " " + "point" + " " + \
			to_string((int)((x + x_shifted) * scale_factor)) + " " + to_string((int)((y + y_shifted) * scale_factor));
		else
			command_to_edit->command = static_cast<string>("point ") + \
			to_string((int)((x + x_shifted) * scale_factor)) + " " + to_string((int)((y + y_shifted) * scale_factor));
		
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
	//creating 24 command lines to work with
	commands.push_back(CommandLine(10, 10));
	for (size_t i = 0; i < 24; i++) {
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
