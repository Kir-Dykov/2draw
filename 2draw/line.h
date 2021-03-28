#pragma once
#include "point.h"

class Line
{
private:						
	double _a, _b, _c;							//koefficienti uravneniya pryamoi
public:
	const double& a = _a;
	const double& b = _b;
	const double& c = _c;


	Line() {}
	Line(const double A, const double B, const double C) { _a = A; _b = B; _c = C; }
	Line(const Line& L) { _a = L.a; _b = L.b; _c = L.c; };
	Line& operator=(const Line& L) { _a = L.a; _b = L.b; _c = L.c; return *this; }; // not sure if I did it right (potential bug)

	//setters
	void set(Point, Point);
	void set(double A = 1, double B = 1, double C = 0) {_a = A;_b = B;_c = C;}
	void set_a(double A) { _a = A; }
	void set_b(double B) { _b = B; }
	void set_c(double C) { _c = C; }

	double get_angle_rad() const;			//vichislenie ugla mezhdu pryamoi i osiu Ox v radianah	a = L.get_angle_rad()
	double get_angle_deg() const;			//vichislenie ugla mezhdu pryamoi i osiu Ox v gradusah	a = L.get_angle_deg()

	void cout_line() const;					//vivod uravneniya pryamoi								L.cout_Line()

	bool point_line_belonging(Point) const; // returns 1 if point belongs to line and 0 otherwise

	bool operator==(const Line) const;				//operator sovpadenia dvuh pryamih						L1 == L2
	//find increase points by two lines
	static Point findpointincrs(const Line, const Line);

	friend Line perpendicular(const Line);			//sozdanie pryamoi, perpendiculyarnoi dannoi			L2 = perpendicular(L1)
	friend bool are_parallel(const Line, const Line);	//opredelenie parallelnosti dvuh pryamih				bool f = are_parallel(L1, L2)
	friend bool point_on_Line(const Point, const Line);	//opredelenie prinadlezhnosti tochki pryamoi			bool f = point_on_Line(p, L)

	friend double get_twoLines_radangle(const Line, const Line); //nahozhdenie ugla mezhdu pryamimi v radianah	double a = get_twoLines_radangle
	friend double get_twoLines_degangle(const Line, const Line); //nahozhdenie ugla mezhdu pryamimi v gradusah double a = get_twoLines_degangle
	friend int find_halfplane(const Line, const Point);    //v kakoi poluploskosti ot pryamoi lezhit tochka  int f = find_halfplane(Line L, point p);
																					//1 - vishe pryamoi, -1 - nizhe pryamoi, 0 - na pryamoi
};

