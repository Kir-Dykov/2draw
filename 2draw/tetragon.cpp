#include "tetragon.h"
#include "triangle.h"
#include <cmath>
#include <vector>
#include <algorithm>
bool cmp(const Point& p1, const Point& p2) {
	if (p1.x != p2.x)
		return p1.x < p2.x;
	else
		return p1.y < p2.y;
}
void Tetragon::set(Point a, Point b, Point c, Point d) {
	vector <Point> p; p.resize(4);
	p[0] = a; p[1] = b; p[2] = c; p[3] = d;
	sort(p.begin(), p.end(), cmp);
	p1 = p[0];
	p2 = p[1];
	l1.set_line(p1, p2);
	if (-l1.a / l1.b > 0 || l1.b == 0)
		if (p[2].y > p[3].y) {
			p3 = p[2];
			p4 = p[3];
		}
		else {
			p3 = p[3];
			p4 = p[2];
		}
	else if (-l1.a / l1.b < 0)
		if (p[2].y < p[3].y) {
			p3 = p[2];
			p4 = p[3];
		}
		else {
			p3 = p[3];
			p4 = p[2];
		}
	else if (-l1.a / l1.b == 0) {
		p3 = p[3];
		p4 = p[2];
	}
	l2.set_line(p2, p3);
	l3.set_line(p3, p4);
	l4.set_line(p1, p4);
	d1.set_line(p1, p3);
	d2.set_line(p2, p4);
	if (l1 == l2 || l2 == l3 || l3 == l4 || l1 == l4)
		cout << "Such Tetragon doesn't exist" << endl;
	side1 = point_distance(p1, p2);
	side2 = point_distance(p2, p3);
	side3 = point_distance(p3, p4);
	side4 = point_distance(p1, p4);
}

bool Tetragon::convex_tetragon() {
	if (find_halfplane(d2, p1) > 0 || find_halfplane(d2, p3) < 0 || find_halfplane(d1, p2) < 0 || find_halfplane(d1, p4) > 0)
		return 1;
	else
		return 0;
}

double Tetragon::tetragon_perimeter() {
	return side1 + side2 + side3 + side4;
}

double Tetragon::tetragon_area() {
	Triangle t1, t2;
	t1.set(p1, p2, p3);
	t2.set(p1, p4, p3);
	return t1.area() + t2.area();
}

Tetragon Tetragon::create_middletetragon() {
	Tetragon t;
	t.p1 = middlepoint(p1, p2);
	t.p2 = middlepoint(p2, p3);
	t.p3 = middlepoint(p3, p4);
	t.p4 = middlepoint(p1, p4);
	t.set(t.p1, t.p2, t.p3, t.p4);
	return t;
}

bool Tetragon::is_in(Point p)
{
	Tetragon T; T.set(p1, p2, p3, p4);
	Triangle T1, T2, T3, T4;
	T1.set(p1, p2, p);	T2.set(p2, p3, p); T3.set(p3, p4, p); T4.set(p1, p4, p);
	return (T1.area() + T2.area() + T3.area() + T4.area() == T.tetragon_area());
}