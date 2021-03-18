#include "triangle.h"
#include <cmath>

const double PI = 3.14159265358979;

void Triangle::set_triangle(Point _p1, Point _p2, Point _p3) {
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
}

double Triangle::get_triangle_angle(int num_point) {
	Line A, B;
	Point p;
	double angle;
	num_to_point(num_point, p);
	if (p == p1) {
		A.set_line(p1, p2);
		B.set_line(p1, p3); 
	}
	if (p == p2) {
		A.set_line(p2, p1); 
		B.set_line(p2, p3); 
	}
	if (p == p3) {
		A.set_line(p3, p1); 
		B.set_line(p3, p2); 
	}
	angle = get_twoLines_radangle(A, B);

	return angle;
}

double Triangle::get_triangle_side(int num_point1, int num_point2) {
	Point p1, p2;
	num_to_point(num_point1, p1);
	num_to_point(num_point2, p2);

	return point_distance(p1, p2);
}

double Triangle::triangle_perimeter() const {
	return point_distance(p1, p2) + point_distance(p1, p3) + point_distance(p2, p3);
}

double Triangle::triangle_area() {
	double p = triangle_perimeter() / 2;
	double a = point_distance(p1, p2);
	double b = point_distance(p2, p3);
	double c = point_distance(p1, p3);

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

int Triangle::triangle_type() {
	double eps = 0.00000000000001;
	bool is_right = false, is_obtise = false;
	for (int i = 0; i < 3; i++) {
		if (get_triangle_angle(i + 1) > PI / 2.0 - eps && get_triangle_angle(i + 1) < PI / 2.0 + eps) 
			is_right = true;
		if (get_triangle_angle(i + 1) > PI / 2.0) is_obtise = true;
	}

	if (is_right == true) return 1;
	if (is_obtise == true) return 2;
	return 3;
}

// formula https://www.wikiwand.com/ru/%D0%9E%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%BD%D0%B0%D1%8F_%D0%BE%D0%BA%D1%80%D1%83%D0%B6%D0%BD%D0%BE%D1%81%D1%82%D1%8C
Circle Triangle::get_circumcircle() { 
	Circle cc;
	double D = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
	cc.set_centerx(((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) + (p2.x * p2.x + p2.y * p2.y) * \
		(p3.y - p1.y) + (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / D);
	cc.set_centery(((p1.x * p1.x + p1.y * p1.y) * (p2.x - p3.x) + (p2.x * p2.x + p2.y * p2.y) * \
		(p3.x - p1.x) + (p3.x * p3.x + p3.y * p3.y) * (p1.x - p2.x)) / -D);
	cc.set_radius(point_distance(cc.get_center(), p1));

	return cc;
}

// we get the center of inscribed circle by solving the system of linear equations (two bisectrixes intersection) and r = S/p
Circle Triangle::get_inscribed_circle() {
	Circle ic;
	Line B1, B2;
	B1 = get_bisectrix(2);
	B2 = get_bisectrix(3);
	ic.set_centery(((B1.c * B2.a) / B1.a - B2.c) / ((-B1.b * B2.a) / B1.a + B2.b));
	ic.set_centerx((-B1.b * ic.get_centery() - B1.c) / B1.a);
	ic.set_radius(2 * triangle_area() / triangle_perimeter());

	return ic;
}

Line Triangle::get_median(int num_point) {
	Point p, a1, a2, m;
	Line M;
	num_to_point(num_point, p);
	point_reassignment(p, p1, p2, p3, a1, a2);
	m.x = (a1.x + a2.x) * 0.5;
	m.y = (a1.y + a2.y) * 0.5;
	M.set_line(m, p);

	return M;
}

Line Triangle::get_bisectrix(int num_point) {
	Line B, L;
	Point p, a1, a2, bis;
	double a, b, c, m;
	num_to_point(num_point, p);
	point_reassignment(p, p1, p2, p3, a1, a2);
	a = point_distance(p, a1);
	b = point_distance(p, a2);
	c = point_distance(a1, a2);
	L.set_line(a1, a2);
	m = a * c / (a + b);
	Vector v;
	if (L.a != 0 && L.b != 0) v.set(L.b / sqrt(L.a * L.a + L.b * L.b), -L.a / sqrt(L.a * L.a + L.b * L.b));
	if (L.a == 0) v.set(1, 0);
	if (L.b == 0) v.set(0, 1);
	v = v * m;
	if (a1.x + v.getx() < a1.x && a1.x + v.getx() > a2.x || a1.x + v.getx() > a1.x && a1.x + v.getx() < a2.x) {
		bis.x = a1.x + v.getx();
		bis.y = a1.y + v.gety();
	}
	else {
		bis.x = a1.x - v.getx();
		bis.y = a1.y - v.gety();
	}
	B.set_line(bis, p);

	return B;
}

Line Triangle::get_altitude(int num_point) {
	Line Alt, L;
	Point p, a1, a2;
	num_to_point(num_point, p);
	point_reassignment(p, p1, p2, p3, a1, a2);
	L.set_line(a1, a2);
	Alt = perp_Line(L);
	Alt.c = -Alt.a * p.x - Alt.b * p.y;

	return Alt;
}

Line Triangle::get_midline(int num_point) {
	Line Mid;
	Point p, a1, a2;
	num_to_point(num_point, p);
	point_reassignment(p, p1, p2, p3, a1, a2);
	Mid.set_line(Point((p.x + a1.x) / 2.0, (p.y + a1.y) / 2.0), Point((p.x + a2.x) / 2.0, (p.y + a2.y) / 2.0));

	return Mid;
}

Line Triangle::get_perp_bis(int num_point) {
	Line Perp, L;
	Point p, a1, a2;
	num_to_point(num_point, p);
	point_reassignment(p, p1, p2, p3, a1, a2);
	L.set_line(a1, a2);
	Perp = perp_Line(L);
	Perp.c = -Perp.a * (a1.x + a2.x) / 2.0 - Perp.b * (a1.y + a2.y) / 2.0;

	return Perp;
}

bool Triangle::point_triangle_belonging(Point p) {
	Triangle T; T.set_triangle(p1, p2, p3);
	Triangle T1, T2, T3;
	T1.set_triangle(p1, p2, p);	T2.set_triangle(p2, p3, p); T3.set_triangle(p1, p3, p);

	return (T1.triangle_area() + T2.triangle_area() + T3.triangle_area() == T.triangle_area());
}

bool Triangle::operator==(Triangle T) {
	Triangle t; t.set_triangle(p1, p2, p3);
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			for (int k = 1; k <= 3; k++)
				if (i != j && j != k && i != k)
					if (t.get_triangle_side(1, 2) == T.get_triangle_side(i, j) && t.get_triangle_side(2, 3) == \
						T.get_triangle_side(j, k) && t.get_triangle_side(1, 3) == T.get_triangle_side(i, k))
						return true;

	return false;
}

void Triangle::num_to_point(int num, Point& p) {
	if (num == 1) p = p1;
	if (num == 2) p = p2;
	if (num == 3) p = p3;
}

void Triangle::point_reassignment(Point p, Point p1, Point p2, Point p3, Point& a1, Point& a2) {
	if (p == p1) { 
		a1 = p2; 
		a2 = p3; 
	}
	if (p == p2) { 
		a1 = p1;
		a2 = p3;
	}
	if (p == p3) {
		a1 = p1;
		a2 = p2; 
	}
}

bool Triangle::are_congruent(Triangle t) {
	Triangle s;
	s.set_triangle(p1, p2, p3);

	return (s == t);
}

bool Triangle::are_similar(Triangle t) {
	Triangle s; s.set_triangle(p1, p2, p3);
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			for (int k = 1; k <= 3; k++)
				if (i != j && j != k && i != k)
					if (s.get_triangle_angle(1) == t.get_triangle_angle(i) && s.get_triangle_angle(2) == \
						t.get_triangle_angle(j) && s.get_triangle_angle(3) == t.get_triangle_angle(k))
						return true;

	return false;
}