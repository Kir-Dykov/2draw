#pragma once
#include <iostream>
#include "vector.h"
using namespace std;

class Point
{
public:
	double x, y;	//koordinati x y

	void set(double, double);   //zadanie tochki:													p.set_point()
	int find_quarter();    //nahozhdenie chetverti v kotoroy nahoditsa tochka:						p.find_quarter() 

	Point() { x = 0; y = 0; }
	Point(double _x, double _y) { x = _x; y = _y; }

	bool operator==(const Point p) { return x == p.x && y == p.y; }

	Vector operator-(Point other) { return Vector(x - other.x, y - other.y); } // Vector conntecting two points
};

std::ostream& operator<<(std::ostream& os, const Point& p);

double distance(const Point p1, const Point p2); //vichislenie rasstoyaniya mezhdy tochkami:				r = point_distance(p1, p2)

Point sym_point_x(const Point);   //sozdanie tochki, simmetrichnoi zadannoi otnositelno osi Ox:			q = sym_point_x(p)
Point sym_point_y(const Point);   //sozdanie tochki, simmetrichnoi zadannoi otnositelno osi Îy:			q = sym_point_y(p)
Point middlepoint(const Point, Point);