#pragma once
#include <iostream>
#include "vector.h"

class Point {
private:
	// Friends
	
public:
	double x, y;
	Point() { x = 0; y = 0; }
	Point(double _x, double _y) { x = _x; y = _y; }
	Point& operator=(const Point& other) {
		x = other.x;
		y = other.y;
		return *this;
	}
	// set the point by x and y
	void set(double, double);

	// Other functions
	// distance between 2 points
	double distance(const Point) const; 
	// the middle point between 2 points
	Point middlepoint(const Point) const;
	// find the quarter where the point is lying
	int find_quarter() const;

	// Operators
	bool operator==(const Point p) const { return x == p.x && y == p.y; }
	
	Point operator+(const Vector s) const { return Point(x + s.x, y + s.y); }
	Point operator+=(Vector s) {
		x += s.x;
		y += s.y;
		return *this;
	}
	friend Vector operator-(const Point to, const Point from) { return Vector(to.x - from.x, to.y - from.y); } // Vector connecting two points
	
	friend class Line;
	friend class Circle;
	friend class Triangle;
	friend class Polygon;
	friend std::ostream& operator<<(std::ostream&, const Point&);
};

