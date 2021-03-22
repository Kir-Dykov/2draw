#pragma once
#include "point.h"
#include "line.h"
#include "circle.h"

class Tetragon {
public:
	Point p1, p2, p3, p4;
	Line l1, l2, l3, l4, d1, d2;    //pryamie, soderzhashie storoni i diagonali
	double side1, side2, side3, side4; //dlini storon
	void set(Point, Point, Point, Point); //zadanie chetiryohugolnika    Tetragon t.set(p1, p2, p3, p4)
	bool convex_tetragon();				//opredelenie vipuklosti		 bool f = t.convex_tetragon()
	double tetragon_perimeter();		//vichislenie perimetra			 double p = t.tetragon_perimeter()
	double tetragon_area();				//vichislenie ploshadi			 double s = t.tetragon_area()
	Tetragon create_middletetragon();	//sodanie chetiryohugolnika, opiraushigosya na seredini dannogo chetiryohugolnika 
	bool is_in(Point); // returns 1 if point belongs to tetragon and 0 otherwise
	Circle get_inscribed_circle();
	// find oppose points for vertex p1;
	Point find_oppose_vertforp1();
	Point find_oppose_vertforp2();
	Point find_oppose_vertforp3();
	Point find_oppose_vertforp4();
	// find oppose points for this vertex
	Point find_oppose_vert(Point);
};