#pragma once
#include "point.h"
#include "line.h"
#include "circle.h"
#include <string>

class triangle
{
public:
	point p1, p2, p3;

	void set_triangle(point, point, point); // sets the triangle using 3 points

	// Angles and sides
	double get_triangle_angle(int); // finds one of the triangle's angles
	double get_triangle_side(int, int); // finds one of the sides using the points that define it

	// Some triangular properties
	double triangle_perimeter(); // finds the perimeter of the triangle
	double triangle_area(); // finds the area of the triangle
	int triangle_type(); // finds the type of the triangle (right - 1, obtise - 2, acute - 3)

	// Triangle and a circle
	circle get_circumcircle();
	circle get_inscribed_circle();

	// Median, bisectix and altitude
	Line get_median(int); // finds the equation for the median taken from the chosen triangle vertex
	Line get_bisectrix(int); // finds the equation for the bisectrix taken from the chosen triangle vertex
	Line get_altitude(int); // finds the equation for the altitude taken from the chosen triangle vertex

	bool operator==(triangle);

	// Subsidary functions
	string line_error_catch(Line(*get_function)(int), int); // incorrect input protection for get_median, bisectrix and altitude
	string double_error_catch(double(*get_function)(int), int); // incorrect input protection for get_angle
	void num_to_point(int, point&); // converts 1 to p1, 2 to p2, 3 to p3
};

// Two triangles
bool are_congruent(triangle, triangle); // checks if two triangles are congruent (=)
bool are_similar(triangle, triangle); // checks if two triangles are similar (~)