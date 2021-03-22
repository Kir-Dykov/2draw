#include "tetragon.h"
#include "triangle.h"
#include "vector.h"
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

bool Tetragon::is_in(Point p) {
	Tetragon T; T.set(p1, p2, p3, p4);
	Triangle T1, T2, T3, T4;
	T1.set(p1, p2, p);	T2.set(p2, p3, p); T3.set(p3, p4, p); T4.set(p1, p4, p);
	return (T1.area() + T2.area() + T3.area() + T4.area() == T.tetragon_area());
}
// find oppose points for vertex p1; idea: find one edge and if she not belonge tetragon sides then this edge is diagonal
Point Tetragon::find_oppose_vertforp1() {
	double distance12 = point_distance(p1, p2);
	if (distance12 != side1 && distance12 != side2 && distance12 != side3 && distance12 != side4) {
		return p2;
	}
	double distance13 = point_distance(p1, p3);
	if (distance13 != side1 && distance13 != side2 && distance13 != side3 && distance13 != side4) {
		return p3;
	}
	double distance14 = point_distance(p1, p4);
	if (distance14 != side1 && distance14 != side2 && distance14 != side3 && distance14 != side4) {
		return p4;
	}
}
Point Tetragon::find_oppose_vertforp2() {
	double distance21 = point_distance(p2, p1);
	if (distance21 != side1 && distance21 != side2 && distance21 != side3 && distance21 != side4) {
		return p1;
	}
	double distance23 = point_distance(p2, p3);
	if (distance23 != side1 && distance23 != side2 && distance23 != side3 && distance23 != side4) {
		return p3;
	}
	double distance24 = point_distance(p2, p4);
	if (distance24 != side1 && distance24 != side2 && distance24 != side3 && distance24 != side4) {
		return p4;
	}
}
Point Tetragon::find_oppose_vertforp3() {
	double distance31 = point_distance(p3, p1);
	if (distance31 != side1 && distance31 != side2 && distance31 != side3 && distance31 != side4) {
		return p1;
	}
	double distance32 = point_distance(p3, p2);
	if (distance32 != side1 && distance32 != side2 && distance32 != side3 && distance32 != side4) {
		return p2;
	}
	double distance34 = point_distance(p3, p4);
	if (distance34 != side1 && distance34 != side2 && distance34 != side3 && distance34 != side4) {
		return p4;
	}
}
Point Tetragon::find_oppose_vertforp4() {
	double distance41 = point_distance(p4, p1);
	if (distance41 != side1 && distance41 != side2 && distance41 != side3 && distance41 != side4) {
		return p1;
	}
	double distance42 = point_distance(p4, p2);
	if (distance42 != side1 && distance42 != side2 && distance42 != side3 && distance42 != side4) {
		return p2;
	}
	double distance43 = point_distance(p4, p3);
	if (distance43 != side1 && distance43 != side2 && distance43 != side3 && distance43 != side4) {
		return p3;
	}
}

Point Tetragon::find_oppose_vert(Point p) {
	if (p == p1) {
		return find_oppose_vertforp1();
	}
	else if (p == p2) {
		return find_oppose_vertforp2();
	}
	else if (p == p3) {
		return find_oppose_vertforp3();
	}
	else if (p == p4) {
		return find_oppose_vertforp4();
	}
}

Circle Tetragon::get_inscribed_circle() {
	Point tmp_p1 = find_oppose_vert(p1);
	if (!(tmp_p1 == p2)) {
		Circle res;
		Point tmp_p2 = find_oppose_vert(p2);
		if (point_distance(p1, p2) + point_distance(p1, tmp_p2) == point_distance(tmp_p1, p2) + point_distance(tmp_p1, tmp_p2)) {
			Triangle tr_p1,tr_p2;
			tr_p1.set(p1, p2, tmp_p2);
			tr_p2.set(tmp_p1, p2, p1);
			double anglep1 = tr_p1.get_triangle_angle(1);
			double anglep2 = tr_p2.get_triangle_angle(2);
			Line bisp1 = tr_p1.get_bisectrix(1);
			Line bisp2 = tr_p2.get_bisectrix(2);
			res.set(Line::findpointincrs(bisp1, bisp2), tetragon_area() / tetragon_perimeter());
			return res;
		}
		else {
			std::cout << "The inscribed circle is impossible";
		}
	}
	else if (!(tmp_p1 == p3)) {
		Circle res;
		Point tmp_p2 = find_oppose_vert(p3);
		if (point_distance(p1, p3) + point_distance(p1, tmp_p2) == point_distance(tmp_p1, p3) + point_distance(tmp_p1, tmp_p2)) {
			Triangle tr_p1, tr_p2;
			tr_p1.set(p1, p3, tmp_p2);
			tr_p2.set(tmp_p1, p3, p1);
			double anglep1 = tr_p1.get_triangle_angle(1);
			double anglep2 = tr_p2.get_triangle_angle(2);
			Line bisp1 = tr_p1.get_bisectrix(1);
			Line bisp2 = tr_p2.get_bisectrix(2);
			res.set(Line::findpointincrs(bisp1, bisp2), tetragon_area() / tetragon_perimeter());
			return res;
		}
		else {
			std::cout << "The inscribed circle is impossible";
		}
	}
}