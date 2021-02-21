#include "point.h"
#include <cmath>

void point::set_point(int _x = 0, int _y = 0) {
	x = _x;
	y = _y;
}

int point::find_quarter() {
	if (x > 0 && y > 0)
		return 1;
	else if (x < 0 && y > 0)
		return 2;
	else if (x < 0 && y < 0)
		return 3;
	else if (x > 0 && y < 0)
		return 4;
	else return 0;
}

void point::cout_point() {
	cout << "(" << x << ", " << y << ") ";
}

bool point::operator==(point p) {
	return x == p.x && y == p.y;
}

point sym_point_x(point p) {
	point a;
	a.x = p.x;
	a.y = -p.y;
	return a;
}

point sym_point_y(point p) {
	point a;
	a.x = -p.x;
	a.y = p.y;
	return a;
}

double point_distance(point p1, point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

