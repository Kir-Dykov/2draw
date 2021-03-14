#pragma once
#include "../point.h"

using namespace std;

int point_main() {
	Point a, b, m;
	a.set_point(1, 1);
	b.set_point(2, 3);
	cout << "A's quarter is - " << a.find_quarter() << endl;
	cout << "Point B is - ";
	b.cout_point();
	cout << endl;
	m = middlepoint(a, b);
	cout << "A, B's middle point is - ";
	m.cout_point();
	cout << endl;

	return 0;
}