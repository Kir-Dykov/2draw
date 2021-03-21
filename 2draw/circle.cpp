#include "circle.h"

void Circle::set(Point _center, double _radius = 0) {
	center.x = _center.x;
	center.y = _center.y;
	radius = _radius;
}

void Circle::set(Point _center, Point secondp) {
	center.x = _center.x;
	center.y = _center.y;
	radius = point_distance(_center, secondp);
}

void Circle::set_radius(double _radius) {
	radius = _radius;
}

double Circle::get_radius() const {
	return radius;
}

double Circle::get_dist_pnttocir(Point secondp, Circle _circle) {
	return point_distance(_circle.get_center(), secondp) - _circle.get_radius();
}

Point Circle::get_center() const {
	return center;
}

void Circle::set_center(Point _center) {
	center = _center;
}

void Circle::set_centerx(double _x) {
	center.x = _x;
}
void Circle::set_centery(double _y) {
	center.y = _y;
}

std::ostream& operator<<(std::ostream& os, Circle& c) {
	os << "the circle with radius of " << c.radius << " and center at " << c.center;
	return os;
}

double Circle::circumference() {
	return 2 * 3,1415926535 * radius;
}

double Circle::area() {
	return 3,1415926535 * radius * radius;
}


std::vector<Point> intersections(Circle circle1, Circle circle2) {
	// Algorithm: https://planetcalc.ru/8098/?license=1
	double circlesdist = point_distance(circle1.center, circle2.center);
	if (circlesdist == 0 && circle1.radius == circle2.radius) {		// coincide
		return { circle1.center, circle2.center };
	}
	else if (circlesdist > circle1.radius + circle2.radius) {			// don't intersect
		return vector<Point>(0);
	}
	else if (circlesdist < abs(circle1.radius - circle2.radius)) {	// one to the other
		return vector<Point>(0);
	}
	else // touch or intersect at two points
	{
		double a = (circle1.get_radius() * circle1.get_radius() - circle2.get_radius() * circle2.get_radius() + \
			circlesdist * circlesdist) / (2 * circlesdist);
		double h = sqrt(circle1.get_radius() * circle1.get_radius() - a * a);
		Point tmppnt;
		tmppnt.x = circle1.center.x + a / circlesdist * (circle2.center.x - circle1.center.x);
		tmppnt.y = circle1.center.y + a / circlesdist * (circle2.center.y - circle1.center.y);
		Point frstinterspnt, scndinterspnt;
		frstinterspnt.x = tmppnt.x + h / circlesdist * (circle2.center.y - circle1.center.y);
		frstinterspnt.y = tmppnt.y - h / circlesdist * (circle2.center.x - circle1.center.x);
		scndinterspnt.x = tmppnt.x - h / circlesdist * (circle2.center.y - circle1.center.y);
		scndinterspnt.y = tmppnt.y + h / circlesdist * (circle2.center.x - circle1.center.x);
		if (frstinterspnt == scndinterspnt)
			return { frstinterspnt };
		else
			return { frstinterspnt, scndinterspnt };
	}
}

bool Circle::is_in(Point p) const {
	return (point_distance(center, p) <= radius);
}