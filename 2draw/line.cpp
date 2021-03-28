#include "line.h"
#include "vector.h"
#define _USE_MATH_DEFINES
#include <math.h>

void Line::set(Point p1, Point p2) {
	_a = p1.y - p2.y;
	_b = p2.x - p1.x;
	_c = p1.x * p2.y - p2.x * p1.y;
}



double Line::get_angle_rad() const {return atan(-_a / _b);}

double Line::get_angle_deg() const {return atan(-_a / _b) * 180 / M_PI;}

bool Line::operator==(const Line L) const {
	return _a / L._a == _b / L._b && _b / L._b == _c / L._c;
}

//TODO: пусть функци€ принимает точку, через которую должна проходить перпендикул€рна€ пр€ма€
Line perpendicular(const Line L) {
	return Line(L.b, -L.a, L.c);
}

bool are_parallel(const Line L1, const Line L2) {
	return L1.a / L2.a == L1.b / L2.b;
}

bool point_on_Line(const Point p, const Line L) {
	return p.x * L.a + p.y * L.b + L.c == 0;
}

void Line::cout_line() const
{
	if (a == 1)
		cout << "x ";
	else if (a == -1)
		cout << "- x ";
	else if (a != 0)
		cout << a << "x ";
	if (b == 1)
		cout << "+ y ";
	else if (b == -1)
		cout << "- y ";
	else if (b != 0)
		if (b > 0)
			cout << "+ " << b << "y ";
		else
			cout << "- " << -b << "y ";
	if (c > 0)
		cout << "+ " << c << " ";
	else if (c < 0)
		cout << "- " << -c << " ";
	cout << "= 0";
}

bool Line::point_line_belonging(Point p) const
{
	return (p.x * a + p.y * b + c == 0);
}

double get_twoLines_radangle(Line L1, Line L2)
{
	double a = (L1.a * L2.a + L1.b * L2.b) / (sqrt(L1.a * L1.a + L1.b * L1.b) * sqrt(L2.a * L2.a + L2.b * L2.b));
	return acos(a);
}

double get_twoLines_degangle(Line L1, Line L2)
{
	if (get_twoLines_radangle(L1, L2) * 180.0 / M_PI > 90)
		return 180 - get_twoLines_radangle(L1, L2) * 180.0 / M_PI;
	else
		return 180 - get_twoLines_radangle(L1, L2) * 180.0 / M_PI;
}

int find_halfplane(Line L, Point p)
{
	if (L.a > 0 || L.a == 0 && L.b > 0) {
		if (p.x * L.a + p.y * L.b + L.c > 0)
			return 1;
		else if (p.x * L.a + p.y * L.b + L.c < 0)
			return -1;
		else
			return 0;
	}
	else
	{
		if (p.x * L.a + p.y * L.b + L.c < 0)
			return 1;
		else if (p.x * L.a + p.y * L.b + L.c > 0)
			return -1;
		else
			return 0;
	}
}
//Kramers method for find increase points
Point Line::findpointincrs(Line first, Line second) {
	double generaldet = determinant(Vector(first.a, first.b), Vector(second.a, second.b));
	double detforx = determinant(Vector(-first.c, first.b), Vector(-second.c, second.b));
	double detfory = determinant(Vector(first.a, -first.c), Vector(second.a, -second.c));
	Point res;
	res.x = detforx / generaldet;
	res.y = detfory / generaldet;
	return res;
}
