#pragma once
#include "../line.h"

using namespace std;

int line_main() {
	Line a, b, m;
	Point p1, p2;
	p1.set_point(2, 1);
	p2.set_point(1, 4);
	a.set_line(1, 1, 2);
	b.set_line(p1, p2);
	cout << "Lines: " << endl;
	a.cout_line();
	b.cout_line();
	cout << "Are lines parallel?: ";
	cout << are_parallel(a, b) << endl;
	cout << "Point p: ";
	p1.cout_point();
	cout << endl;
	cout << "Is p laying on the a-line?: ";
	cout << point_on_Line(p1, a) << endl;
	cout << "The angle between a-line and b-line is: " << get_twoLines_degangle(a, b) << endl;
	return 0;
}