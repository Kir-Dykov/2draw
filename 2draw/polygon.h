#pragma once
#include <vector>
#include "point.h"
#include "triangle.h"
#include "vector.h"

//polygon is defined by series of points
//each pair of adjacent points defines an edge of polygon
class Polygon {

private:
	std::vector<Point> vertexes;

public:

	//constructors
	Polygon() {};
	Polygon(initializer_list<Point> l) : vertexes(l) {};
	Polygon(const Polygon& other) { vertexes = other.vertexes; }
	Polygon& operator=(const Polygon& other) {
		vertexes = other.vertexes;
		return *this;
	}

	//appends
	void append(const Point& new_point) { vertexes.push_back(new_point); }
	void append(initializer_list<Point> l) { vertexes.insert(vertexes.end(), l.begin(), l.end()); }

	//operators
	inline Point operator [] (unsigned int idx) const { return vertexes[idx]; }
	Polygon operator+=(const Vector& s) {
		for (int i = 0; i < vertexes.size(); i++) vertexes[i] += s;
		return *this;
	}

	// @todo 
	//bool is_selfx();

	//rotate around center of mass by /angle/ given in radians
	void rotate(double angle);
	void rotate(const Point& center, double angle);

	//properties
	bool is_convex() const;
	Point center_of_mass() const;
	double area() const;
	bool is_in(const Point&) const; // returns 1 if point belongs to polygon and 0 otherwise

	//takes array of points, returns their convex hull
	friend Polygon convex_hull(const vector<Point>& points);
	//prints coordinates of each vertex
	friend std::ostream& operator<<(std::ostream& os, const Polygon& p);
};

Polygon convex_hull(const vector<Point>& f);
std::ostream& operator<<(std::ostream& os, const Polygon& p);
