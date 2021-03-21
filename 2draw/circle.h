#pragma once
#include <vector>
#include "point.h"

class Circle
{
public:
	// Set circle functions
	// set a circle by point and radius
	void set(Point, double);
	// set a circle from two points
	void set(Point, Point);
    void set_radius(double);
	void set_center(Point);
	void set_centerx(double);
	void set_centery(double);

	// Get circle parameters functions
	double get_radius() const;
	Point get_center() const;
	double circumference();
	double area();

	// Some circle special functions
	// get the distance from a point to a circle
	static double get_dist_pnttocir(Point, Circle);
	
	// returns 1 if point belongs to circle and 0 otherwise
	bool is_in(Point) const;

	// get the intersection points of two circles
	friend vector<Point> intersections(Circle, Circle);

	// Output circle
	friend std::ostream& operator<<(std::ostream& os, Circle& c);

private:
	Point center;
	double radius;
};