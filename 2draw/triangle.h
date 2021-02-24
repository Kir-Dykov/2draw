#pragma once
#include "point.h"
#include "line.h"
using namespace std;

class triangle
{
public:
	point p1, p2, p3;
	void set(point, point, point); // sets the triangle using 3 points
	Line find_median(point); // finds the equation for the median taken from the chosen triangle vertex
	double triangle_perimeter(); // find the perimeter of the triangle
	double triangle_area(); // finds the area of the triangle
	int triangle_type(); // finds the type of the triangle (right, obtise, acute)
	bool operator==(triangle);
};