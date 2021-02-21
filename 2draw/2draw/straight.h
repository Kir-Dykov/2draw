#pragma once
#include "point.h"
class straight
{
public:
	point p1, p2;							//2 tochki, zadayshie pryamuy
	double a, b, c;							//koefficienti uravneniya pryamoi
	void set_straight_p(point, point);		//zadanie pryamoi cherez 2 tocki
	void set_straight_abc(int, int, int);	//zadanie pryamoi uravneniem
	double get_straight_radangle();			//vichislenie ugla mezhdu pryamoi i osiu Ox v radianah
	double get_straight_degangle();			//vichislenie ugla mezhdu pryamoi i osiu Ox v gradusah
	bool operator==(straight);				//operator sovpadenia dvuh pryamih
	void cout_straight();					//vivod uravneniya pryamoi
};

straight perp_straight(straight);			//sozdanie pryamoi, perpendiculyarnoi dannoi
bool parallel_straight(straight, straight);	//opredelenie parallelnosti dvuh pryamih
bool point_on_straight(point, straight);	//opredelenie prinadlezhnosti tochki pryamoi