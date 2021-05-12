#include "point.h"
#include "consts.h"
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

Point Point::middlepoint(const Point& p) const{
	Point m;
	m.x = (x + p.x) / 2;
	m.y = (y + p.y) / 2;
	return m;
}

std::ostream& operator<<(std::ostream& os, const Point& p) { os << "(" << p.x << ", " << p.y << ")"; return os; }

void Point::Draw() const {
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(red, green, blue);/*rand() % 128 + 128*/
	
	int N = 10;
	float radius = 4;
	float d_angle = 2 * PI / (float)N;
	float angle = 0;

	glVertex2f(x, y);
	for (int i = 0; i <= N; i++) {
		angle += d_angle;
		glVertex2f(radius * cos(angle) + x, radius * sin(angle) + y);
	}
	glEnd();
	
}