#pragma once
#include "line.h"
#include "circle.h"
#include "vector.h"
#include <string>

class Triangle
{
private:
	Point p1, p2, p3;

	// Friends
	friend std::ostream& operator<<(std::ostream& os, Triangle& t);
public:
	Triangle() { p1.x = 0; p2.x = 1; p3.x = 0; p1.y = 0; p2.y = 0; p3.y = 1; };
	Triangle(Point _p1, Point _p2, Point _p3) { p1 = _p1; p2 = _p2; p3 = _p3; };
	Triangle(const Triangle& other) { p1 = other.p1; p2 = other.p2; p3 = other.p3; };
	// Triangle existence function
	bool exist(Point, Point, Point) const;
	// sets the Triangle using 3 points
	void set(const Point, Point, Point);

	// "getters"
	const Point& first_vertex = p1;
	const Point& second_vertex = p2;
	const Point& third_vertex = p3;

	// Angles and sides
	// finds one of the Triangle's angles
	double get_angle(const Point) const;
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
	/*Circle get_excircle(const Point) const;*/

	// Median, bisectix, altitude, midpoint, perp. bisector
	// finds the equation for the median taken from the chosen Triangle vertex
	Line get_median(const Point) const;
	// finds the equation for the bisectrix taken from the chosen Triangle vertex
	Line get_bisectrix(const Point) const;
	// finds the equation for the altitude taken from the chosen Triangle vertex
	Line get_altitude(const Point) const;
	// finds the equation for the midline taken for the side laying opposite the chosen Triangle vertex
	Line get_midline(const Point) const;
	// finds the equation for the perpendicular bisector taken for the side laying opposite the chosen Triangle vertex
	Line get_perp_bis(const Point) const;

	// Subsidary functions
	// converts 1 to p1, 2 to p2, 3 to p3
	void num2point(const int, Point&) const;
	// if we have received a main point p, this func changes a1 and a2 to other points of a Triangle
	void point_reassignment(const Point, Point&, Point&) const;

	// Triangle and a point
	// returns 1 if point belongs to triangle and 0 otherwise
	bool is_in(const Point) const;
};

std::ostream& operator<<(std::ostream&, Triangle&);