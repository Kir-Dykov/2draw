#pragma once
#include "../line.h"

using namespace std;

int line_main() {
	Line a, b, m;
	Point p1, p2;
	p1.set(2, 0);
	p2.set(4, 0);
	a.set(1, 4, 0);
	b.set(p1, p2);
	cout << "Lines: " << endl;
	cout << a << endl;
	cout << b <<endl;

	//cout << endl << "Does p1 belong to a: " << a.point_line_belonging(p1) << endl;
	return 0;
}