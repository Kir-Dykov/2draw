#pragma once
#include "line.h"
#include "circle.h"
#include "vector.h"
#include <string>

class Triangle
{
private:
	Point p1, p2, p3;
public:
	Triangle() {};
	Triangle(Point, Point, Point);
	// Triangle existence function
	bool exist(Point, Point, Point);

	// sets the Triangle using 3 points
	void set(const Point, Point, Point);

	// Angles and sides
	// finds one of the Triangle's angles
	double get_angle(const int) const;
	// finds one of the sides using the points that define it
	double get_side(const int, const int) const;

	bool operator==(const Triangle) const;

	// Some triangular properties
	// finds the perimeter of the Triangle
	double perimeter() const;
	// finds the area of the Triangle
	double area() const;
	// finds the type of the Triangle (right - 1, obtise - 2, acute - 3)
	int triangle_type() const;

	// Triangle and a circle
	Circle get_circumcircle() const;
	Circle get_inscribed_circle() const;

	// Median, bisectix, altitude, midpoint, perp. bisector
	// finds the equation for the median taken from the chosen Triangle vertex
	Line get_median(const int) const;
	// finds the equation for the bisectrix taken from the chosen Triangle vertex
	Line get_bisectrix(const int) const;
	// finds the equation for the altitude taken from the chosen Triangle vertex
	Line get_altitude(const int) const;
	// finds the equation for the midline taken for the side laying opposite the chosen Triangle vertex
	Line get_midline(const int) const;
	// finds the equation for the perpendicular bisector taken for the side laying opposite the chosen Triangle vertex
	Line get_perp_bis(const int) const;

	// Subsidary functions
	// converts 1 to p1, 2 to p2, 3 to p3
	void num2point(const int, Point&) const;
	// if we have received a main point p, this func changes a1 and a2 to other points of a Triangle
	void point_reassignment(Point, Point&, Point&) const;

	// Triangle and a point
	// returns 1 if point belongs to triangle and 0 otherwise
	bool is_in(const Point);

	// Friends
	friend std::ostream& operator<<(std::ostream& os, Triangle& t);
};