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
	void set(Point, double);
	void set(Point, Point);
    void set_radius(double _radius) { radius = _radius; }
	void set_center(Point _center) { center = _center; }
	void set_centerx(double _x) { center.x = _x; }
	void set_centery(double _y) { center.y = _y; }

	// get circle parameters functions
	double get_radius() const { return radius; }
	Point get_center() const { return center; }
	double circumference() const { return 2 * M_PI * radius; }
	double area() const { return M_PI * radius * radius; }

	// Some circle special functions
	
	// return 1 if point lies inside circle, 0 otherwise
	bool is_in(Point p) const { return (point_distance(center, p) <= radius); }

	// get the intersection points of two circles
	friend std::vector<Point> intersections(Circle, Circle);

	// Output circle
	friend std::ostream& operator<<(std::ostream& os, Circle& c);
};