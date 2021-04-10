#define _USE_MATH_DEFINES
#include <math.h>
#include "triangle.h"

void Triangle::set(Point _p1, Point _p2, Point _p3) {
	try {
		if (!exist(_p1, _p2, _p3)) throw "Triangle doesn't exist";
		else { p1 = _p1; p2 = _p2; p3 = _p3; }
	}
	catch (const char* exception) {
		cerr << "Error: " << exception << endl;
		exit(0);
	}
}

bool Triangle::exist(Point _p1, Point _p2, Point _p3) const {
	Line L;
	L.set(_p1, _p2);
	if (L.point_on_Line(_p3)) return 0;
	if (_p1 == _p2 || _p2 == _p3 || _p1 == _p3) return 0;
	return 1;
}

double Triangle::get_angle(const Point vertex) const {
	Line A, B;					// lines lying on the sides of a given vertex
	// finding two lines of a selected vertex
	if (vertex == p1) {
		A.set(p1, p2);
		B.set(p1, p3); 
	}
	else if (vertex == p2) {
		A.set(p2, p1); 
		B.set(p2, p3); 
	}
	else if (vertex == p3) {
		A.set(p3, p1); 
		B.set(p3, p2); 
	}

	return A.get_twoLines_radangle(B);
}

double Triangle::get_side(const int num_point1, const int num_point2) const {
	Point p1, p2;	// vertices
	// selecting a vertex
	num2point(num_point1, p1);
	num2point(num_point2, p2);

	return p1.distance(p2);
}

double Triangle::perimeter() const{
	return p1.distance(p2) + p1.distance(p3) + p2.distance(p3);
}

double Triangle::area() const{
	double p = perimeter() / 2;		// perimeter
	// finding the lengths of the sides
	double a = p1.distance(p2);
	double b = p2.distance(p3);
	double c = p1.distance(p3);

	return sqrt(p * (p - a) * (p - b) * (p - c));	// Heron's formula
}

int Triangle::triangle_type() const {
	double first_side, second_side, third_side;
	first_side = p1.distance(p2);
	second_side = p1.distance(p3);
	third_side = p2.distance(p3);
	if (first_side * first_side == second_side * second_side + third_side * third_side || \
		second_side * second_side == first_side * first_side + third_side * third_side || \
		third_side * third_side == first_side * first_side + second_side * second_side)
		return 1;
	else if (first_side * first_side > second_side * second_side + third_side * third_side || \
		second_side * second_side > first_side * first_side + third_side * third_side || \
		third_side * third_side > first_side * first_side + second_side * second_side)
		return 2;
	else
		return 3;
}

