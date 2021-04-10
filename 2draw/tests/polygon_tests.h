#pragma once
#include "consts.h"
#include <math.h>
#include "../polygon.h"
#include <iostream>

int polygon_main() {

	{
		Polygon p = { Point(0,0), Point(1,0), Point(1,1), Point(0,1) };
		std::cout << "points in rectangle: " << p << endl;

		std::cout << "it's center: \n";
		std::cout << p.center_of_mass() << endl;

		p.rotate(PI / 4);

		std::cout << "it's points after rotation by pi/4:\n" << p << endl;
		std::cout << "Is (0.5, 0.5) inside polygon? " << p.is_in(Point(0.5, 0.5)) << endl;
		p += Vector(10, 10);
		std::cout << "it's points after shifting by vector (10, 10):\n" << p << endl;
		std::cout << "Area of moved square:\n" << p.area() << endl;
	}

	std::cout << "\n\n\n";

	{
		Polygon p = { Point(2,0), Point(0,2), Point(6,6) };
		cout << "points in triangle: " << p << endl;
		cout << "it's area:\n" << p.area() << endl;
		cout << "it's center: \n";
		cout << p.center_of_mass() << endl;

		p.rotate(PI / 4);

		cout << "it's points after rotation by pi/4:\n" << p << endl;

		p += Vector(10, 10);
		cout << "it's points after shifting by vector (10, 10):\n" << p << endl;
		cout << "Area of moved triangle:\n" << p.area() << endl;
	}

	std::cout << "\n\n\n";

	{
		Polygon p;
		for (int i = 0; i < 8; i++)
			p.append(Point(cos(2* PI * i / 8), sin(2* PI * i / 8)));

		cout << "points in octagon: " << p << endl;
		cout << "it's center: " << p.center_of_mass() << endl;
		cout << "it's area: " << p.area() << endl;

		cout << "Is (0, 0) inside octagon? " << p.is_in(Point(0, 0)) << endl;
	}
	std::cout << "\n\n\n";
	
	{
		std::cout << "Zadacha is kontesta na vypuklie obolochki (finding a convex hull)\n";
		vector<Point> v = {
			Point(4,6),
			Point(2,5),
			Point(6,4),
			Point(7,7),
			Point(4,4),
			Point(1,5),
			Point(3,8),
			Point(3,2),
			Point(5,7),
			Point(7,3)
		};

		Polygon p = convex_hull(v);
		std::cout << "convex hull is " << p << endl;
		std::cout << "area of the convex hull is " << p.area() << endl;
	}
	std::cout << "\n\n\n";
	{
		const int N = 1000000;
		Polygon p;
		for (int i = 0; i < N; i++)
			p.append(Point(cos(2 * PI * (double)i / (double)N), sin(2 * PI * (double)i / (double)N)));

		std::cout << "1'000'000-gon approximating a circle" << endl;
		std::cout << "it's center (should be (0,0)): " << p.center_of_mass() << endl;
		std::cout << "it's area (should be good aproximation of pi): " << p.area() << endl;
		std::cout << "difference from actual pi value: " << p.area() - PI << endl;
		std::cout << "Is (0, 0) inside polygon? (should be 1) : " << p.is_in(Point(0, 0)) << endl;
		std::cout << "Is (1, 0) inside polygon? (should be 1) : " << p.is_in(Point(1, 0)) << endl;
		std::cout << "Is (1, 1) inside polygon? (should be 0) : " << p.is_in(Point(1, 1)) << endl;
		std::cout << "Is (-1, -1) inside polygon? (should be 0) : " << p.is_in(Point(-1, -1)) << endl;
		std::cout << "Is (-0.999, 0) inside polygon? (should be 1) : " << p.is_in(Point(-0.999, 0)) << endl;
	}
	

	return 0;
}