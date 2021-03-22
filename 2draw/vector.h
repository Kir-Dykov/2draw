#pragma once

#include <math.h>
using namespace std;

class Vector
{
public:

	Vector(double _x = 0, double _y = 0) { x = _x; y = _y; }

	void set(double _x, double _y) { x = _x; y = _y; }
	double getx() { return x; }
	double gety() { return y; }

	bool operator==(Vector other) { return other.x==x && other.y==y; }
	bool operator!=(Vector other) { return other.x != x || other.y != y; }

	Vector operator+(Vector other) { return Vector(x + other.x, y + other.y); }
	Vector operator-(Vector other) { return Vector(x - other.x, y - other.y); }
	double operator*(Vector other) { return x * other.x + y * other.y; } //dot product
	Vector operator*(double lambda) { return Vector(x*lambda, y*lambda); } // miltiplication by a number

	double abs() { return sqrt(x * x + y * y); }
	double arg() { return atan2(x, y); }
private:
	double x, y;	//koordinati x y
};

double determinant(Vector, Vector);