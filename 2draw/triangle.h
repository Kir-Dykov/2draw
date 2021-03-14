#pragma once
#include "point.h"
#include "line.h"
#include "circle.h"
#include "tetragon.h"
#include "vector.h"
#include <string>

class Triangle
{
public:
	void set_triangle(Point, Point, Point); // sets the Triangle using 3 points

	// Angles and sides
	double get_triangle_angle(int); // finds one of the Triangle's angles
	double get_triangle_side(int, int); // finds one of the sides using the points that define it

	bool operator==(Triangle);
	// Some triangular properties
	double triangle_perimeter(); // finds the perimeter of the Triangle
	double triangle_area(); // finds the area of the Triangle
	int triangle_type(); // finds the type of the Triangle (right - 1, obtise - 2, acute - 3)

	// Triangle and a circle
	Circle get_circumcircle();
	Circle get_inscribed_circle();

	// Median, bisectix and altitude
	Line get_median(int); // finds the equation for the median taken from the chosen Triangle vertex
	Line get_bisectrix(int); // finds the equation for the bisectrix taken from the chosen Triangle vertex
	Line get_altitude(int); // finds the equation for the altitude taken from the chosen Triangle vertex

	// Subsidary functions
	void num_to_point(int, Point&); // converts 1 to p1, 2 to p2, 3 to p3
	void point_reassignment(Point, Point, Point, Point, Point&, Point&); // if we have received a main point p, this func changes a1 and a2 to other points of a Triangle

	// Two triangles
	bool are_congruent(Triangle); // checks if two triangles are congruent (=)
	bool are_similar(Triangle); // checks if two triangles are similar (~)

	// Triangle and a point
	bool point_triangle_belonging(Point); // returns 1 if point belongs to triangle and 0 otherwise

private:
	Point p1, p2, p3;
	
	// Friends
	friend double Tetragon::tetragon_area();
};