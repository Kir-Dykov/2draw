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
#include "command_line.h"

using namespace std;

const int DELAY = 20;

GLint Width = 1080, Height = 720;

extern vector<CommandLine> commands;
bool editing_a_command;
bool moving_a_point;
CommandLine* command_to_edit;
CommandLine* point_to_move;

void Display(void) {
	//glBegin(GL_TRIANGLE_FAN);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	/*calls of drawing functions*/

	

	for (size_t i = 0; i < commands.size(); i++) {
		if (commands[i].obj != nullptr) {
			commands[i].obj->Draw();
			cout << commands[i].symbol << " is drawn" << endl;
		};
	}

	for (size_t i = 0; i < commands.size(); i++) {
		commands[i].Draw();
	}

	glFinish();
	
}

/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
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
void Keyboard(unsigned char key, int, int)
{
	cout << (int)key;
	if (editing_a_command) {
		
		//backspace key
		if (key == 8 && command_to_edit->command.length() > 0) {
			command_to_edit->command.resize(command_to_edit->command.length() - 1);
		}
		//enter key
		else if (key == 13) { 
			editing_a_command = false;
			command_to_edit->Compile();
			command_to_edit = nullptr;
		}
		else {
			command_to_edit->command.append(1, key);
		}
		
		glutPostRedisplay();
	}
}

void MouseFunc(int button, int state, int x, int y)
{
	y = Height - y;
	cout << button << " " << state << " " << x << " " << y << endl;
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) {
			for (size_t i = 0; i < commands.size(); i++) {
				if (commands[i].is_in(x, y)) {
					editing_a_command = true;
					if (command_to_edit != nullptr) {
						command_to_edit->Compile();
					}

					command_to_edit = &(commands[i]);
					command_to_edit->b = 192;
					cout << "editing a command!" << endl;
					goto break_all;
				}
			}
			for (size_t i = 0; i < commands.size(); i++) {
				if (commands[i].type == "point") cout << distance((*(Point*)commands[i].obj), Point(x, y)) << " ";
				if (commands[i].type == "point" && distance((*(Point*)commands[i].obj), Point(x, y)) < 4)
				{
					moving_a_point = true;
					point_to_move = &(commands[i]);
					cout << "yes";
				}
			}
			break_all:
			glutPostRedisplay();
		}
	}

	
}



void Loop(int) {
	/*dynamic actions go there*/
	glutPostRedisplay();
	glutTimerFunc(DELAY, Loop, 1);
}


void MotionFunc(int x, int y) {
	y = Height - y;
	//cout << "Motion " << x << " " << y << endl;
	if (moving_a_point) {
		point_to_move->command = point_to_move->symbol + " " + "point" + " " + to_string(x) + " " + to_string(y);
		point_to_move->Compile();
		glutPostRedisplay();
	}
}


void PassiveMotionFunc(int x, int y) {
	//cout << "Passive motion " << x << " " << y << endl;

	//glutPostRedisplay();
}


/* Главный цикл приложения */
int gui_main() {
	
	
	commands.push_back(CommandLine(0, 10));
	for (size_t i = 0; i < 10; i++) {
		commands.push_back(CommandLine(0, commands[i].y + 30));
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
