#pragma once
#include <iostream>
#include "vector.h"
#include "object.h"

class Point : public Object {
public:
	double x, y;
	Point() { x = 0; y = 0; }
	Point(double _x, double _y) { x = _x; y = _y; }
	Point(const Point& other) { x = other.x; y = other.y; }
	Point& operator=(const Point& other) {
		x = other.x;
		y = other.y;
		return *this;
	}
	// set the point by x and y
	void set(double, double);

	// Other functions
	// distance between 2 points
	
	// the middle point between 2 points
	Point middlepoint(const Point&) const;
	// find the quarter where the point is lying
	int find_quarter() const;

	// Operators
	bool operator==(const Point& p) const { return x == p.x && y == p.y; }
	
	Point operator+(const Vector& s) const { return Point(x + s.x, y + s.y); }
	Point operator+=(const Vector& s) {
		x += s.x;
		y += s.y;
		return *this;
	}

	void Draw() const;

	// Vector connecting two points
	friend Vector operator-(const Point& to, const Point& from) { return Vector(to.x - from.x, to.y - from.y); } 
	
	friend std::ostream& operator<<(std::ostream&, const Point&);
};

class PointSet : public Object {
	vector<Point> v;

	void push_back(const Point& p) { v.push_back(p); }

	void Draw() const {
		for (size_t i = 0; i < v.size(); i++) {
			v[i].Draw();
		}
	}
};

inline double distance(const Point& p, const Point& q) {
	return sqrt((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y));
};