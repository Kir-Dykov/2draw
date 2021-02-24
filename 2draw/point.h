#pragma once
#include <iostream>
using namespace std;
class point
{
public:
	void set_point(int, int);   //zadanie tochki:													p.set_point()
	int find_quarter();    //nahozhdenie chetverti v kotoroy nahoditsa tochka:						p.find_quarter() 
	void cout_point();     //vivod koordinat tochki d konsol:										p.cout_point()
	bool operator==(point); 
	double x, y;	//koordinati x y
};

//Funkcii ot tochek:
point sym_point_x(point);   //sozdanie tochki, simmetrichnoi zadannoi otnositelno osi Ox:			q = sym_point_x(p)
point sym_point_y(point);   //sozdanie tochki, simmetrichnoi zadannoi otnositelno osi Îy:			q = sym_point_y(p)
double point_distance(point p1, point p2); //vichislenie rasstoyaniya mezhdy tochkami:				r = point_distance(p1, p2)