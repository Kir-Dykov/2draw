#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include "glut.h"

#include "point.h"
#include "circle.h"
#include "polygon.h"

using namespace std;
GLint Width = 1600, Height = 900;
const int DELAY = 20;

ObjectList objects;

void Display(void) {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	/*calls of drawing functions*/
	
	objects.Draw();
	
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
void Keyboard(int key, int, int)
{
	
}

void MouseFunc(int button, int state, int x, int y)
{
	//cout << button << " " << state << " " << x << " " << y << endl;
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			
			/* action */
			

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
	//cout << "Motion " << x << " " << y << endl;
	glutPostRedisplay();
}

Circle circle_filled(Width * 1 / 10, Height * 9 / 10, 50);
Circle circle_not_filled(Width * 2 / 10, Height * 9 / 10, 50);
Point p(Width * 3 / 10, Height * 9 / 10);

Polygon polygon_not_filled = { Point(50,100), Point(50,500),Point(450,500), Point(250,400) };
Polygon polygon_filled = { Point(500,100), Point(500,500), Point(600,700), Point(750,450), Point(900,500), Point(650,400) };


void PassiveMotionFunc(int x, int y) {
	//cout << "Passive motion " << x << " " << y << endl;
	circle_filled.set_radius(x);
	circle_not_filled.set_radius(x);

	glutPostRedisplay();
}


/* Главный цикл приложения */
int opengl_main()
{
	
	circle_filled.set_look(255, 192, 128);
	objects.append(circle_filled);

	circle_not_filled.set_look(255, 128, 192, false);
	objects.append(circle_not_filled);

	p.set_look(128, 192, 255);
	objects.append(p);

	polygon_not_filled.set_look(255, 192, 128, false);
	objects.append(polygon_not_filled);

	polygon_filled.set_look(255, 192, 128, true);
	objects.append(polygon_filled);
	
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("2draw");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	//glutTimerFunc(DELAY, Loop, 1);
	glutSpecialFunc(Keyboard);
	glutMouseFunc(MouseFunc);
	//glutKeyboardFunc(Keyboard);

	glutMotionFunc(MotionFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);


	glutMainLoop();

	return 0;
}
