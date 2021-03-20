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
	// sets the Triangle using 3 points
	void set(Point, Point, Point); 
	Triangle() {};
	Triangle(Point, Point, Point);
	// Angles and sides
	// finds one of the Triangle's angles
	double get_triangle_angle(int);
	// finds one of the sides using the points that define it
	double get_triangle_side(int, int);

	bool operator==(Triangle);

	// Some triangular properties
	// finds the perimeter of the Triangle
	double perimeter() const;
	// finds the area of the Triangle
	double area();
	// finds the type of the Triangle (right - 1, obtise - 2, acute - 3)
	int triangle_type();

	// Triangle and a circle
	Circle get_circumcircle();
	Circle get_inscribed_circle();

	// Median, bisectix, altitude, midpoint, perp. bisector
	// finds the equation for the median taken from the chosen Triangle vertex
	Line get_median(int);
	// finds the equation for the bisectrix taken from the chosen Triangle vertex
	Line get_bisectrix(int);
	// finds the equation for the altitude taken from the chosen Triangle vertex
	Line get_altitude(int);
	// finds the equation for the midline taken for the side laying opposite the chosen Triangle vertex
	Line get_midline(int);
	// finds the equation for the perpendicular bisector taken for the side laying opposite the chosen Triangle vertex
	Line get_perp_bis(int);

	// Subsidary functions
	// converts 1 to p1, 2 to p2, 3 to p3
	void num_to_point(int, Point&);
	// if we have received a main point p, this func changes a1 and a2 to other points of a Triangle
	void point_reassignment(Point, Point, Point, Point, Point&, Point&);

	// Two triangles
	// checks if two triangles are congruent (=)
	bool are_congruent(Triangle);
	// checks if two triangles are similar (~)
	bool are_similar(Triangle);

	// Triangle and a point
	// returns 1 if point belongs to triangle and 0 otherwise
	bool is_in(Point);

private:
	Point p1, p2, p3;
	
	// Friends
	friend double Tetragon::tetragon_area();
	friend std::ostream& operator<<(std::ostream& os, Triangle& t);
};