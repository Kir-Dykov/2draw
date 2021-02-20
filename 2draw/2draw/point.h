#pragma once
#include <iostream>
using namespace std;
class point
{
public:
	void set_point(int, int);   //задание точки:													p.set_point()
	int find_quarter();    //нахождение четверти, в которой находитс€ точка							p.find_quarter() 
	void cout_point();     //вывести координаты точки в консоль										p.cout_point()
double x, y;	//координаты x, y
};

//‘ункции от точек:
point sym_point_x(point);   //создание точки, симметричной заданной относительно оси ќx				q = sym_point_x(p)
point sym_point_y(point);   //создание точки, симметричной заданной относительно оси ќy				q = sym_point_y(p)
double point_distance(point p1, point p2); //вычисление рассто€ни€ между заданными точками			r = point_distance(p1, p2)