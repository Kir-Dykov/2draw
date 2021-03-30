#pragma once
#include "point.h"

class Line
{
public:
	Point p1, p2;							//2 tochki, zadayshie pryamuy							
	double a, b, c;							//koefficienti uravneniya pryamoi

	void set_line(Point, Point);		//zadanie pryamoi cherez 2 tocki (uravnenie zadayotsa avtomatichski) L.set(p1, p2)
	void set_line(int, int, int);	//zadanie pryamoi uravneniem							L.set(a, b, c)

	double get_angle_rad();			//vichislenie ugla mezhdu pryamoi i osiu Ox v radianah	a = L.get_angle_rad()
	double get_angle_deg();			//vichislenie ugla mezhdu pryamoi i osiu Ox v gradusah	a = L.get_angle_deg()

	void cout_line();					//vivod uravneniya pryamoi								L.cout_Line()

	bool operator==(const Line);				//operator sovpadenia dvuh pryamih						L1 == L2
};
std::ostream& operator<<(std::ostream& os, const Line& l);
Line perp_Line(const Line);			//sozdanie pryamoi, perpendiculyarnoi dannoi			L2 = perp_Line(L1)
bool are_parallel(const Line, const Line);	//opredelenie parallelnosti dvuh pryamih				bool f = are_parallel(L1, L2)
bool point_on_Line(const Point, const Line);	//opredelenie prinadlezhnosti tochki pryamoi			bool f = point_on_Line(p, L)

double get_twoLines_radangle(const Line, const Line); //nahozhdenie ugla mezhdu pryamimi v radianah	double a = get_twoLines_radangle
double get_twoLines_degangle(const Line, const Line); //nahozhdenie ugla mezhdu pryamimi v gradusah double a = get_twoLines_degangle
int find_halfplane(const Line, const Point);    //v kakoi poluploskosti ot pryamoi lezhit tochka  int f = find_halfplane(Line L, point p);
																				//1 - vishe pryamoi, -1 - nizhe pryamoi, 0 - na pryamoi