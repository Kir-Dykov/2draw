#pragma once
#include "../tetragon.h"

using namespace std;

int tetragon_main() {
	Tetragon t;
	Point p1, p2, p3, p4;
	p1.set(3, 3);
	p2.set(0, 0);
	p3.set(0, 2);
	p4.set(3, 0);
	t.set(p1, p2, p3, p4);
	cout << "Is tetragon convex?: " << t.convex_tetragon() << endl;
	cout << "Tetragon's perimeter is: " << t.tetragon_perimeter() << endl;
	cout << "Tetragon's area is: " << t.tetragon_area() << endl;
	return 0;
}