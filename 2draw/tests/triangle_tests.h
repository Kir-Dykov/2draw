#pragma once
#include "../triangle.h"

using namespace std;

int triangle_main() 
{
	triangle t;
	Line bis;
	Circle cir;

	Point p1, p2, p3;
	p1.set_point(-2, 0);
	p2.set_point(-3, -1);
	p3.set_point(-2, -10);
	t.set_triangle(p1, p2, p3);

	cout << "Triangle area: " << t.triangle_area() << endl;

	cout << "Triangle bisectrix: ";
	bis = t.get_bisectrix(2);
	bis.cout_line();
	cout << endl;

	cout << "Triangle altitude: ";
	bis = t.get_altitude(1);
	bis.cout_line();
	cout << endl;

	cout << "Triangle median: ";
	bis = t.get_median(1);
	bis.cout_line();
	cout << endl;

	cout << "Tetragon circumcircle: ";
	cir = t.get_circumcircle();
	cir.cout_circle(cir);
	cout << endl;

	cout << "Tetragon inscribed circle: ";
	cir = t.get_inscribed_circle();
	cir.cout_circle(cir);
	cout << endl;

	return 0;
}