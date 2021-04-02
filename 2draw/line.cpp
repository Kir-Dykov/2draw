#include "line.h"
#include <math.h>

const double PI = 3.14159265358979;
void Line::set(Point _p1, Point _p2)
{
	p1 = _p1;
	p2 = _p2;
	a = p1.y - p2.y;
	b = p2.x - p1.x;
	c = p1.x * p2.y - p2.x * p1.y;
}

void Line::set(int _a = 1, int _b = 1, int _c = 0)
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

bool Line::operator==(const Line L)
{
	return a / L.a == b / L.b && b / L.b == c / L.c;
}

//TODO: пусть функци€ принимает точку, через которую должна проходить перпендикул€рна€ пр€ма€
Line perpendicular(const Line L)
{
	Line res;
	res.a = L.b;
	res.b = -L.a;
	res.c = L.c;
	return res;
}

bool are_parallel(const Line L1, const Line L2)
{
	return L1.a / L2.a == L1.b / L2.b;
}

bool point_on_Line(const Point p, const Line L)
{
	return p.x * L.a + p.y * L.b + L.c == 0;
}

void Line::cout_line()
{
	if (a == 1)
		cout << "x ";
	else if (a == -1)
		cout << "-x ";
	else if (a != 0)
		cout << a << "x ";
	if (b == 1)
		cout << "+y ";
	else if (b == -1)
		cout << "-y ";
	else if (b != 0)
		if (b > 0)
			cout << "+ " << b << "y ";
		else
			cout << b << "y ";
	if (c > 0)
		cout << "+" << c << " ";
	else if (c < 0)
		cout << c << " ";
	cout << "= 0";
}

double get_twoLines_radangle(const Line L1, const Line L2)
{
	double a = (L1.a * L2.a + L1.b * L2.b) / (sqrt(L1.a * L1.a + L1.b * L1.b) * sqrt(L2.a * L2.a + L2.b * L2.b));
	return acos(a);
}

double get_twoLines_degangle(const Line L1, const Line L2)
{
	if (get_twoLines_radangle(L1, L2) * 180.0 / PI > 90)
		return 180 - get_twoLines_radangle(L1, L2) * 180.0 / PI;
	else
		return 180 - get_twoLines_radangle(L1, L2) * 180.0 / PI;
}

int find_halfplane(const Line L, const Point p)
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