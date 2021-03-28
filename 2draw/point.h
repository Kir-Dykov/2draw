#pragma once
#include <iostream>
#include "vector.h"
using namespace std;

class Point
{
public:
	double x, y;	//koordinati x y

	void set(double, double);   //zadanie tochki:													p.set()
	int find_quarter();    //nahozhdenie chetverti v kotoroy nahoditsa tochka:						p.find_quarter() 

	void cout_point();     //vivod koordinat tochki d konsol:										p.cout_point()
	
	Point() { x = 0; y = 0; }
	Point(double _x, double _y) { x = _x; y = _y; }
	Point& operator =(const Point& other);

	bool operator==(Point p) {return x == p.x && y == p.y;}

	Vector operator-(Point other) { return Vector(x - other.x, y - other.y); } // Vector conntecting two points
	Point operator+=(Vector s) { x += s.getx(); y += s.gety(); return *this; }
	Point operator+(Vector s) {return Point(x + s.getx(), y + s.gety()); }
};

std::ostream& operator<<(std::ostream& os, const Point& p);

double distance(Point p1, Point p2); //vichislenie rasstoyaniya mezhdy tochkami:				r = distance(p1, p2)

Point sym_point_x(Point);   //sozdanie tochki, simmetrichnoi zadannoi otnositelno osi Ox:			q = sym_point_x(p)
Point sym_point_y(Point);   //sozdanie tochki, simmetrichnoi zadannoi otnositelno osi �y:			q = sym_point_y(p)
Point middlepoint(Point, Point);