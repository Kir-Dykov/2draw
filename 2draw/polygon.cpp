#include <math.h>
#include <algorithm>
#include <vector>
#include "polygon.h"
#include "vector.h"
#include "point.h"
#include "utilities.h"

bool Polygon::is_convex() const{
	//if (is_selfx())
	//	return 0;

	// algorithm assumes that there are no self-intersections
	// the idea is the folowing:
	// polygon is convex iff all it's consecutive edges
	// are rotated in the same direction
	// so there are no inner angles greater than 180 degrees

	// more precisely, determinants of pairs of vectors representing adjacent
	// edges must all have the same sign.

	Vector first = vertexes.back() - vertexes[vertexes.size()-2];
	Vector second = vertexes[0] - vertexes.back();
	double det_0 = determinant(first, second);
	for (unsigned int i = 2; i < vertexes.size(); i += 1) {
		first = second;
		second = vertexes[i] - vertexes[i - 1];
		double det = determinant(first, second);
		if (det * det_0 < 0)
			return 0;
	}

	return 1;
}

Point Polygon::center_of_mass() const{
	// the formula is taken from https://en.wikipedia.org/wiki/Centroid#Of_a_polygon
	// the notation is preserved

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
	Point pivot = center_of_mass();

	double cos_ = cos(angle);
	double sin_ = sin(angle);

	for (unsigned int i = 0; i < vertexes.size(); i += 1) {
		//shift pivot of rotation to zero
		vertexes[i].x -= pivot.x;
		vertexes[i].y -= pivot.y;

		double x = vertexes[i].x;
		double y = vertexes[i].y;

		//rotate around pivot by an angle
		vertexes[i].x = x * cos_ - y * sin_;
		vertexes[i].y = x * sin_ + y * cos_;

		//shifting the pivot back
		vertexes[i].x += pivot.x;
		vertexes[i].y += pivot.y;
	}
}

