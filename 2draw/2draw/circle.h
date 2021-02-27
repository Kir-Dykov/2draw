#pragma once
#include <iostream>
using namespace std;

class circle
{
public:
	circle(double, double, double);
	double get_radius();
	double get_centerx();
	double get_centery();
	void cout_circle();
	double get_length();
	double get_square();
	double get_diameter();
private:
	double radius;
	struct center
	{
		double x, y;
	};
	center center;
};

