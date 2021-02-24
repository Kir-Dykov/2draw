#include "polygon.h"
#include "vector.h"



bool Polygon::is_convex() {
	if (is_selfx())
		return 0;

	// algorithm assumes that there are no self-intersections
	// the idea is the folowing:
	// polygon is convex iff all it's consecutive edges
	// are rotated in the same direction
	
	// or, more precisely, determinants of pairs of vectors representing adjacent
	// edges all have the same sign.
	
	Vector first = vertexes[0] - vertexes.back();
	Vector second = vertexes[1] - vertexes[0];
	double det_0 = determinant(first, second);
	for (int i = 2; i<vertexes.size(); i+=1) {
		second = first;
		first = vertexes[i] - vertexes[i-1];
		double det = determinant(first, second);
		if (det*det_0 < 0)
			return 0;
	}
	
	return 1;
}

Point center_of_mass () {
	// the formula is taken from https://en.wikipedia.org/wiki/Centroid#Of_a_polygon
	// TESTING REQUIRED!!!!
	double A = 0; // 2*A from original formula
	for (int i = 0; i<vertexes.size()-1; i+=1) {
		A += vertexes[i].x * vertexes[i+1].y - vertexes[i+1].x * vertexes[i].y;
	}
	A += vertexes.back().x * vertexes[0].y - vertexes[0].x * vertexes.back().y;
	
	Point center = Point(0, 0);
	for (int i = 0; i<vertexes.size()-1 ; i+=1) {
		center.x += (vertexes[i].x + vertexes[i+1].x)
		           *(vertexes[i].x * vertexes[i+1].y - vertexes[i+1].x * vertexes[i].y)
		center.y += (vertexes[i].y + vertexes[i+1].y)
		           *(vertexes[i].x * vertexes[i+1].y - vertexes[i+1].x * vertexes[i].y)		
	}
	center.x += (vertexes.back().x + vertexes[0].x)
	           *(vertexes.back().x * vertexes[0].y - vertexes[0].x * vertexes.back().y)
	center.y += (vertexes.back().y + vertexes[0].y)
	           *(vertexes.back().x * vertexes[0].y - vertexes[0].x * vertexes.back().y)	
	           
	center.x /= 12*A;
	center.y /= 12*A;
	
	return center;
}
