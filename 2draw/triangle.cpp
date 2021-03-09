#include "triangle.h"
#include <cmath>

const double PI = 3.14159265358979;

void triangle::set_triangle(Point _p1, Point _p2, Point _p3)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
}

double triangle::get_triangle_angle(int num_point)
{
	Line A, B;
	Point p;
	double angle;

	num_to_point(num_point, p);
	if (p == p1) { A.set_line(p1, p2); B.set_line(p1, p3); }
	if (p == p2) { A.set_line(p2, p1); B.set_line(p2, p3); }
	if (p == p3) { A.set_line(p3, p1); B.set_line(p3, p2); }
	angle = get_twoLines_radangle(A, B);

	return angle;
}

double triangle::get_triangle_side(int num_point1, int num_point2)
{
	Point p1, p2;
	num_to_point(num_point1, p1);
	num_to_point(num_point2, p2);
	return point_distance(p1, p2);
}

double triangle::triangle_perimeter()
{
	return point_distance(p1, p2) + point_distance(p1, p3) + point_distance(p2, p3);
}

double triangle::triangle_area()
{
	double p = triangle_perimeter() / 2;
	double a = point_distance(p1, p2);
	double b = point_distance(p2, p3);
	double c = point_distance(p1, p3);
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

int triangle::triangle_type()
{
	double angle[3];
	bool is_right = false, is_obtise = false;
	for (int i = 0; i < 3; i++)
	{
		angle[i] = get_triangle_angle(i + 1);
		if (angle[i] == PI / 2) is_right;
		if (angle[i] > PI / 2) is_obtise;
	}
	if (is_right) return 1;
	else if (is_obtise) return 2;
	else return 3;

	return 0;
}

Circle triangle::get_circumcircle() // formula https://www.wikiwand.com/ru/%D0%9E%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%BD%D0%B0%D1%8F_%D0%BE%D0%BA%D1%80%D1%83%D0%B6%D0%BD%D0%BE%D1%81%D1%82%D1%8C
{
	Circle cc;
	double D = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
	cc.set_centerx(((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) + (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y) + (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / D);
	cc.set_centery(((p1.x * p1.x + p1.y * p1.y) * (p2.x - p3.x) + (p2.x * p2.x + p2.y * p2.y) * (p3.x - p1.x) + (p3.x * p3.x + p3.y * p3.y) * (p1.x - p2.x)) / -D);
	cc.set_radius(point_distance(cc.get_center(), p1));

	return cc;
}

Circle triangle::get_inscribed_circle() // we get the center of inscribed circle by solving the system of linear equations (two bisectrixes intersection) and r = S/p
{
	Circle ic;
	Line B1, B2;
	B1 = get_bisectrix(2);
	B2 = get_bisectrix(3);
	ic.set_centery(((B1.c * B2.a) / B1.a - B2.c) / ((-B1.b * B2.a) / B1.a + B2.b));
	ic.set_centerx((-B1.b * ic.get_centery() - B1.c) / B1.a);
	ic.set_radius(2 * triangle_area() / triangle_perimeter());

	return ic;
}

Line triangle::get_median(int num_point)
{
	Point p, a1, a2, m;
	Line M;

	num_to_point(num_point, p);
	if (p == p1) { a1 = p2; a2 = p3; }
	if (p == p2) { a1 = p1; a2 = p3; }
	if (p == p3) { a1 = p1; a2 = p2; }

	m.x = (a1.x + a2.x) * 0.5;
	m.y = (a1.y + a2.y) * 0.5;
	M.set_line(m, p);

	return M;
}

Line triangle::get_bisectrix(int num_point)
{
	Line B, L;
	Point p, a1, a2, bis;
	double a, b, c, m;

	num_to_point(num_point, p);
	if (p == p1) { a1 = p2; a2 = p3; }
	if (p == p2) { a1 = p1; a2 = p3; }
	if (p == p3) { a1 = p1; a2 = p2; }

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

	if (a1.x + v.getx() < a1.x && a1.x + v.getx() > a2.x || a1.x + v.getx() > a1.x && a1.x + v.getx() < a2.x)
	{
		bis.x = a1.x + v.getx();
		bis.y = a1.y + v.gety();
	}
	else
	{
		bis.x = a1.x - v.getx();
		bis.y = a1.y - v.gety();
	}

	B.set_line(bis, p);

	return B;
}

Line triangle::get_altitude(int num_point)
{
	Line Alt, L;
	Point p, a1, a2;

	num_to_point(num_point, p);
	if (p == p1) { a1 = p2; a2 = p3; }
	if (p == p2) { a1 = p1; a2 = p3; }
	if (p == p3) { a1 = p1; a2 = p2; }

	L.set_line(a1, a2);
	Alt = perp_Line(L);
	Alt.c = -Alt.a * p.x - Alt.b * p.y;

	return Alt;
}

bool triangle::operator==(triangle T) {
	Point p[3]; p[0] = p1; p[1] = p2; p[2] = p3;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				if (i != j && j != k && i != k)
					if (point_distance(p[i], p[j]) == point_distance(T.p1, T.p2) && point_distance(p[j], p[k]) == point_distance(T.p1, T.p2) && point_distance(p[i], p[k]) == point_distance(T.p1, T.p2))
						return true;
	return false;
}

void triangle::num_to_point(int num, Point& p)
{
	if (num == 1) p = p1;
	if (num == 2) p = p2;
	if (num == 3) p = p3;
}

bool are_congruent(triangle t1, triangle t2)
{
	if (t1 == t2) return true;
	else return false;
}

bool are_similar(triangle t1, triangle t2)
{
	for (int i = 1; i <= 3; i++)
		if (t1.get_triangle_angle(i) != t2.get_triangle_angle(i)) return false;
	return true;
}