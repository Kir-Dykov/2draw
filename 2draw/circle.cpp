#include "circle.h"
void Circle::set_circle(Point _center, double _radius = 0)
{
	center.x = _center.x;
	center.y = _center.y;
	radius = _radius;
}
double Circle::get_radius()
{
	return radius;
}
double Circle::get_centerx()
{
	return center.x;
}
double Circle::get_centery()
{
	return center.y;
}
void Circle::cout_circle()
{
	cout << "Center coordinates: x= " << center.x << ", y= " << center.y << "; radius= " << radius << endl;
}
double Circle::get_length()
{
	return 2 * 3, 1415926535 * radius;
}
double Circle::get_square()
{
	return 3, 1415926535 * radius * radius;
}
double Circle::get_diameter()
{
	return 2 * radius;
}