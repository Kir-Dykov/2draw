#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "point.h"

class Circle
{
private:
	Point c;
	double r;

public:
	Circle(double, double, double);
	Circle();
	Circle(const Circle& other) {
		c = other.center;
		r = other.radius;
	}
	Circle& operator =(const Circle& other) {
		c = other.center;
		r = other.radius;
		return *this;
	}

	// "getters"
	const Point& center = c;
	const double& radius = r;

	// Setters
	// set the circle by center point and radius
	void set(const Point, const double);
	// set the circle by centerpoint and a point on a circle
	void set(const Point, const Point);
    void set_radius(const double _radius) { r = _radius; }
	void set_center(const Point _center) { c = _center; }
	void set_centerx(const double _x) { c.x = _x; }
	void set_centery(const double _y) { c.y = _y; }

	double circumference() const { return 2 * M_PI * r; }
	double area() const { return M_PI * r * r; }

	// Some circle special functions
	// return 1 if point lies inside circle, 0 otherwise
	bool is_in(const Point p) const { return (c.distance(p) <= r); }

	// get the intersection points of two circles
	std::vector<Point> intersections(const Circle) const;

};

std::ostream& operator<<(std::ostream&, const Circle&);