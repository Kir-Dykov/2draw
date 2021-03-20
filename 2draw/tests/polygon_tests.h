#pragma once
#define _USE_MATH_DEFINES
#include "math.h"
#include "../polygon.h"

using namespace std;

int polygon_main() {

	{
		Polygon p = { Point(0,0), Point(1,0), Point(1,1), Point(0,1) };
		cout << "points in rectangle: " << p << endl;

		cout << "it's center: \n";
		cout << p.center_of_mass() << endl;

		p.rotate(M_PI / 4);

		cout << "it's points after rotation by pi/4:\n" << p << endl;
		cout << "Is (0.5, 0.5) inside polygon? " << p.is_in(Point(0.5, 0.5)) << endl;
		p += Vector(10, 10);
		cout << "it's points after shifting by vector (10, 10):\n" << p << endl;
		cout << "Area of moved square:\n" << p.area() << endl;
	}

	cout << "\n\n\n";

	{
		Polygon p = { Point(2,0), Point(0,2), Point(6,6) };
		cout << "points in triangle: " << p << endl;
		cout << "it's area:\n" << p.area() << endl;
		cout << "it's center: \n";
		cout << p.center_of_mass() << endl;

		p.rotate(M_PI / 4);

		cout << "it's points after rotation by pi/4:\n" << p << endl;

		p += Vector(10, 10);
		cout << "it's points after shifting by vector (10, 10):\n" << p << endl;
		cout << "Area of moved triangle:\n" << p.area() << endl;
	}

	cout << "\n\n\n";

	{
		Polygon p;
		for (int i = 0; i < 8; i++)
			p.append(Point(cos(M_PI * i / 8), sin(M_PI * i / 8)));

		cout << "points in octagon: " << p << endl;
		cout << "it's center: " << p.center_of_mass() << endl;
		cout << "it's area: " << p.area() << endl;

		cout << "Is (0, 0) inside polygon? " << p.is_in(Point(0, 0)) << endl;
	}
	


	return 0;
}