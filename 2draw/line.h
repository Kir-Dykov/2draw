#pragma once
#include "point.h"

class Line
{
public:
	Point p1, p2;				//2 tochki, zadayshie pryamuy							
	double a, b, c;				//koefficienti uravneniya pryamoi

	//zadanie pryamoi cherez 2 tocki (uravnenie zadayotsa avtomatichski)
	void set(Point, Point);
	//zadanie pryamoi uravneniem
	void set(int, int, int);


	void set_argument_c(double _c) { c = _c; }
	//vichislenie ugla mezhdu pryamoi i osiu Ox v radianah
	double get_angle_rad();
	//vichislenie ugla mezhdu pryamoi i osiu Ox v gradusah
	double get_angle_deg();

	//operator sovpadenia dvuh pryamih
	bool operator==(const Line);
};
std::ostream& operator<<(std::ostream& os, const Line& l);
//sozdanie pryamoi, perpendiculyarnoi dannoi
Line perpendicular(const Line);
//opredelenie parallelnosti dvuh pryamih
bool are_parallel(const Line, const Line);
//opredelenie prinadlezhnosti tochki pryamoi
bool point_on_Line(const Point, const Line);

//nahozhdenie ugla mezhdu pryamimi v radianah	double
double get_twoLines_radangle(const Line, const Line);
//nahozhdenie ugla mezhdu pryamimi v gradusah double
double get_twoLines_degangle(const Line, const Line);
//v kakoi poluploskosti ot pryamoi lezhit tochka 1 - vishe pryamoi, -1 - nizhe pryamoi, 0 - na pryamoi
int find_halfplane(const Line, const Point);