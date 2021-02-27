#pragma once
#include "line.h"

class tetragon {
public:
	point p1, p2, p3, p4;
	Line l1, l2, l3, l4, d1, d2;    //pryamie, soderzhashie storoni i diagonali
	double side1, side2, side3, side4; //dlini storon
	void set(point, point, point, point); //zadanie chetiryohugolnika    tetragon t.set(p1, p2, p3, p4)
	bool convex_tetragon();				//opredelenie vipuklosti		 bool f = t.convex_tetragon()
	double tetragon_perimeter();		//vichislenie perimetra			 double p = t.tetragon_perimeter()
	double tetragon_area();				//vichislenie ploshadi			 double s = t.tetragon_area()
	tetragon create_middletetragon();	//sodanie chetiryohugolnika, opiraushigosya na seredini dannogo chetiryohugolnika 
};