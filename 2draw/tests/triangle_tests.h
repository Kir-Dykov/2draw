#pragma once
#include "../triangle.h"

using namespace std;

int triangle_main() 
{
	Triangle t, s;
	Line bis;
	Circle cir;

	Point p1, p2, p3;
	p1.set(1, 0);
	p2.set(2, 0);
	p3.set(4, 0);
	t.set(p1, p2, p3);

	cout << "Triangle area: " << t.area() << endl;

	cout << "Triangle bisectrix: ";
	bis = t.get_bisectrix(t.second_vertex);
	cout << bis;
	cout << endl;

	cout << "Triangle altitude: ";
	bis = t.get_altitude(t.second_vertex);
	cout << bis;
	cout << endl;

	cout << "Triangle median: ";
	bis = t.get_median(t.second_vertex);
	cout << bis;
	cout << endl;

	cout << "Triangle circumcircle: ";
	cir = t.get_circumcircle();
	cout << cir;
	cout << endl;

	cout << "Triangle inscribed circle: ";
	cir = t.get_inscribed_circle();
	cout << cir;
	cout << endl;

	return 0;
}