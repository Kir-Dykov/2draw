#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include "glut.h"

#include "gui.h"
#include "../object.h"
#include "../point.h"
#include "../circle.h"

using namespace std;

extern GLint Width, Height;

class CommandLine {
public:
	string command = "";
	string symbol = "";
	string type = "";
	vector<string> dependent;
	vector<string> dependency;

	bool filled = 1;

	int r = 128, g = 128, b = 128;


	Object* obj = nullptr;

	double x, y, width=300, height=22, margin = 3;
	CommandLine(double _x, double _y) {
		x = _x;
		y = _y;
	}
	void set_location(double _x, double _y) {
		x = _x;
		y = _y;
	}

	bool is_in(double _x, double _y) {
		_y = Height - _y;
		return (_x > x && _x < x + width && _y > y && _y < y + height);
	}

	void Compile();
	void Draw();
};

void Draw(const CommandLine&);