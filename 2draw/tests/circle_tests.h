#pragma once
#include "../circle.h"

int circle_main()
{
	Circle first, second, third;
	first.set(Point(0, 0), Point(2, 0));
	cout << first << endl;
	second.set(Point(0, 3), Point(0, 2));
	cout << second << endl;

	std::cout << "\nIntersections of cicles: \n\t";
	for (auto i : intersections(first, second)) 
		cout << i << " ";
	std::cout << "\n";

	std::cout << endl << "Does (-1, 3) belong to the second circle: " << second.is_in(Point(-1, 3)) << endl;
	return 0;
}