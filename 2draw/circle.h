#pragma once
#include "point.h"
using namespace std;

class Circle
{
public:
	Point center;
	double radius;
	void set_circle(Point, double); // set a circle by its center and radius

	double get_radius();
	double get_centerx();
	double get_centery();
	void cout_circle();
	double get_length();
	double get_square();
	double get_diameter();
};