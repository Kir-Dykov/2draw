#pragma once
#include "../triangle.h"

using namespace std;

int triangle_main() 
{
	Triangle t, s;
	Line bis;
	Circle cir;

	Point p1, p2, p3;
	p1.set(-2, -10);
	p2.set(-3, -1);
	p3.set(-2, 0);
	t.set(p1, p2, p3);

	cout << "Triangle area: " << t.area() << endl;

	cout << "Triangle bisectrix: ";
	bis = t.get_bisectrix(t.point2);
	cout << bis;
	cout << endl;

	cout << "Triangle altitude: ";
	bis = t.get_altitude(t.point2);
	cout << bis;
	cout << endl;

	cout << "Triangle median: ";
	bis = t.get_median(t.point2);
	cout << bis;
	cout << endl;

	cout << "Triangle circumcircle: ";
	cout << t.get_circumcircle();
	cout << endl;

	cout << "Triangle inscribed circle: ";
	cout << t.get_inscribed_circle();
	cout << endl;

	return 0;
}