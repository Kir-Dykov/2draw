#pragma once
#include "../tetragon.h"

using namespace std;

int tetragon_main() {
	tetragon t;
	Point p1, p2, p3, p4;
	p1.set_point(0, 0);
	p2.set_point(2, 2);
	p3.set_point(3, 2);
	p4.set_point(3, 0);
	t.set(p1, p2, p3, p4);
	cout << "Is tetragon convex?: " << t.convex_tetragon() << endl;
	cout << "Tetragon's perimeter is: " << t.tetragon_perimeter() << endl;
	cout << "Tetragon's area is: " << t.tetragon_area() << endl;
	return 0;
}