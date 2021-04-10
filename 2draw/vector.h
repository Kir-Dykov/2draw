#pragma once

#include <math.h>
using namespace std;

class Vector
{
public:
	double x, y;	//koordinati x y

	Vector(double _x = 0, double _y = 0) { x = _x; y = _y; }
	Vector(const Vector& other) { x = other.x; y = other.y; }
	void set(double _x, double _y) { x = _x; y = _y; }

	bool operator==(const Vector other) const{ return other.x==x && other.y==y; }
	bool operator!=(const Vector other) const{ return other.x != x || other.y != y; }

	Vector operator+(const Vector other) const{ return Vector(x + other.x, y + other.y); }
	Vector operator-(const Vector other) const{ return Vector(x - other.x, y - other.y); }
	double operator*(const Vector other) const{ return x * other.x + y * other.y; } //dot product
	Vector operator*(const double lambda)const{ return Vector(x*lambda, y*lambda); } // miltiplication by a number

	double abs() const{ return sqrt(x * x + y * y); }
	double arg() const{ return atan2(x, y); }

	friend double determinant(Vector, Vector); // determinant of the 2x2 matrix formed by two vector-column's
	friend double dot(Vector, Vector);
	friend double cos(Vector, Vector);

};

