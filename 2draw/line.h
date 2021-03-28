#pragma once
#include "point.h"

class Line
{
private:
	Point p1, p2;							//2 tochki, zadayshie pryamuy							
	double a, b, c;							//koefficienti uravneniya pryamoi
public:
	void set(Point, Point);		//zadanie pryamoi cherez 2 tocki (uravnenie zadayotsa avtomatichski) L.set(p1, p2)
	void set(double, double, double);	//zadanie pryamoi uravneniem							L.set(a, b, c)

	double get_angle_rad() const;			//vichislenie ugla mezhdu pryamoi i osiu Ox v radianah	a = L.get_angle_rad()
	double get_angle_deg() const;			//vichislenie ugla mezhdu pryamoi i osiu Ox v gradusah	a = L.get_angle_deg()

	void cout_line() const;					//vivod uravneniya pryamoi								L.cout_Line()

	bool point_line_belonging(Point) const; // returns 1 if point belongs to line and 0 otherwise

	bool operator==(Line) const;				//operator sovpadenia dvuh pryamih						L1 == L2
	//find increase points by two lines
	static Point findpointincrs(Line, Line);

	friend Line perpendicular(Line);			//sozdanie pryamoi, perpendiculyarnoi dannoi			L2 = perpendicular(L1)
	friend bool are_parallel(Line, Line);	//opredelenie parallelnosti dvuh pryamih				bool f = are_parallel(L1, L2)
	friend bool point_on_Line(Point, Line);	//opredelenie prinadlezhnosti tochki pryamoi			bool f = point_on_Line(p, L)

	friend double get_twoLines_radangle(Line, Line); //nahozhdenie ugla mezhdu pryamimi v radianah	double a = get_twoLines_radangle
	friend double get_twoLines_degangle(Line, Line); //nahozhdenie ugla mezhdu pryamimi v gradusah double a = get_twoLines_degangle
	friend int find_halfplane(Line, Point);    //v kakoi poluploskosti ot pryamoi lezhit tochka  int f = find_halfplane(Line L, point p);
																					//1 - vishe pryamoi, -1 - nizhe pryamoi, 0 - na pryamoi
};

