#pragma once
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
	void set(Point _center, double _radius);
	void set(Point _center, Point other);
    void set_radius(double);
	void set_center(Point);
	void set_centerx(double);
	void set_centery(double);

	// Get circle parameters functions
	double get_radius() const;
	Point get_center() const;
	double circumference() const;
	double area() const;

	// Some circle special functions
	
	// return 1 if point lies inside circle, 0 otherwise
	bool is_in(Point) const;

	// get the intersection points of two circles
	friend std::vector<Point> intersections(Circle, Circle);

	// Output circle
	friend std::ostream& operator<<(std::ostream& os, Circle& c);
};