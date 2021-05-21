#include "consts.h"
#include "line.h"

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
	p1.x = -c / a;
	p1.y = 0;
	p2.x = -(b + c) / a;
	p2.y = 1;
}

double Line::get_angle_rad() const{
	return atan(-a / b);
}

double Line::get_angle_deg() const{
	return atan(-a / b) * 180 / PI;
}

bool Line::operator==(const Line& L) const {
	return a / L.a == b / L.b && b / L.b == c / L.c;
}

Line Line::perpendicular() const {
	Line res;
	res.a = b;
	res.b = -a;
	res.c = c;
	return res;
}

Line Line::perp2point_on_line(const Point& pnt) const {
	Line res;
	res.a = -b;
	res.b = a;
	res.c = -a * pnt.y + b * pnt.x;

	return res;
}

bool Line::is_parallel_to(const Line& L) const{
	return a * L.b == b * L.a;
}

bool Line::point_on_Line(const Point& p) const {
	return p.x * a + p.y * b + c == 0;
}

double Line::get_twoLines_radangle(const Line& L) const {
	double ang = (a * L.a + b * L.b) / ((sqrt(a * a + b * b) * sqrt(L.a * L.a + L.b * L.b)));
	return acos(ang);
}

double Line::get_twoLines_degangle(const Line& L) const
{
	if ((*this).get_twoLines_radangle(L) * 180.0 / PI > 90)
		return 180 - (*this).get_twoLines_radangle(L) * 180.0 / PI;
	else
		return (*this).get_twoLines_radangle(L) * 180.0 / PI;
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

Line Line::parallel(const Point& P) const {
	Line LP;
	LP.a = a; LP.b = b;
	LP.c = -a * P.x - b * P.y; // value, such that when we plug-in point P into formula a*x+b*y+c we get 0
	return LP;
}

void Line::Draw() const {
	Vector ab; Point _a, _b;
	_a = p1; _b = p2;
	// means that the function get a line without certain dots (in construct base coords is (0, 0) and (1, 1))
	if (p1 == Point(0, 0) && p2 == Point(1, 1) || p2 == Point(0, 0) && p1 == Point(1, 1)) {
		if (a == 0) {
			_a = Point(0, -c / b);
			_b = Point(1, -c / b);
		}
		else if (b == 0) {
			_a = Point(-c / a, 0);
			_b = Point(-c / a, 1);
		}
		else {
			if (c != 0) {
				_a = Point(-c / a, 0);
				_b = Point(0, -c / b);
			}
			else {
				_a = Point(0, 0);
				_b = Point(1, -a / b);
			}
		}
	}
	ab = _a - _b;
	ab.x *= 10000; ab.y *= 10000;
	_a = _a + ab;
	ab.x = -ab.x; ab.y = -ab.y;
	_b = _b + ab;

	glBegin(GL_LINES);
	glVertex2f(_a.x, _a.y);
	glVertex2f(_b.x, _b.y);
	glEnd();
}