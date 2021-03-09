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
	p2.set_point(3, 0);
	p3.set_point(0, 4);
	t.set_triangle(p1, p2, p3);

	cout << "Triangle area: " << t.triangle_area() << endl;

	cout << "Triangle angles: ";
	for (int i = 1; i <= 3; i++)
		cout << t.get_triangle_angle(i) << "  ";
	cout << endl;

	cout << "Triangle bisectrix: ";
	bis = t.get_bisectrix(1);
	bis.cout_line();
	cout << endl;

	cout << "Triangle altitude: ";
	bis = t.get_altitude(2);
	bis.cout_line();
	cout << endl;

	cout << "Triangle median: ";
	bis = t.get_median(3);
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

	cout << "Triangle type: " << t.triangle_type() << endl;

	return 0;
}