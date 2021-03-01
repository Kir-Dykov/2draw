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
	double get_dist_pnttocir(Point, Circle);	// get the distance from a point to a circle
	void find_cros_2circlespnts(Circle, Circle);// get the intersection points of two circles
	void cout_circle(Circle);
	double get_length();
	double get_square();
	double get_diameter();
private:
	Point center;
	double radius;
};