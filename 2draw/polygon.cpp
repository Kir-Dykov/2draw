#include <math.h>
#include "polygon.h"
#include "vector.h"

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

Point Polygon::center_of_mass() {
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

void Polygon::rotate(const Point center, double angle) {
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

double Polygon::area() {
	// Formula is taken from https://en.wikipedia.org/wiki/Shoelace_formula
	double A = 0;
	for (unsigned int i = 0; i < vertexes.size() - 1; i += 1)
		A += vertexes[i].x * vertexes[i + 1].y - vertexes[i + 1].x * vertexes[i].y;

	A += vertexes.back().x * vertexes[0].y - vertexes[0].x * vertexes.back().y;

	return abs(A * 0.5);
}

std::ostream& operator<<(std::ostream& os, Polygon& p) {
	for (unsigned int i = 0; i < p.vertexes.size(); i++)
	{
		os << p[i] << " ";
	}
	return os;
}

bool Polygon::is_in(Point p)
{
	/*vector<Triangle> T(vertexes.size());
	for (unsigned int i = 0; i < vertexes.size() - 1; i++) 
		T[i].set(vertexes[i + 1], vertexes[i + 2], p);

	T[vertexes.size() - 1].set(vertexes[1], vertexes[vertexes.size() - 1], p);

	double area = 0;

	for (unsigned int i = 0; i < vertexes.size(); i++) 
		area += T[i].area();

	return (area == this->area()); */ 

	double A = 0;
	for (unsigned int i = 0; i < vertexes.size() - 1; i++) {
		A += Triangle(vertexes[i], vertexes[i + 1U], p).area();
		cout << Triangle(vertexes[i], vertexes[i + 1U], p).area() << endl;
	}
		

	A += Triangle(vertexes[0], vertexes[vertexes.size() - 1], p).area();
	cout << Triangle(vertexes[0], vertexes[vertexes.size() - 1], p).area() << endl;
	cout << " " << A << " ";
	return (A == area());
}