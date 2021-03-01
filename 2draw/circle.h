#pragma once
#include "point.h"

class Circle
{
public:
	void set_circle(Point, double);		// set a circle by point and radius
	void set_circleby2p(Point, Point);	// set a circle from two points

	void set_radius(double);
	double get_radius();
	Point get_center();
	void set_centerx(double);
	double get_centerx();
	void set_centery(double);
	double get_centery();
	static double get_dist_pnttocir(Point, Circle);	// get the distance from a point to a circle
	static void find_cros_2circlespnts(Circle, Circle);// get the intersection points of two circles
	static void cout_circle(Circle);
	static double get_length(Circle);
	static double get_square(Circle);
	static double get_diameter(Circle);
private:
	Point center;
	double radius;
};