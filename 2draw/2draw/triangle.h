#pragma once
#include "point.h"
#include "line.h"

class triangle
{
public:
	point p1, p2, p3;

	void set(point, point, point); // sets the triangle using 3 points

	double triangle_angle(point); // finds one of the triangle's angles

	double triangle_perimeter(); // find the perimeter of the triangle
	double triangle_area(); // finds the area of the triangle

	int triangle_type(); // finds the type of the triangle (right, obtise, acute)

	Line get_median(point); // finds the equation for the median taken from the chosen triangle vertex
	Line get_bisectrix(point); // finds the equation for the bisectrix taken from the chosen triangle vertex
	Line get_altitude(point);// finds the equation for the altitude taken from the chosen triangle vertex

	bool operator==(triangle);
};