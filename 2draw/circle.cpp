#define _USE_MATH_DEFINES
#include <math.h>

#include "circle.h"

Circle::Circle(double _x = 0, double _y = 0, double _r = 0) {
	center.x = 0;
	center.y = 0;
	radius = 0;
}

Circle::Circle() {
	center.x = 0;
	center.y = 0;
	radius = 0;
}

void Circle::set(Point _center, double _radius) {
	center.x = _center.x;
	center.y = _center.y;
	radius = _radius;
}
void Circle::set(Point _center, Point other) {
	center = _center;
	radius = distance(_center, other);
}
void Circle::set_radius(double _radius) {radius = _radius;}
void Circle::set_center(Point _center) {center = _center;}
void Circle::set_centerx(double _x) {center.x = _x;}
void Circle::set_centery(double _y) {center.y = _y;}


double Circle::get_radius() const {return radius;}
Point Circle::get_center() const {return center;}

std::ostream& operator<<(std::ostream& os, Circle& c) {
	os << "the circle with the radius of " << c.radius << " and the center at " << c.center;
	return os;
}

double Circle::circumference() const {
	return 2 * M_PI * radius;
}

double Circle::area() const {
	return M_PI * radius * radius;
}


std::vector<Point> intersections(Circle circle1, Circle circle2) {
	// Algorithm: https://planetcalc.ru/8098/?license=1
	double centers_distance = distance(circle1.center, circle2.center);
	if (centers_distance == 0 && circle1.radius == circle2.radius) {		// coincide
		return { circle1.center, circle2.center };
	}
	else if (centers_distance > circle1.radius + circle2.radius) {			// don't intersect
		return vector<Point>(0);
	}
	else if (centers_distance < abs(circle1.radius - circle2.radius)) {	// one to the other
		return vector<Point>(0);
	}
	else // touch or intersect at two points
	{
		double a = (circle1.get_radius() * circle1.get_radius() - circle2.get_radius() * circle2.get_radius() + \
			centers_distance * centers_distance) / (2 * centers_distance);
		double h = sqrt(circle1.get_radius() * circle1.get_radius() - a * a);
		Point tmppnt;
		tmppnt.x = circle1.center.x + a / centers_distance * (circle2.center.x - circle1.center.x);
		tmppnt.y = circle1.center.y + a / centers_distance * (circle2.center.y - circle1.center.y);
		Point first_intersection, second_intersection;
		first_intersection.x = tmppnt.x + h / centers_distance * (circle2.center.y - circle1.center.y);
		first_intersection.y = tmppnt.y - h / centers_distance * (circle2.center.x - circle1.center.x);
		second_intersection.x = tmppnt.x - h / centers_distance * (circle2.center.y - circle1.center.y);
		second_intersection.y = tmppnt.y + h / centers_distance * (circle2.center.x - circle1.center.x);
		if (first_intersection == second_intersection)
			return { first_intersection };
		else
			return { first_intersection, second_intersection };
	}
}

bool Circle::is_in(Point p) const {
	return (distance(center, p) <= radius);
}