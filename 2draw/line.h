#pragma once
#include "point.h"
class Line
{
public:
	point p1, p2;							//2 tochki, zadayshie pryamuy							
	double a, b, c;							//koefficienti uravneniya pryamoi
	void set(point, point);		//zadanie pryamoi cherez 2 tocki (uravnenie zadayotsa avtomatichski) L.set(p1, p2)
	void set(int, int, int);	//zadanie pryamoi uravneniem							L.set(a, b, c)
	double get_angle_rad();			//vichislenie ugla mezhdu pryamoi i osiu Ox v radianah	a = L.get_angle_rad()
	double get_angle_deg();			//vichislenie ugla mezhdu pryamoi i osiu Ox v gradusah	a = L.get_angle_deg()
	bool operator==(Line);				//operator sovpadenia dvuh pryamih						L1 == L2
	void print();					//vivod uravneniya pryamoi								L.cout_Line()
};

Line perp_Line(Line);			//sozdanie pryamoi, perpendiculyarnoi dannoi			L2 = perp_Line(L1)
bool are_parallel(Line, Line);	//opredelenie parallelnosti dvuh pryamih				bool f = are_parallel(L1, L2)
bool point_on_Line(point, Line);	//opredelenie prinadlezhnosti tochki pryamoi			bool f = point_on_Line(p, L)
double get_twoLines_radangle(Line, Line); //nahozhdenie ugla mezhdu pryamimi v radianah	double a = get_twoLines_radangle
double get_twoLines_degangle(Line, Line); //nahozhdenie ugla mezhdu pryamimi v gradusah double a = get_twoLines_degangle