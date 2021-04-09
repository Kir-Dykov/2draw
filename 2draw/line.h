#pragma once
#include "point.h"

class Line
{
private:
	Point p1, p2; 					
	double a, b, c;	

public:
	Line() { p1.x = 0; p2.x = 1; p1.y = 0; p2.y = 1; a = 1; b = -1; c = 0; };
	Line(Point _p1, Point _p2) { p1 = _p1; p2 = _p2; a = p1.y - p2.y; b = p2.x - p1.x; c = p1.x * p2.y - p2.x * p1.y; };
	Line(double _a, double _b, double _c) { a = _a; b = _b; c = _c; p1.x = -c / a; p1.y = 0; p2.x = -(b + c) / a; p2.y = 1; };
	// Setters
	// set line by 2 points
	void set(Point, Point);
	// set line by coeffietients of its equation
	void set(double, double, double);
	// set the C coeffitient of line
	void set_argument_c(double _c) { c = _c; }

	// Getters
	// angle between line and Ox in radians
	double get_angle_rad() const;
	// ... in degrees
	double get_angle_deg() const;

	// Other functions
	// are lines parallel
	bool is_parallel_to(const Line L) const;
	// point line belonging
	bool point_on_Line(const Point) const;
	// angle between 2 lines in radians
	double get_twoLines_radangle(const Line) const;
	// ... in degrees
	double get_twoLines_degangle(const Line) const;
	// finding point halfplane 1 - above the line, -1 - below the line, 0 - on a line
	int find_halfplane(const Point) const;
	// drawing a line perpendicular to the given line
	Line perpendicular() const;
	// finds the intersection point of two lines
	Point intersection_point_lines(const Line) const;
	// Operators
	bool operator==(const Line) const;

	// Friends
	friend class Point;
	friend class Circle;
	friend class Triangle;
	friend class Polygon;
	friend std::ostream& operator<<(std::ostream&, const Line&);
};