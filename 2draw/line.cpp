#include "line.h"

Line::Line(const Point& _p1, const Point& _p2) {
	p1 = _p1;
	p2 = _p2;
	a = p1.y - p2.y;
	b = p2.x - p1.x;
	c = p1.x * p2.y - p2.x * p1.y;
}

Line::Line(const double _a, const double _b, const double _c) {
	a = _a; b = _b; c = _c; 
	if (a == 0) {
		p1 = Point(0, -c / b);
		p2 = Point(1, -c / b);
	}
	else if (b == 0) {
		p1 = Point(-c / a, 0);
		p2 = Point(-c / a, 1);
	}
	else
		if (c != 0) {
			p1 = Point(-c / a, 0);
			p2 = Point(0, -c / b);
		}
		else {
			p1 = Point(0, 0);
			p2 = Point(1, -a / b);
		}
}

void Line::set(const Point& _p1, const Point& _p2) {
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
	if (a == 0) {
		p1 = Point(0, -c / b);
		p2 = Point(1, -c / b);
	}
	else if (b == 0) {
		p1 = Point(-c / a, 0);
		p2 = Point(-c / a, 1);
	}
	else
		if (c != 0) {
			p1 = Point(-c / a, 0);
			p2 = Point(0, -c / b);
		}
		else {
			p1 = Point(0, 0);
			p2 = Point(1, -a / b);
		}
}

double Line::get_twoLines_radangle(const Line& L) const {
	double ang = (a * L.a + b * L.b) / ((sqrt(a * a + b * b) * sqrt(L.a * L.a + L.b * L.b)));
	return acos(ang);
}

double Line::get_twoLines_degangle(const Line& L) const
{
	if (get_twoLines_radangle(L) * 180.0 / PI > 90)
		return 180 - get_twoLines_radangle(L) * 180.0 / PI;
	else
		return get_twoLines_radangle(L) * 180.0 / PI;
}

int Line::find_halfplane(const Point& p) const {
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

Point Line::intersection(const Line& second) const {
	// Cramer's method
	// find the determinant of the matrix of the system
	double general_det = determinant(Vector(a, second.a), Vector(b, second.b));
	if (general_det == 0) {
		cerr << "Intersection of two parallel lines does not exist";
		throw "Intersection of two parallel lines does not exist";
	}
	// finding determinant for x-coordinate
	double x_det = determinant(Vector(-c, -second.c), Vector(b, second.b));
	// finding determinant for y-coordinate
	double y_det = determinant(Vector(a, second.a), Vector(-c, -second.c));

	// returning the coordinates of the intersection point
	return (Point(x_det / general_det, y_det / general_det));
}

void Line::Draw() const {
	Vector ab; Point _a, _b;
	_a = p1; _b = p2;
	ab = _a - _b;
	ab.x *= 10000; ab.y *= 10000;
	_a = _a + ab;
	ab.x = -ab.x; ab.y = -ab.y;
	_b = _b + ab;

	glBegin(GL_LINES);
	glColor3ub(red, green, blue);
	glVertex2f(_a.x, _a.y);
	glVertex2f(_b.x, _b.y);
	glEnd();
}