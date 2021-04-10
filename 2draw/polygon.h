#pragma once
#include <vector>
#include "point.h"
#include "triangle.h"
#include "vector.h"

//here polygon is defined by series of points
//adjacent points form an edge of polygon
//currently edges are allowed to intersect each other
class Polygon {

private:
	std::vector<Point> vertexes;

public:

	Polygon() {};
	Polygon(initializer_list<Point> l) : vertexes(l) {};
	Polygon(const Polygon& other) { vertexes = other.vertexes; }
	Polygon& operator=(const Polygon& other) {
		vertexes = other.vertexes;
		return *this;
	}

	void append(const Point& new_point) { vertexes.push_back(new_point); }
	void append(initializer_list<Point> l) { vertexes.insert(vertexes.end(), l.begin(), l.end()); }

	inline Point operator [] (unsigned int idx) const { return vertexes[idx]; }
	Polygon operator+=(const Vector& s) {
		for (int i = 0; i < vertexes.size(); i++) vertexes[i] += s;
		return *this;
	}

	// @todo 
	//bool is_selfx();

	bool is_convex();

	Point center_of_mass() const;

	//rotate around center of mass by /angle/ given in radians
	void rotate(double angle);
	void rotate(const Point& center, double angle);

	double area() const;

	bool is_in(const Point&) const; // returns 1 if point belongs to polygon and 0 otherwise

	friend Polygon convex_hull(const vector<Point>& points);
	friend std::ostream& operator<<(std::ostream& os, const Polygon& p);
};

Polygon convex_hull(const vector<Point>& f);
std::ostream& operator<<(std::ostream& os, const Polygon& p);
