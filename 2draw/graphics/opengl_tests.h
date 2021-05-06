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

void PassiveMotionFunc(int x, int y) {
	//cout << "Passive motion " << x << " " << y << endl;
	
	
	glutPostRedisplay();
}

/* Главный цикл приложения */
int opengl_main()
{
	Circle c(Width / 2, Height / 2, 50);
	c.set_look(255, 192, 128);

	objects.append(c);
	
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
