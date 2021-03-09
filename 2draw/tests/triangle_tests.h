#pragma once
#include "../triangle.h"

using namespace std;

int triangle_main() 
{
	triangle t;
	Line bis;
	Circle cir;

	Point p1, p2, p3;
	p1.set_point(0, 0);
	p2.set_point(0, 4);
	p3.set_point(-7, 2);
	t.set_triangle(p1, p2, p3);

	cout << "Triangle area: " << t.triangle_area() << endl;

	cout << "Triangle bisectrix: ";
	bis = t.get_bisectrix(3);
	bis.cout_line();
	cout << endl;

	cout << "Tetragon circumcircle: ";
	cir = t.get_circumcircle();
	cir.cout_circle(cir);
	cout << endl;

	return 0;
}