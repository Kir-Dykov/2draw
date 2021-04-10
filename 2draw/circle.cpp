#include "circle.h"

Circle::Circle(double _x = 0, double _y = 0, double _r = 1) {
	c.x = _x;
	c.y = _y;
	r = _r;
}

Circle::Circle() {
	c.x = 0;
	c.y = 0;
	r = 1;
}

void Circle::set(const Point _center, const double _radius) {
	c.x = _center.x;
	c.y = _center.y;
	r = _radius;
}

void Circle::set(const Point _center, const Point other) {
	c = _center;
	r = c.distance(other);
}

std::ostream& operator<<(std::ostream& os, const Circle& cir) {
	os << "radius: " << cir.radius << ", center: " << cir.center;
	return os;
}

std::vector<Point> Circle::intersections(const Circle circle) const {
	// Algorithm: https://planetcalc.ru/8098/?license=1
	double centers_distance = c.distance(circle.center);
	if (centers_distance == 0 && r == circle.radius) {		// coincide
		return { c, circle.c };
	}
	else if (centers_distance > r + circle.radius) {			// don't intersect
		return vector<Point>(0);
	}
	else if (centers_distance < abs(r - circle.r)) {		// one to the other
		return vector<Point>(0);
	}
	else // touch or intersect at two points
	{
		double a = (r * r - circle.r * circle.r + \
			centers_distance * centers_distance) / (2 * centers_distance);
		double h = sqrt(r * r - a * a);
		Point tmp_pnt;
		tmp_pnt.x = c.x + a / centers_distance * (circle.c.x - c.x);
		tmp_pnt.y = c.y + a / centers_distance * (circle.c.y - c.y);
		Point first_intersection, second_intersection;
		first_intersection.x = tmp_pnt.x + h / centers_distance * (circle.c.y - c.y);
		first_intersection.y = tmp_pnt.y - h / centers_distance * (circle.c.x - c.x);
		second_intersection.x = tmp_pnt.x - h / centers_distance * (circle.c.y - c.y);
		second_intersection.y = tmp_pnt.y + h / centers_distance * (circle.c.x - c.x);
		if (first_intersection == second_intersection)
			return { first_intersection };
		else
			return { first_intersection, second_intersection };
	}
}