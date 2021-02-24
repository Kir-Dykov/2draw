#pragma once
#include <vector>
using namespace std;


//polygon is defined by series of points
//adjacent points form an edge of polygon
//currently edges are allowed to intersect each other
class Polygon {
public:
	vector<Point> vertexes;
	
	Point operator [] (int idx) return vertexes[idx];
	
	
	// checks for self-intersections
	bool is_selfx ();
	
	bool is_convex ();
	
	Point center_of_mass ();
	
	//rotate around center of mass by /angle/ given in radians
	void rotate (double angle); 
}
