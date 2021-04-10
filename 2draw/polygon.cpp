#include <math.h>
#include <algorithm>
#include <vector>
#include "polygon.h"
#include "vector.h"
#include "point.h"

bool Polygon::is_convex() {
	//if (is_selfx())
	//	return 0;

	// algorithm assumes that there are no self-intersections
	// the idea is the folowing:
	// polygon is convex iff all it's consecutive edges
	// are rotated in the same direction

	// or, more precisely, determinants of pairs of vectors representing adjacent
	// edges all have the same sign.

	Vector first = vertexes[0] - vertexes.back();
	Vector second = vertexes[1] - vertexes[0];
	double det_0 = determinant(first, second);
	for (unsigned int i = 2; i < vertexes.size(); i += 1) {
		second = first;
		first = vertexes[i] - vertexes[i - 1];
		double det = determinant(first, second);
		if (det * det_0 < 0)
			return 0;
	}

	return 1;
}

Point Polygon::center_of_mass() const{
	// the formula is taken from https://en.wikipedia.org/wiki/Centroid#Of_a_polygon

	double A = 0;
	for (unsigned int i = 0; i < vertexes.size() - 1; i += 1) {
		A += vertexes[i].x * vertexes[i + 1].y - vertexes[i + 1].x * vertexes[i].y;
	}
	A += vertexes.back().x * vertexes[0].y - vertexes[0].x * vertexes.back().y;

	Point center = Point(0, 0);
	for (unsigned int i = 0; i < vertexes.size() - 1; i += 1) {
		center.x += (vertexes[i].x + vertexes[i + 1].x)
			* (vertexes[i].x * vertexes[i + 1].y - vertexes[i + 1].x * vertexes[i].y);
		center.y += (vertexes[i].y + vertexes[i + 1].y) 
			* (vertexes[i].x * vertexes[i + 1].y - vertexes[i + 1].x * vertexes[i].y);
	}
	center.x += (vertexes.back().x + vertexes[0].x)
		* (vertexes.back().x * vertexes[0].y - vertexes[0].x * vertexes.back().y);
	center.y += (vertexes.back().y + vertexes[0].y)
		* (vertexes.back().x * vertexes[0].y - vertexes[0].x * vertexes.back().y);

	center.x /= 3 * A; // 3*A is there instead of 6*A because we didn't devide A by 2 yet
	center.y /= 3 * A;

	return center;
}

void Polygon::rotate(double angle) {
	//just applying rotation matrix to all points
	Point center = center_of_mass();

	double cos_ = cos(angle);
	double sin_ = sin(angle);

		for (unsigned int i = 0; i < vertexes.size(); i += 1) {
			vertexes[i].x -= center.x;
			vertexes[i].y -= center.y;

			double x = vertexes[i].x;
			double y = vertexes[i].y;

			vertexes[i].x = x * cos_ - y * sin_;
			vertexes[i].y = x * sin_ + y * cos_;

			vertexes[i].x += center.x;
			vertexes[i].y += center.y;

		}
}

void Polygon::rotate(const Point& center, double angle) {
	//just applying rotation matrix to all points

	double cos_ = cos(angle);
	double sin_ = sin(angle);

		for (unsigned int i = 0; i < vertexes.size(); i += 1) {
			vertexes[i].x -= center.x;
			vertexes[i].y -= center.y;

			double x = vertexes[i].x;
			double y = vertexes[i].y;

			vertexes[i].x = x * cos_ - y * sin_;
			vertexes[i].y = x * sin_ + y * cos_;

			vertexes[i].x += center.x;
			vertexes[i].y += center.y;

		}
}

double Polygon::area() const{
	// Formula is taken from https://en.wikipedia.org/wiki/Shoelace_formula
	double A = 0;
	for (unsigned int i = 0; i < vertexes.size() - 1; i += 1)
		A += vertexes[i].x * vertexes[i + 1].y - vertexes[i + 1].x * vertexes[i].y;

	A += vertexes.back().x * vertexes[0].y - vertexes[0].x * vertexes.back().y;

	return abs(A * 0.5);
}

std::ostream& operator<<(std::ostream& os, const Polygon& p) {
	for (unsigned int i = 0; i < p.vertexes.size(); i++)
	{
		os << p.vertexes[i] << " ";
	}
	return os;
}

bool Polygon::is_in(const Point& p) const {
	double det_0 = determinant(vertexes[0] - vertexes.back(), p - vertexes.back());
	for (unsigned int i = 0; i < vertexes.size()-1; i += 1) {
		double det = determinant(vertexes[i + 1] - vertexes[i], p - vertexes[i]);
		if (det * det_0 < 0)
			return 0;
	}

	return 1;
}

//Graham scan algorithm
Polygon convex_hull(const vector<Point>& _f) {
	vector<Point> f = _f;
	if (f.size() == 3)
	{
		Polygon hull = { f[0], f[1], f[2] };
		return hull;
	}

	double min_y = f[0].y;
	int min_idx = 0;
	for (int i = 1; i < f.size(); i++)
	{
		if (f[i].y < min_y ||
			f[i].y == min_y && f[i].x < f[min_idx].x)
		{
			min_y = f[i].y;
			min_idx = i;
		}
	}
	
	swap(f[0], f[min_idx]);
	double _x = f[0].x;
	double _y = f[0].y;

	sort(f.begin()+1, f.end(), 
		[p0 = f[0]](Point a, Point b) {
		return cos(a - p0, Vector(1,0)) > cos(b - p0, Vector(1, 0));
	});

	Polygon hull;

	hull.append({ f[0], f[1], f[2] });

	size_t head = 2;

	
	for (size_t i = 3; i < f.size(); i++)
	{
		
		if (determinant(hull[head] - hull[head - 1], f[i] - hull[head]) > 0) {
			hull.append(f[i]);
			head++;
			
		}
		else {
			while (determinant(hull[head-1] - hull[head - 2], f[i] - hull[head-1]) <= 0) {
				head--;
			}
			hull.vertexes[head] = f[i];
			hull.vertexes.resize(head + (size_t)1);
		}
	}
	return hull;
}