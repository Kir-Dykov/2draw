#include "circle.h"
void Circle::set_circle(Point _center, double _radius = 0)
{
	center.x = _center.x;
	center.y = _center.y;
	radius = _radius;
}
void Circle::set_circleby2p(Point _center, Point secondp)
{
	center.x = _center.x;
	center.y = _center.y;
	radius = point_distance(_center, secondp);
}
double Circle::get_radius()
{
	return radius;
}
double Circle::get_dist_pnttocir(Point secondp, Circle _circle)
{
	return point_distance(_circle.center, secondp) - radius;
}
double Circle::get_centerx()
{
	return center.x;
}
double Circle::get_centery()
{
	return center.y;
}
void Circle::cout_circle(Circle _circle)
{
	std::cout << "\nCenter coordinates: x= " << _circle.get_centerx() << ", y= " \
		<< _circle.get_centery() << "; radius= " << _circle.get_radius();
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
void Circle::find_cros_2circlespnts(Circle _circlef, Circle _circles)
{
	// Algorithm: https://planetcalc.ru/8098/?license=1
	double circlesdist = point_distance(_circlef.center, _circles.center);
	if (circlesdist == 0 && _circlef.get_radius() == _circles.get_radius()) // coincide
	{
		std::cout << "\nThe circles coincide";
	}
	else if (circlesdist > _circlef.get_radius() + _circles.get_radius())   // don't intersect
	{
		std::cout << "\nThe circles don't intersect";
	}
	else if (circlesdist < abs(_circlef.get_radius() - _circles.get_radius()))	// one to the other
	{
		std::cout << "\nOne circle is in the other";
	}
	else // touch or intersect at two points
	{
		double a = (_circlef.get_radius() * _circlef.get_radius() - _circles.get_radius() * _circles.get_radius() + \
			circlesdist * circlesdist) / (2 * circlesdist);
		double h = sqrt(radius * radius - a * a);
		Point tmppnt;
		tmppnt.x = center.x + a / circlesdist * (_circles.get_centerx() - _circlef.get_centerx());
		tmppnt.y = center.y + a / circlesdist * (_circles.get_centery - _circlef.get_centery());
		Point frstinterspnt, scndinterspnt;
		frstinterspnt.x = tmppnt.x + h / circlesdist * (_circles.get_centery - _circlef.get_centery());
		frstinterspnt.y = tmppnt.y - h / circlesdist * (_circles.get_centerx - _circlef.get_centerx());
		scndinterspnt.x = tmppnt.x - h / circlesdist * (_circles.get_centery - _circlef.get_centery());
		scndinterspnt.y = tmppnt.y + h / circlesdist * (_circles.get_centerx - _circlef.get_centerx());
		if (frstinterspnt == scndinterspnt)
			std::cout << "\nIntesection point: " << frstinterspnt;
		else
			std::cout << "\nFirst intersection point: " << frstinterspnt \
			<< " Second intersection point: " << scndinterspnt;
	}
}