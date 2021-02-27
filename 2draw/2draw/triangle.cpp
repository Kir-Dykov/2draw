#include "triangle.h"
#include <cmath>

void triangle::set(point _p1, point _p2, point _p3)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
}

double triangle::triangle_angle(point p)
{
	Line A, B;
	double angle;
	if (p == p1) { A.set(p1, p2); B.set(p1, p3); }
	if (p == p2) { A.set(p2, p1); B.set(p2, p3); }
	if (p == p3) { A.set(p3, p1); B.set(p3, p2); }
	angle = get_twoLines_radangle(A, B);
	return angle;
}

double triangle::triangle_perimeter()
{
	return point_distance(p1, p2) + point_distance(p1, p3) + point_distance(p2, p3);
}

bool triangle::operator==(triangle T) {
	point p[3]; p[0] = p1; p[1] = p2; p[2] = p3;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				if (i != j && j != k && i != k)
					if (point_distance(p[i], p[j]) == point_distance(T.p1, T.p2) && point_distance(p[j], p[k]) == point_distance(T.p1, T.p2) && point_distance(p[i], p[k]) == point_distance(T.p1, T.p2))
						return true;
	return false;
}

double triangle::triangle_area()
{
	double p = triangle_perimeter() / 2;
	double a = point_distance(p1, p2);
	double b = point_distance(p2, p3);
	double c = point_distance(p1, p3);
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

Line triangle::get_median(point p)
{
	Line M;
	if (!(p == p1) && !(p == p2) && !(p == p3)); // idk what to rerurn if user decides to choose a point not as a triangle vertex
	else
	{
		point a1, a2, m;
		if (p == p1) { a1 = p2; a2 = p3; }
		if (p == p2) { a1 = p1; a2 = p3; }
		if (p == p3) { a1 = p1; a2 = p2; }
		m.x = (a1.x + a2.x) * 0.5;
		m.y = (a1.y + a2.y) * 0.5;
		M.set(m, p);
	}
	return M;
}

Line triangle::get_bisectrix(point p)
{
	Line B;
	if (!(p == p1) && !(p == p2) && !(p == p3)); // same as in line 39
	else
	{
		Line L;
		point a1, a2, bis;
		double a, b, c;
		if (p == p1) { a1 = p2; a2 = p3; }
		if (p == p2) { a1 = p1; a2 = p3; }
		if (p == p3) { a1 = p1; a2 = p2; }
		a = point_distance(p, p1);
		b = point_distance(p, p2);
		c = point_distance(p1, p2);
		L.set(p1, p2);
		double k = sqrt(a*c / (a + b) * (L.a * L.a + L.b * L.b));
		bis.x = p1.x - k * L.b;
		bis.y = p1.y + k * L.a;
		B.set(bis, p);
	}
	return B;
}

Line triangle::get_altitude(point p)
{
	Line Alt;
	if (!(p == p1) && !(p == p2) && !(p == p3)); // same as in line 39
	else
	{
		point a1, a2;
		Line L;
		if (p == p1) { a1 = p2; a2 = p3; }
		if (p == p2) { a1 = p1; a2 = p3; }
		if (p == p3) { a1 = p1; a2 = p2; }
		L.set(p1, p2);
		Alt = perp_Line(L);
		Alt.c = -L.a * p.x - L.b * p.y;
	}
	return Alt;
}

int triangle::triangle_type()
{
	
}