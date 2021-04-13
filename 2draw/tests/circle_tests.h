#pragma once
#include "../circle.h"

int circle_main()
{
	Circle first, second, third;
	first.set(Point(0, 0), Point(2, 0));
	cout << first << endl;
	second.set(Point(0, 3), Point(0, 2));
	cout << second << endl;

	std::cout << "\nIntersections of circles: \n";
	for (auto i : first.intersections(second)) 
		std::cout << i << " ";
	std::cout << "\n";

	std::cout << endl << "Does (-1, 3) belong to the second circle: " << second.is_in(Point(-1, 3)) << endl;
	
	std::cout << "\nTangents of circles: \n";
	for (auto i : first.tangents(Point(8,7)))
		std::cout << i << " ";
	std::cout << "\n";
	return 0;
}