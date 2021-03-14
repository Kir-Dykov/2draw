#pragma once
#include <vector>
#include "point.h"
#include "triangle.h"


//polygon is defined by series of points
//adjacent points form an edge of polygon
//currently edges are allowed to intersect each other
class Polygon {
public:
	std::vector<Point> vertexes;
	Polygon() {};

	void append(Point);

	Point operator [] (int idx) { return vertexes[idx]; }

	// unimplemented
	//bool is_selfx();

	bool is_convex();

	Point center_of_mass();

	//rotate around center of mass by /angle/ given in radians
	void rotate(double angle);
	void rotate(Point center, double angle);

	double area();

	bool point_polygon_belonging(Point); // returns 1 if point belongs to polygon and 0 otherwise
};

std::ostream& operator<<(std::ostream& os, Polygon& p);