#include "vector.h"
#include <math.h>
double determinant(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

<<<<<<< HEAD
double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; };
double cos(Vector a, Vector b) {return (a.x * b.x + a.y * b.y)/sqrt((a.x*a.x + a.y*a.y)*(b.x*b.x + b.y*b.y));}
=======
double determinant(Vector a, Vector b) { return a.getx() * b.gety() - a.gety() * b.getx(); }
>>>>>>> ff87574ec63aa7b3c1da036d3b5158d3557b7b46
