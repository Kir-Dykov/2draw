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
void Circle::set_radius(double _radius)
{
	radius = _radius;
}
double Circle::get_radius()
{
	return radius;
}
double Circle::get_dist_pnttocir(Point secondp, Circle _circle)
{
	return point_distance(_circle.get_center(), secondp) - _circle.get_radius();
}
Point Circle::get_center()
{
	return center;
}
void Circle::set_centerx(double _centerx)
{
	center.x = _centerx;
}
double Circle::get_centerx()
{
	return center.x;
}
void Circle::set_centery(double _centery)
{
	center.y = _centery;
}
double Circle::get_centery()
{
	return center.y;
}
void Circle::cout_circle(Circle _circle)
{
	std::cout << "\nCenter coordinates: x = " << _circle.get_centerx() << ", y = " \
		<< _circle.get_centery() << "; radius = " << _circle.get_radius();
}
double Circle::get_length(Circle _circle)
{
	return 2 * 3, 1415926535 * _circle.get_radius();
}
double Circle::get_square(Circle _circle)
{
	return 3, 1415926535 * _circle.get_radius() * _circle.get_radius();
}
double Circle::get_diameter(Circle _circle)
{
	return 2 * _circle.get_radius();
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
		double h = sqrt(_circlef.get_radius() * _circlef.get_radius() - a * a);
		Point tmppnt;
		tmppnt.x = _circlef.get_centerx() + a / circlesdist * (_circles.get_centerx() - _circlef.get_centerx());
		tmppnt.y = _circlef.get_centery() + a / circlesdist * (_circles.get_centery() - _circlef.get_centery());
		Point frstinterspnt, scndinterspnt;
		frstinterspnt.x = tmppnt.x + h / circlesdist * (_circles.get_centery() - _circlef.get_centery());
		frstinterspnt.y = tmppnt.y - h / circlesdist * (_circles.get_centerx() - _circlef.get_centerx());
		scndinterspnt.x = tmppnt.x - h / circlesdist * (_circles.get_centery() - _circlef.get_centery());
		scndinterspnt.y = tmppnt.y + h / circlesdist * (_circles.get_centerx() - _circlef.get_centerx());
		if (frstinterspnt == scndinterspnt)
			std::cout << "\nIntesection point: " << frstinterspnt;
		else
			std::cout << "\nFirst intersection point: " << frstinterspnt \
			<< " Second intersection point: " << scndinterspnt;
	}
}

bool Circle::point_circle_belonging(Point p)
{
	return (point_distance(center, p) == radius);
}