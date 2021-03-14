#pragma once
#include "point.h"

class Circle
{
public:
	// Set circle functions
	void set_circle(Point, double);		// set a circle by point and radius
	void set_circleby2p(Point, Point);	// set a circle from two points
    void set_radius(double);
	void set_centerx(double);
	void set_centery(double);

	// Get circle parameters functions
	double get_radius();
	Point get_center();
	double get_centerx();
	double get_centery();
	static double get_length(Circle);
	static double get_square(Circle);
	static double get_diameter(Circle);

	// Some circle special functions
	static double get_dist_pnttocir(Point, Circle);	// get the distance from a point to a circle
	static void find_cros_2circlespnts(Circle, Circle);// get the intersection points of two circles
	bool point_circle_belonging(Point); // returns 1 if point belongs to circle and 0 otherwise

	// Output circle
	static void cout_circle(Circle);

private:
	Point center;
	double radius;
};