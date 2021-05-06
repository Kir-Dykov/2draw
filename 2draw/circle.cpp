#include "circle.h"

Circle::Circle(double _x = 0, double _y = 0, double _r = 1) {
	c.x = _x;
	c.y = _y;
	r = _r;
}

Circle::Circle() {
	c.x = 0;
	c.y = 0;
	r = 1;
}

void Circle::set(const Point _center, const double _radius) {
	c.x = _center.x;
	c.y = _center.y;
	r = _radius;
}

void Circle::set(const Point _center, const Point other) {
	c = _center;
	r = distance(c, other);
}

std::ostream& operator<<(std::ostream& os, const Circle& cir) {
	os << "radius: " << cir.radius << ", center: " << cir.center;
	return os;
}

std::vector<Point> Circle::intersections(const Circle other) const {
	// Algorithm: https://planetcalc.ru/8098/?license=1
	double centers_distance = distance(c, other.center);
	if (centers_distance == 0 && r == other.radius) {		// coincide
		return { c, other.c };
	}
	else if (centers_distance > r + other.radius) {			// don't intersect
		return std::vector<Point>(0);
	}
	else if (centers_distance < abs(r - other.r)) {		// one to the other
		return std::vector<Point>(0);
	}
	else // touch or intersect at two points
	{
		double a = (r * r - other.r * other.r + \
			centers_distance * centers_distance) / (2 * centers_distance);
		double h = sqrt(r * r - a * a);
		Point tmp_pnt;
		tmp_pnt.x = c.x + a / centers_distance * (other.c.x - c.x);
		tmp_pnt.y = c.y + a / centers_distance * (other.c.y - c.y);
		Point first_intersection, second_intersection;
		first_intersection.x = tmp_pnt.x + h / centers_distance * (other.c.y - c.y);
		first_intersection.y = tmp_pnt.y - h / centers_distance * (other.c.x - c.x);
		second_intersection.x = tmp_pnt.x - h / centers_distance * (other.c.y - c.y);
		second_intersection.y = tmp_pnt.y + h / centers_distance * (other.c.x - c.x);
		if (first_intersection == second_intersection)
			return { first_intersection };
		else
			return { first_intersection, second_intersection };
	}
}

std::vector<Line> Circle::tangents(const Point p) const {
	//gроверка на принадлежность точки окр

	double dist = (p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y);
	if (dist == r * r) {
		Line linedist(Point(p.x, p.y), Point(center.x, center.y));
		Line ans = linedist.perp2point_on_line(Point(p.x, p.y));
		return { ans };
	}
	else if (dist > r * r) {
		double distcas = dist - r * r;
		Circle second(p.x, p.y, sqrt(distcas));
		std::vector<Point> tangen_points;
		tangen_points = (*this).intersections(second);
		Line first_tan(tangen_points[0], Point(p.x, p.y)), second_tan(tangen_points[1], Point(p.x, p.y));
		return { first_tan, second_tan };
	}
	else
		return std::vector<Line>(0);
}

std::vector<Point> Circle::intersections_line(const Point first, const Point second) const {
	double k = (first.y - second.y) / (first.x - second.x);
	double b = first.y - k * first.x;
	//находим дискриминант квадратного уравнения
	double d = (pow((2 * k * b - 2 * c.x - 2 * c.y * k), 2) - (4 + 4 * k * k) * (b * b - r * r + c.x * c.x + c.y * c.y - 2 * c.y * b));

	//если он равен 0, уравнение не имеет решения
	if (d < 0)  return vector<Point>(0);

	//иначе находим корни квадратного уравнения
	double x1 = ((-(2 * k * b - 2 * c.x - 2 * c.y * k) - sqrt(d)) / (2 + 2 * k * k));
	double x2 = ((-(2 * k * b - 2 * c.x - 2 * c.y * k) + sqrt(d)) / (2 + 2 * k * k));
	//если абсциссы точек совпадают, то пересечение только в одной точке    
	if (x1 == x2) return { Point(x1, first.y) };
	//иначе находим ординаты точек пересечения 
	double y1 = k * x1 + b;
	double y2 = k * x2 + b;
	return { Point(x1,y1), Point(x2,y2) };
}


void Circle::Draw() const {
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(red, green, blue);/*rand() % 128 + 128*/
	const int N = 7*(int)(sqrt(radius));
	glVertex2f(center.x, center.y);
	float d_angle = 2 * PI / N;
	float angle = 0;
	for (int i = 0; i <= N; i++) {
		angle += d_angle;
		glVertex2f(radius * cos(angle) + center.x, radius * sin(angle) + center.y);
	}
	glEnd();
}