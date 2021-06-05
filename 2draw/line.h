#pragma once
#include "point.h"
#include "object.h"
#include "consts.h"

class Line : public Object {
private:
	Point p1, p2;
	double a, b, c;
public:
	Line() { p1.x = 0; p2.x = 1; p1.y = 0; p2.y = 1; a = 1; b = -1; c = 0; };
	Line(const Line& other) { p1 = other.p1; p2 = other.p2; a = other.a; b = other.b; c = other.c; }
	Line(const double, const double, const double);
	Line(const Point&, const Point&);

	// Setters
	// set line by 2 points
	void set(const Point&, const Point&);
	// set line by coeffietients of its equation
	void set(double, double, double);
	// set the C coeffitient of line
	void set_argument_c(const double& _c) { c = _c; }

	// Getters
	double get_a() const { return a; }
	double get_b() const { return b; }
	double get_c() const { return c; }
	// angle between line and Ox in radians
	double get_angle_rad() const { return atan(-a / b); }
	// ... in degrees
	double get_angle_deg() const { return atan(-a / b) * 180 / PI; }

	// Other functions
	// are lines parallel
	bool is_parallel_to(const Line& L) const { return a * L.b == b * L.a; }

	// point line belonging
	bool point_on_Line(const Point& p) const { return p.x * a + p.y * b + c == 0; }

	// angle between 2 lines in radians
	double get_twoLines_radangle(const Line&) const;
	// ... in degrees
	double get_twoLines_degangle(const Line&) const;
	// finding point halfplane 1 - above the line, -1 - below the line, 0 - on a line
	int find_halfplane(const Point&) const;

	// finding a line perpendicular to the given line
	Line perpendicular() const { return Line(b, -a, c); }

	// finding a perpendicular to the line, that goes thrue point
	Line perp2point_on_line(const Point& pnt) const { return Line(-b, a, -a * pnt.y + b * pnt.x); }

	// finds the intersection point of two lines
	Point intersection(const Line&) const;

	// finds a parallel line through the point
	// 3th param is value, such that when we plug-in point P into formula a*x+b*y+c we get 0
	Line parallel(const Point& p) const { return Line(a, b, -a * p.x - b * p.y); }

	// Operators
	bool operator==(const Line& L) const { return a / L.a == b / L.b && b / L.b == c / L.c; }

	void Draw() const;

	friend std::ostream& operator<<(std::ostream&, const Line&);

	friend class Triangle;
	friend class Polygon;
};