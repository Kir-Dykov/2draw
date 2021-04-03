#pragma once
#include <iostream>
#include "vector.h"

class Point {
private:
	double x, y;

	// Friends
	friend class Line;
	friend class Circle;
	friend class Triangle;
	friend class Polygon;
	friend std::ostream& operator<<(std::ostream&, const Point&);
public:
	Point() { x = 0; y = 0; }
	Point(double _x, double _y) { x = _x; y = _y; }
	// set the point by x and y
	void set(double, double);

	// Other functions
	// distance between 2 points
	double distance(const Point); 
	// the middle point between 2 points
	Point middlepoint(const Point);
	// find the quarter where the point is lying
	int find_quarter();

	// Operators
	bool operator==(const Point p) { return x == p.x && y == p.y; }
	Vector operator-(const Point other) { return Vector(x - other.x, y - other.y); } // Vector conntecting two points
};

std::ostream& operator<<(std::ostream& os, const Point& p) { os << "(" << p.x << ", " << p.y << ")"; return os; }