#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "point.h"

class Circle
{
private:
	Point center;
	double radius;
public:
	Circle(double, double, double);
	Circle();
	// setters
	void set(const Point, const double);
	void set(const Point, const Point);
    void set_radius(const double _radius) { radius = _radius; }
	void set_center(const Point _center) { center = _center; }
	void set_centerx(const double _x) { center.x = _x; }
	void set_centery(const double _y) { center.y = _y; }

	// get circle parameters functions
	double get_radius() const { return radius; }
	Point get_center() const { return center; }
	double circumference() const { return 2 * M_PI * radius; }
	double area() const { return M_PI * radius * radius; }

	// Some circle special functions
	
	// return 1 if point lies inside circle, 0 otherwise
	bool is_in(const Point p) const { return (distance(center, p) <= radius); }

	// get the intersection points of two circles
	friend std::vector<Point> intersections(const Circle, const Circle);

	// Output circle
	friend std::ostream& operator<<(std::ostream& os, const Circle& c);
};