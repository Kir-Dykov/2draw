#define _USE_MATH_DEFINES
#include <math.h>
#include "line.h"

void Line::set(Point _p1, Point _p2) {
	p1 = _p1;
	p2 = _p2;
	a = p1.y - p2.y;
	b = p2.x - p1.x;
	c = p1.x * p2.y - p2.x * p1.y;
}

void Line::set(double _a, double _b, double _c) {
	a = _a;
	b = _b;
	c = _c;
	p1.x = -c / a;
	p1.y = 0;
	p2.x = -(b + c) / a;
	p2.y = 1;
}

double Line::get_angle_rad() {
	return atan(-a / b);
}

double Line::get_angle_deg() {
	return atan(-a / b) * 180 / M_PI;
}

bool Line::operator==(const Line L) {
	return a / L.a == b / L.b && b / L.b == c / L.c;
}

Line Line::perpendicular() {
	Line res;
	res.a = b;
	res.b = -a;
	res.c = c;
	return res;
}

bool Line::is_parallel_to(const Line L) {
	return a / L.a == b / L.b;
}

bool Line::point_on_Line(const Point p) {
	return p.x * a + p.y * b + c == 0;
}

double Line::get_twoLines_radangle(const Line L) {
	double ang = (a * L.a + b * L.b) / (sqrt(a * a + L.b * L.b) * sqrt(L.a * L.a + L.b * L.b));
	return acos(ang);
}

double Line::get_twoLines_degangle(const Line L) {
	if ((*this).get_twoLines_radangle(L) * 180.0 / M_PI > 90)
		return 180 - (*this).get_twoLines_radangle(L) * 180.0 / M_PI;
	else
		return 180 - (*this).get_twoLines_radangle(L) * 180.0 / M_PI;
}

int Line::find_halfplane(const Point p) {
	if (a > 0 || a == 0 && b > 0) {
		if (p.x * a + p.y * b + c > 0)
			return 1;
		else if (p.x * a + p.y * b + c < 0)
			return -1;
		else
			return 0;
	}
	else
	{
		if (p.x * a + p.y * b + c < 0)
			return 1;
		else if (p.x * a + p.y * b + c > 0)
			return -1;
		else
			return 0;
	}
}

std::ostream& operator<<(std::ostream& os, const Line& l) {
	if (l.a == 1)
		os << "x ";
	else if (l.a == -1)
		os << "-x ";
	else if (l.a != 0)
		os << l.a << "x ";
	if (l.b == 1)
		os << "+y ";
	else if (l.b == -1)
		os << "-y ";
	else if (l.b != 0)
		if (l.b > 0)
			os << "+ " << l.b << "y ";
		else
			os << l.b << "y ";
	if (l.c > 0)
		os << "+" << l.c << " ";
	else if (l.c < 0)
		os << l.c << " ";
	cout << "= 0";
	return os;
}