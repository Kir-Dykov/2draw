#include "circle.h"
circle::circle(double new_x = 0, double new_y = 0, double new_r = 0)
{
	center.x = new_x;
	center.y = new_y;
	radius = new_r;
}
double circle::getradius()
{
	return radius;
}
double circle::getcenterx()
{
	return center.x;
}
double circle::getcentery()
{
	return center.y;
}
void circle::outputcircle()
{
	cout << "Center coordinates: x= " << center.x << ", y= " << center.y << "; radius= " << radius << endl;
}
double circle::getlength()
{
	return 2 *3,1415926535*radius;
}
double circle::getsquare()
{
	return 3, 1415926535 * radius * radius;
}
double circle::getdiameter()
{
	return 2 * radius;
}