void Polygon::rotate(const Point& pivot, double angle) {
	//applying rotation matrix to all points

	//save values explicitly for sake of optimization (just in case compiler doesn't do it)
	double cos_ = cos(angle);
	double sin_ = sin(angle);

	for (unsigned int i = 0; i < vertexes.size(); i += 1) {
		//shift pivot of rotation to zero
		vertexes[i].x -= pivot.x;
		vertexes[i].y -= pivot.y;

		double x = vertexes[i].x;
		double y = vertexes[i].y;

		//rotate around pivot by an angle
		vertexes[i].x = x * cos_ - y * sin_;
		vertexes[i].y = x * sin_ + y * cos_;

		//shifting the pivot back
		vertexes[i].x += pivot.x;
		vertexes[i].y += pivot.y;
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

//prints coordinates of each vertex
std::ostream& operator<<(std::ostream& os, const Polygon& p) {
	for (unsigned int i = 0; i < p.vertexes.size(); i++)
	{
		os << p.vertexes[i] << " ";
	}
	return os;
}

bool Polygon::is_in(const Point& p) const {
	
	if (this->is_convex()) {
		//convex case is easier to compute, and could be more reliable because
		//there are no 'equals' comparison of floats, where rounding issues could occur
		double det_0 = determinant(vertexes[0] - vertexes.back(), p - vertexes.back());
		for (size_t i = 0; i < vertexes.size() - 1; i += 1) {
			double det = determinant(vertexes[i + 1Ui64] - vertexes[i], p - vertexes[i]);
			if (det * det_0 < 0)
				return 0;
		}
		return 1;
	}
	else {
		// the idea of the algorithm: https://en.wikipedia.org/wiki/Point_in_polygon#Winding_number_algorithm

		int winding_number = 0;
		int turn_sign;
		
		for (size_t i = 0; i < vertexes.size() - 1; i += 1)	{
			// if edge crosses vertical line
			if ((vertexes[i].x - p.x) * (vertexes[i+1].x - p.x) <= 0) {
				// then we add a sign of a rotation (it's positive 
				// iff vector from vertexes[i] to vertexes[i + 1]
				// goes around p counter-clockwise
				winding_number += 2 * (determinant(vertexes[i] - p, vertexes[i + 1] - p) > 0) - 1;
			}
		}
		//repeat for the unaccounted edge
		if ((vertexes.back().x - p.x) * (vertexes[0].x - p.x) <= 0) {
			winding_number += 2 * (determinant(vertexes.back() - p, vertexes[0] - p) > 0) - 1;
		}
		
		return (winding_number!=0);
	}
}

//Graham scan algorithm
Polygon convex_hull(const vector<Point>& _f) {
	vector<Point> f = _f; //copy so we can change it (sort it, etc...)

	// three points always form a convex shape
	// if they are colinear, it considered as convex shape too
	if (f.size() == 3)
	{
		Polygon hull = { f[0], f[1], f[2] };
		return hull;
	}

	//according to algorythm, we find point with minimal y-coordinate
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
	
	//put found point in the begining of array
	swap(f[0], f[min_idx]);

	//sort by angle to a lowest point
	sort(f.begin()+1, f.end(), 
		[p0 = f[0]](Point a, Point b) {
		return cos(a - p0, Vector(1,0)) > cos(b - p0, Vector(1, 0));
	});

	//there we will add all the selected points in order
	Polygon hull;

	hull.append({ f[0], f[1], f[2] });

	// index, pointing to last added vertex
	size_t head = 2;
	
	for (size_t i = 3; i < f.size(); i++) //starting from index 3 (intentionaly)
	{
		// adding f[i] not results in angles larger than 180 degrees
		if (determinant(hull[head] - hull[head - 1], f[i] - hull[head]) > 0) {
			hull.append(f[i]);
			head++;
		}
		else {
			//delete last added vertexes until shape is convex again
			while (determinant(hull[head-1] - hull[head - 2], f[i] - hull[head-1]) <= 0) {
				head--;
			}
			hull.vertexes[head] = f[i];
			hull.vertexes.resize(head + (size_t)1);
		}
	}
	return hull;
}

double Polygon::perimeter() const {
	double res = sqrt((vertexes[vertexes.size() - 1].x - vertexes[0].x) * (vertexes[vertexes.size() - 1].x - vertexes[0].x) \
		+ (vertexes[vertexes.size() - 1].y - vertexes[0].y) * (vertexes[vertexes.size() - 1].y - vertexes[0].y));
	for (int i = 0; i < vertexes.size() - 1; i++)
	{
		res += sqrt((vertexes[i].x - vertexes[i + 1].x) * (vertexes[i].x - vertexes[i + 1].x) + (vertexes[i].y - vertexes[i + 1].y) \
			* (vertexes[i].y - vertexes[i + 1].y));
	}
	return res;
}

void CALLBACK tessBeginCB(GLenum which)
{ 
	glBegin(which);
}

void CALLBACK tessEndCB()
{
	glEnd();
}

void CALLBACK tessVertexCB(const GLvoid* data)
{
	// cast back to double type
	const GLdouble* ptr = (const GLdouble*)data;

	glVertex2dv(ptr);
}

void Polygon::Draw() const {
	if (filled) {

		GLdouble** ver = new GLdouble * [vertexes.size()];
		for (int i = 0; i < vertexes.size(); i++)
		{
			ver[i] = new GLdouble[3];
			for (int j = 0; j < 3; j++)
			{
				if (j == 0) ver[i][j] = vertexes[i].x;
				else if (j == 1) ver[i][j] = vertexes[i].y;
				else if (j == 2) ver[i][j] = 0;
			}
		}

		GLUtesselator* pTess;
		glColor3ub(red, green, blue);
		pTess = gluNewTess();
		gluTessCallback(pTess, GLU_TESS_BEGIN, (void (CALLBACK*)())tessBeginCB);
		gluTessCallback(pTess, GLU_TESS_END, (void (CALLBACK*)())tessEndCB);
		gluTessCallback(pTess, GLU_TESS_VERTEX, (void (CALLBACK*)())tessVertexCB);
		gluTessBeginPolygon(pTess, NULL);
		gluTessBeginContour(pTess);
		for (int i = 0; i < vertexes.size(); i++)
		{
			gluTessVertex(pTess, ver[i], ver[i]);
		}
		gluTessEndContour(pTess);
		gluTessEndPolygon(pTess);
		gluDeleteTess(pTess);
		for (int i = 0; i < vertexes.size(); i++) delete[] ver[i];
		delete[] ver;
	}
	else {
		glBegin(GL_LINE_LOOP);
		glColor3ub(red, green, blue);/*rand() % 128 + 128*/
		for (int i = 0; i < vertexes.size(); i++) {
			glVertex2d(vertexes[i].x, vertexes[i].y);
		}
		glEnd();
	}
}