#include "vector.h"

double determinant(Vector a, Vector b) { return a.getx() * b.gety() - a.gety() * b.getx(); }