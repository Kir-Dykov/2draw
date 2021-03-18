#pragma once
#include "point.h"

class Circle
{
public:
	// Set circle functions
	// set a circle by point and radius
	void set_circle(Point, double);
	// set a circle from two points
	void set_circleby2p(Point, Point);
    void set_radius(double);
	void set_centerx(double);
	void set_centery(double);

	// Get circle parameters functions
	double get_radius() const;
	Point get_center() const;
	double get_centerx() const;
	double get_centery() const;
	static double get_length(Circle);
	static double get_square(Circle);
	static double get_diameter(Circle);

	// Some circle special functions
	// get the distance from a point to a circle
	static double get_dist_pnttocir(Point, Circle);
	// get the intersection points of two circles
	static void find_cros_2circlespnts(Circle, Circle);
	// returns 1 if point belongs to circle and 0 otherwise
	bool point_circle_belonging(Point) const; 

	// Output circle
	static void cout_circle(Circle);

private:
	Point center;
	double radius;
};