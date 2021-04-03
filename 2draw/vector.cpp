#include "vector.h"
#include <math.h>
double determinant(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }


double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; };
double cos(Vector a, Vector b) { return (a.x * b.x + a.y * b.y)/sqrt((a.x*a.x + a.y*a.y)*(b.x*b.x + b.y*b.y)); }