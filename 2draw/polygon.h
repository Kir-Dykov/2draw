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
	
	const std::vector<Point>& v = vertexes;

	Polygon() {};

	Polygon(initializer_list<Point> l) : vertexes(l) {};

	void append(Point new_point) { 
		vertexes.push_back(new_point); 
	}
	void append(initializer_list<Point> l) {
		vertexes.insert(vertexes.end(), l.begin(), l.end());
	}

	inline Point operator [] (unsigned int idx) const { return vertexes[idx]; }


	Polygon operator+=(Vector s) {
		for (int i = 0; i < vertexes.size(); i++) vertexes[i] += s;
		return *this;
	}

	// unimplemented (is_selfx is short for is_self_intersecting)
	//bool is_selfx();

	bool is_convex() const;

	Point center_of_mass() const;

	//rotate around center of mass by /angle/ given in radians
	void rotate(double angle);
	void rotate(Point center, double angle);

	double area() const;

	bool is_in(Point) const; // returns 1 if point belongs to polygon and 0 otherwise

	friend Polygon convex_hull(const vector<Point> f);

};

std::ostream& operator<<(std::ostream& os, const Polygon& p);
