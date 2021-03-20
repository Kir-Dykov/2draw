#pragma once
#include "../triangle.h"

using namespace std;

int triangle_main() 
{
	Triangle t, s;
	Line bis, alt, med, mid, perp;
	Circle cir;

	Point p1, p2, p3;
	p1.set_point(0, 2);
	p2.set_point(2, 0);
	p3.set_point(6, 6);
	t.set(p1, p2, p3);

	cout << t << endl;

	cout << "Triangle area: " << t.area() << endl;

	cout << "Triangle angles: ";
	for (int i = 1; i <= 3; i++)
		cout << t.get_triangle_angle(i) << "  ";
	cout << endl;

	cout << "Triangle bisectrix: ";
	bis = t.get_bisectrix(1);
	bis.cout_line();
	cout << endl;

	cout << "Triangle altitude: ";
	alt = t.get_altitude(2);
	alt.cout_line();
	cout << endl;

	cout << "Triangle median: ";
	med = t.get_median(3);
	med.cout_line();
	cout << endl;

	cout << "Triangle midline: ";
	mid = t.get_midline(3);
	mid.cout_line();
	cout << endl;

	cout << "Triangle perp. bisector: ";
	perp = t.get_perp_bis(3);
	perp.cout_line();
	cout << endl;

	cout << "Tetragon circumcircle: ";
	cir = t.get_circumcircle();
	cir.cout_circle(cir);
	cout << endl;

	cout << "Tetragon inscribed circle: ";
	cir = t.get_inscribed_circle();
	cir.cout_circle(cir);
	cout << endl;

	cout << "Triangle type: " << t.triangle_type() << endl;

	Point r1, r2, r3;
	r1.set_point(0, 6.5);
	r2.set_point(0, 5);
	r3.set_point(-2, 5);
	s.set(r1, r2, r3);

	cout << "Is t congruent to s: " << t.are_congruent(s) << endl;
	cout << "Is t similar to s: " << t.are_similar(s) << endl;

	cout << endl << "Does r1 belong to t: " << t.is_in(r1) << endl;
	return 0;
}