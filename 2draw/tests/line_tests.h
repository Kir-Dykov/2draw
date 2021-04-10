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
	cout << a << endl;
	cout << b <<endl;
	cout << "Are lines parallel?: ";
	cout << a.is_parallel_to(b) << endl;
	cout << "Point p: ";
	cout << p1 << endl;
	cout << "Is p laying on the a-line?: ";
	cout << a.point_on_Line(p1) << endl;
	cout << "The angle between a-line and b-line is: " << a.get_twoLines_radangle(b) << endl;

	Point p3;
	p3.set(-1.4, 2.1212323);
	cout << "Is point lower or higher than a-line: " << a.find_halfplane(p3) << endl;
	cout << "Is point lower or higher than b-line: " << b.find_halfplane(p3) << endl;

	//cout << endl << "Does p1 belong to a: " << a.point_line_belonging(p1) << endl;
	return 0;
}