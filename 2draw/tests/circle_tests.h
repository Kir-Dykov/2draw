#pragma once
#include "../circle.h"

int circle_main()
{
	Circle first, second, third;
	first.set_circle(Point(1, 3), 3);
	Circle::cout_circle(first);
	second.set_circleby2p(Point(1, 5), Point(3, 7));
	Circle::cout_circle(second);
	std::cout << "\nDistance point to circle: "<<Circle::get_dist_pnttocir(Point(10, 9), second);
	std::cout << "\nDistance point to circle: " << Circle::get_dist_pnttocir(Point(10, 9), first);
	Circle::find_cros_2circlespnts(first, second);

	cout << endl << "Does (-1, 3) belong to second: " << second.point_circle_belonging(Point(-1, 3)) << endl;
	return 0;
}