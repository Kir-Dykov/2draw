#include "circle.h"
void circle::set_circle(point _center, double _radius = 0)
{
	center.x = _center.x;
	center.y = _center.y;
	radius = _radius;
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