Circle Triangle::get_circumcircle() const{
	// Method: https://www.wikiwand.com/ru/%D0%9E%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%BD%D0%B0%D1%8F_%D0%BE%D0%BA%D1%80%D1%83%D0%B6%D0%BD%D0%BE%D1%81%D1%82%D1%8C
	Circle cc;
	double D = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
	cc.set_centerx(((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) + (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y) + (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / D);
	cc.set_centery(((p1.x * p1.x + p1.y * p1.y) * (p2.x - p3.x) + (p2.x * p2.x + p2.y * p2.y) * (p3.x - p1.x) + (p3.x * p3.x + p3.y * p3.y) * (p1.x - p2.x)) / -D);
	cc.set_radius(cc.center.distance(p1));
	return cc;
}


Circle Triangle::get_inscribed_circle() const{
	// Method: we get the center of inscribed circle by solving the system of
	// linear equations (two bisectrixes intersection) and r = S/p
	Circle ic;		// answer - inscribed circle
	Line B1, B2;	// bisectors of a vertices
	// finding the bisector of a vertex
	B1 = get_bisectrix(p1);
	B2 = get_bisectrix(p2);
	// set circle
	ic.set_centery(((B1.c * B2.a) / B1.a - B2.c) / ((-B1.b * B2.a) / B1.a + B2.b));
	ic.set_centerx((-B1.b * ((B1.c * B2.a) / B1.a - B2.c) / ((-B1.b * B2.a) / B1.a + B2.b) - B1.c) / B1.a);
	ic.set_radius(2 * (*this).area() / (*this).perimeter());

	return ic;
}

Line Triangle::get_median(const Point vertex) const{
	// Method: we just find the mid point of the opposite side and draw a line through two points
	Point a1, a2, medianbase;		// vertices and base of the median 
	Line M;								// median
	// finding the other two vertices
	point_reassignment(vertex, a1, a2);
	// finding the coordinates of the base of the median
	medianbase.x = (a1.x + a2.x) * 0.5;
	medianbase.y = (a1.y + a2.y) * 0.5;
	M.set(medianbase, vertex);

	return M;
}

Line Triangle::get_bisectrix(const Point vertex) const {
	// Method: using the bisectrix properties (AB/AC = MB/MC), we find the point of bisectrix 
	// intersection with the triangle side and draw a line through two points
	Line B, L;
	Point a1, a2, bis;			// vertices and
	double a, b, c, m;			// the length of the sides
	// finding the other two vertices
	point_reassignment(vertex, a1, a2);
	// finding the lengths of the sides
	a = vertex.distance(a1);
	b = vertex.distance(a2);
	c = a1.distance(a2);
	// set side
	L.set(a1, a2);
	m = a * c / (a + b);
	Vector v;
	if (L.a != 0 && L.b != 0) v.set(L.b / sqrt(L.a * L.a + L.b * L.b), -L.a / sqrt(L.a * L.a + L.b * L.b));
	if (L.a == 0) v.set(1, 0);
	if (L.b == 0) v.set(0, 1);
	v = v * m;

	bis.x = a1.x + v.x;
	bis.y = a1.y + v.y;
	B.set(bis, vertex);

	return B;
}

Line Triangle::get_altitude(const Point vertex) const{
	// Method: we draw a perp. line to the opposite side and using its equation Ax + By + C = 0 
	// choose such C, that this line intersects our point 
	Line Alt, L;			// altitude and side (line)
	Point a1, a2;			// vertices
	// finding the other two vertices
	point_reassignment(vertex, a1, a2);
	// set side (line)
	L.set(a1, a2);
	Alt = L.perpendicular();
	Alt.set_argument_c(-Alt.a * vertex.x - Alt.b * vertex.y);

	return Alt;
}

Line Triangle::get_midline(const Point vertex) const{
	Line Mid;		// midline
	Point a1, a2;	// vertices
	// finding the other two vertices
	point_reassignment(vertex, a1, a2);
	//set midline
	Mid.set(Point((vertex.x + a1.x) / 2.0, (vertex.y + a1.y) / 2.0), Point((vertex.x + a2.x) / 2.0, (vertex.y + a2.y) / 2.0));

	return Mid;
}

Line Triangle::get_perp_bis(const Point vertex) const{
	Line Perp, L;		// add side (line)
	Point a1, a2;		// vertices
	// finding the other two vertices
	point_reassignment(vertex, a1, a2);
	// set side (line)
	L.set(a1, a2);
	Perp = L.perpendicular();
	Perp.set_argument_c(-Perp.a * (a1.x + a2.x) / 2.0 - Perp.b * (a1.y + a2.y) / 2.0);

	return Perp;
}

bool Triangle::is_in(const Point p) const{
	// Finding out if the point belongs to triangle using cross products
	double det_0 = determinant(Vector(p1 - p3), Vector(p - p3));
	double det_1 = determinant(Vector(p2 - p1), Vector(p - p1));
	double det_2 = determinant(Vector(p3 - p2), Vector(p - p2));
	if (det_1 * det_0 < 0 || det_2 * det_0 < 0)
		return 0;
	return 1;
}

void Triangle::num2point(const int num, Point& p) const{
	// determining the vertex by number
	if (num == 1) p = p1;
	else if (num == 2) p = p2;
	else if (num == 3) p = p3;
}

void Triangle::point_reassignment(const Point p, Point& a1, Point& a2) const{
	// finding the other two vertices
	if (p == p1) {
		a1 = p2;
		a2 = p3;
	}
	else if (p == p2) {
		a1 = p1;
		a2 = p3;
	}
	else if (p == p3) {
		a1 = p1;
		a2 = p2;
	}
}

bool Triangle::operator==(const Triangle T) const{
	// Method: Triangles are congruent if you can get one from another by rotations and reflections
	// This method does not take much time cause there are only 3! = 6 iterations of cycle
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			for (int k = 1; k <= 3; k++)
				if (i != j && j != k && i != k)
					if ((*this).get_side(1, 2) == T.get_side(i, j) && (*this).get_side(2, 3) == \
						T.get_side(j, k) && (*this).get_side(1, 3) == T.get_side(i, k))
						return true;

	return false;
}

std::ostream& operator<<(std::ostream& os, Triangle& t) {
	os << "(" << t.p1 << ", " << t.p2 << ", " << t.p3 << ")";
	return os;
}

Circle Triangle::get_excircle(const Point vertex) const {
	// vertex - the vertex opposite which there will be a circle
	Point second_vertex, third_vertex;	// the other two vertices
	// finding the other two vertices
	point_reassignment(vertex, second_vertex, third_vertex);
	Line bisect_second_vertex, bisect_third_vertex;			// bisectors of two other vertices
	// finding the bisector the other two vertices
	bisect_second_vertex = get_bisectrix(second_vertex);
	bisect_third_vertex = get_bisectrix(third_vertex);
	Line perp2bis_second_vert, perp2bis_third_vert;			// perpendicular to bisectors
	// finding perpendicular to bisectors
	perp2bis_second_vert = bisect_second_vertex.perp2point_on_line(second_vertex);
	perp2bis_third_vert = bisect_third_vertex.perp2point_on_line(third_vertex);
	Point intersection = perp2bis_second_vert.intersection_point_lines(perp2bis_third_vert);
	double radius = (*this).area() / ((*this).perimeter() - second_vertex.distance(third_vertex));
	Circle res;
	res.set(intersection, radius);
	cout << intersection << ' ' << radius << '\n';
	return res;
}