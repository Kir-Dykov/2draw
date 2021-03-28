#include "point.h"
#include <cmath>


void Point::set(double _x = 0, double _y = 0)
{
	x = _x;
	y = _y;
}

int Point::find_quarter()
{
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

void Point::cout_point()
{
	cout << "(" << x << ", " << y << ") ";
}

std::ostream& operator<<(std::ostream& os, const Point& p) { os << "(" << p.x << ", " << p.y << ")"; return os; }

Point sym_point_x(Point p)
{
	Point a;
	a.x = p.x;
	a.y = -p.y;
	return a;
}

Point sym_point_y(Point p)
{
	Point a;
	a.x = -p.x;
	a.y = p.y;
	return a;
}

double distance(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

Point middlepoint(Point p1, Point p2) {
	Point p;
	p.x = (p1.x + p2.x) / 2;
	p.y = (p1.y + p2.y) / 2;
	return p;
}

