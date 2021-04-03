#pragma once
#include "../point.h"

using namespace std;

int point_main() {
	Point a, b, m;
	a.set(1, 1);
	b.set(2, 3);
	cout << "A's quarter is - " << a.find_quarter() << endl;
	cout << "Point B is - ";
	cout << b << endl;
	m = a.middlepoint(b);
	cout << "A, B's middle point is - ";
	cout << m << endl;

	return 0;
}