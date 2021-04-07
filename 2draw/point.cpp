#include "point.h"
#include <cmath>

void Point::set(double _x = 0, double _y = 0) {
	x = _x;
	y = _y;
}

int Point::find_quarter() const{
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

double Point::distance(const Point p) const{
	return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

Point Point::middlepoint(const Point p) const{
	Point m;
	m.x = (x + p.x) / 2;
	m.y = (y + p.y) / 2;
	return m;
}

std::ostream& operator<<(std::ostream& os, const Point& p) { os << "(" << p.x << ", " << p.y << ")"; return os; }