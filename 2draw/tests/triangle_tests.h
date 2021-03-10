#pragma once
#include "../triangle.h"

using namespace std;

int triangle_main() 
{
	triangle t, s;
	Line bis, alt, med;
	Circle cir;

	Point p1, p2, p3;
	p1.set_point(0, 0);
	p2.set_point(3, 0);
	p3.set_point(0, 4);
	t.set_triangle(p1, p2, p3);

	cout << "Triangle area: " << t.triangle_area() << endl;

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
	s.set_triangle(r1, r2, r3);

	cout << "Is t congruent to s: " << t.are_congruent(s) << endl;
	cout << "Is t similar to s: " << t.are_similar(s) << endl;
	return 0;
}