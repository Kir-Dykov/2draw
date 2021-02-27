#include "line.h"
#include <math.h>

const double PI = 3.14159265358979;
void Line::set(point _p1, point _p2) 
{
	p1 = _p1;
	p2 = _p2;
	a = 1.0 / (p2.x - p1.x);
	b = 1.0 / (p1.y - p2.y);
	c = p1.y / (p2.y - p1.y) - p1.x / (p2.x - p1.x);
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

bool point_on_Line(point p, Line L) 
{
	return p.x * L.a + p.y * L.b + L.c == 0;
}

void Line::cout_line() 
{
	cout << a << "*x ";
	if (b > 0)
		cout << "+";
	cout << b << "*y ";
	if (c > 0)
		cout << "+";
	cout << c << endl;
}

double get_twoLines_radangle(Line L1, Line L2) 
{
	double a = (L1.a * L2.a + L1.b * L2.b) / (sqrt(L1.a * L1.a + L1.b * L1.b) * sqrt(L2.a * L2.a + L2.b * L2.b));
	return acos(a);
}

double get_twoLines_degangle(Line L1, Line L2) 
{
	double a = (L1.a * L2.a + L1.b * L2.b) / (sqrt(L1.a * L1.a + L1.b * L1.b) * sqrt(L2.a * L2.a + L2.b * L2.b));
	return acos(a) * 180 / PI;
}
