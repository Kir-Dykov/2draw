#pragma once
#include "point.h"
class straight
{
public:
	point p1, p2;							//2 tochki, zadayshie pryamuy							
	double a, b, c;							//koefficienti uravneniya pryamoi
	void set_straight_p(point, point);		//zadanie pryamoi cherez 2 tocki (uravnenie zadayotsa avtomatichski) L.set_straight_p(p1, p2)
	void set_straight_abc(int, int, int);	//zadanie pryamoi uravneniem							L.set_straight_abc(a, b, c)
	double get_straight_radangle();			//vichislenie ugla mezhdu pryamoi i osiu Ox v radianah	a = L.get_straight_radangle()
	double get_straight_degangle();			//vichislenie ugla mezhdu pryamoi i osiu Ox v gradusah	a = L.get_straight_degangle()
	bool operator==(straight);				//operator sovpadenia dvuh pryamih						L1 == L2
	void cout_straight();					//vivod uravneniya pryamoi								L.cout_straight()
};

straight perp_straight(straight);			//sozdanie pryamoi, perpendiculyarnoi dannoi			L2 = perp_straight(L1)
bool parallel_straight(straight, straight);	//opredelenie parallelnosti dvuh pryamih				bool f = parallel_straight(L1, L2)
bool point_on_straight(point, straight);	//opredelenie prinadlezhnosti tochki pryamoi			bool f = point_on_straight(p, L)