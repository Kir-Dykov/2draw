#pragma once
#include "../polygon.h"

using namespace std;

int polygon_main() {

	Polygon p;

	p.append(Point(0, 0));
	p.append(Point(1, 0));
	p.append(Point(1, 1));
	p.append(Point(0, 1));

	cout << "center: \n";
	cout << p.center_of_mass().x << " " << p.center_of_mass().y << endl;

	cout << "Points before rotation:\n" << p << endl;

	p.rotate(3.141592 / 4);

	cout << "Points after rotation:\n" << p << endl;

	cout << "Are of rotated square:\n" << p.area() << endl;

	return 0;
}