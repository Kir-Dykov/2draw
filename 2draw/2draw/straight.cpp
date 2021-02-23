#include "straight.h"
#include <cmath>
const double PI = 3.14159265358979;
void straight::set_straight_p(point _p1, point _p2) {
	p1 = _p1;
	p2 = _p2;
	a = 1.0 / (p2.x - p1.x);
	b = 1.0 / (p1.y - p2.y);
	c = p1.y / (p2.y - p1.y) - p1.x / (p2.x - p1.x);
}

void straight::set_straight_abc(int _a = 1, int _b = 1, int _c = 0) {
	a = _a;
	b = _b;
	c = _c;
}

double straight::get_straight_radangle() {
	return atan(-a / b);
}

double straight::get_straight_degangle() {
	return atan(-a / b) * 180 / PI;
}

bool straight::operator==(straight L) {
	return a / L.a == b / L.b && b / L.b == c / L.c;
}

straight perp_straight(straight L) {
	straight res;
	res.a = L.b;
	res.b = -L.a;
	res.c = L.c;
	return res;
}

bool parallel_straight(straight L1, straight L2) {
	return L1.a / L2.a == L1.b / L2.b;
}

bool point_on_straight(point p, straight L) {
	return p.x * L.a + p.y * L.b + L.c == 0;
}

void straight::cout_straight() {
	cout << a << "*x ";
	if (b > 0)
		cout << "+";
	cout << b << "*y ";
	if (c > 0)
		cout << "+";
	cout << c << endl;
}