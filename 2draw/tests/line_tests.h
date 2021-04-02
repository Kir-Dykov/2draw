#pragma once
#include "../line.h"

using namespace std;

int line_main() {
	Line a, b, m;
	Point p1, p2;
	p1.set(10, 1);
	p2.set(2, 3);
	a.set(1, 4, 0);
	b.set(p1, p2);
	cout << "Lines: " << endl;
	a.cout_line();
	cout << endl;
	b.cout_line();
	cout << endl;
	cout << "Are lines parallel?: ";
	cout << are_parallel(a, b) << endl;
	cout << "Point p: ";
	cout << p1 << endl;
	cout << "Is p laying on the a-line?: ";
	cout << point_on_Line(p1, a) << endl;
	cout << "The angle between a-line and b-line is: " << get_twoLines_degangle(a, b) << endl;

	Point p3;
	p3.set(-1.4, 2.1212323);
	cout << "Is point lower or higher than a-line: " << find_halfplane(a, p3) << endl;
	cout << "Is point lower or higher than b-line: " << find_halfplane(b, p3) << endl;

	//cout << endl << "Does p1 belong to a: " << a.point_line_belonging(p1) << endl;
	return 0;
}