#include "circle.h"
circle::circle(double new_x = 0, double new_y = 0, double new_r = 0)
{
	center.x = new_x;
	center.y = new_y;
	radius = new_r;
}
double circle::get_radius()
{
	return radius;
}
double circle::get_centerx()
{
	return center.x;
}
double circle::get_centery()
{
	return center.y;
}
void circle::cout_circle()
{
	cout << "Center coordinates: x= " << center.x << ", y= " << center.y << "; radius= " << radius << endl;
}
double circle::get_length()
{
	return 2 * 3, 1415926535 * radius;
}
double circle::get_square()
{
	return 3, 1415926535 * radius * radius;
}
double circle::get_diameter()
{
	return 2 * radius;
}