#include "line.h"
#include "vector.h"
#include <math.h>

const double PI = 3.14159265358979;
void Line::set_line(Point _p1, Point _p2)
{
	p1 = _p1;
	p2 = _p2;
	a = p1.y - p2.y;
	b = p2.x - p1.x;
	c = p1.x * p2.y - p2.x * p1.y;
}

void Line::set_line(double _a = 1, double _b = 1, double _c = 0)
{
	a = _a;
	b = _b;
	c = _c;
}

double Line::get_angle_rad()
{
	return atan(-a / b);
}

double Line::get_angle_deg()
{
	return atan(-a / b) * 180 / PI;
}

bool Line::operator==(Line L)
{
	return a / L.a == b / L.b && b / L.b == c / L.c;
}

//TODO: пусть функци€ принимает точку, через которую должна проходить перпендикул€рна€ пр€ма€
Line perp_Line(Line L)
{
	Line res;
	res.a = L.b;
	res.b = -L.a;
	res.c = L.c;
	return res;
}

bool are_parallel(Line L1, Line L2)
{
	return L1.a / L2.a == L1.b / L2.b;
}

bool point_on_Line(Point p, Line L)
{
	return p.x * L.a + p.y * L.b + L.c == 0;
}

void Line::cout_line()
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

bool Line::point_line_belonging(Point p)
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
	if (get_twoLines_radangle(L1, L2) * 180.0 / PI > 90)
		return 180 - get_twoLines_radangle(L1, L2) * 180.0 / PI;
	else
		return 180 - get_twoLines_radangle(L1, L2) * 180.0 / PI;
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
