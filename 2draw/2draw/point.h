#pragma once
#include <iostream>
using namespace std;
class point
{
public:
	void set_point(int, int);   //������� �����:													p.set_point()
	int find_quarter();    //���������� ��������, � ������� ��������� �����							p.find_quarter() 
	void cout_point();     //������� ���������� ����� � �������										p.cout_point()
double x, y;	//���������� x, y
};

//������� �� �����:
point sym_point_x(point);   //�������� �����, ������������ �������� ������������ ��� �x				q = sym_point_x(p)
point sym_point_y(point);   //�������� �����, ������������ �������� ������������ ��� �y				q = sym_point_y(p)
double point_distance(point p1, point p2); //���������� ���������� ����� ��������� �������			r = point_distance(p1, p2)