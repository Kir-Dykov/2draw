#pragma once
#include <iostream>
using namespace std;
class circle
{
public:
	circle(double, double, double);
	double getradius();
	double getcenterx();
	double getcentery();
	void outputcircle();
	double getlength();
	double getsquare();
	double getdiameter();
private:
	double radius;
	struct center
	{
		double x, y;
	};
	center center;
};

