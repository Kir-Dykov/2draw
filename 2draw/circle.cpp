#include "circle.h"

Circle::Circle(double _x = 0, double _y = 0, double _r = 1) {
	center.x = 0;
	center.y = 0;
	radius = 0;
}

Circle::Circle() {
	center.x = 0;
	center.y = 0;
	radius = 0;
}

void Circle::set(const Point _center, const double _radius) {
	center.x = _center.x;
	center.y = _center.y;
	radius = _radius;
}

void Circle::set(const Point _center, const Point other) {
	Point cen = _center;
	center = _center;
	radius = cen.distance(other);
}

std::ostream& operator<<(std::ostream& os, const Circle& c) {
	os << "the circle with the radius of " << c.radius << " and the center at " << c.center;
	return os;
}

std::vector<Point> Circle::intersections(const Circle circle) {
	// Algorithm: https://planetcalc.ru/8098/?license=1
	double centers_distance = (*this).center.distance(circle.center);
	if (centers_distance == 0 && (*this).radius == circle.radius) {		// coincide
		return { (*this).center, circle.center };
	}
	else if (centers_distance > (*this).radius + circle.radius) {			// don't intersect
		return vector<Point>(0);
	}
	else if (centers_distance < abs((*this).radius - circle.radius)) {		// one to the other
		return vector<Point>(0);
	}
	else // touch or intersect at two points
	{
		double a = ((*this).get_radius() * (*this).get_radius() - circle.get_radius() * circle.get_radius() + \
			centers_distance * centers_distance) / (2 * centers_distance);
		double h = sqrt((*this).get_radius() * (*this).get_radius() - a * a);
		Point tmppnt;
		tmppnt.x = (*this).center.x + a / centers_distance * (circle.center.x - (*this).center.x);
		tmppnt.y = (*this).center.y + a / centers_distance * (circle.center.y - (*this).center.y);
		Point first_intersection, second_intersection;
		first_intersection.x = tmppnt.x + h / centers_distance * (circle.center.y - (*this).center.y);
		first_intersection.y = tmppnt.y - h / centers_distance * (circle.center.x - (*this).center.x);
		second_intersection.x = tmppnt.x - h / centers_distance * (circle.center.y - (*this).center.y);
		second_intersection.y = tmppnt.y + h / centers_distance * (circle.center.x - (*this).center.x);
		if (first_intersection == second_intersection)
			return { first_intersection };
		else
			return { first_intersection, second_intersection };
	}
}