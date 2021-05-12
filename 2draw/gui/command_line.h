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
#include "../triangle.h"

using namespace std;

extern GLint Width, Height;

// this class 
class CommandLine {
public:
	string command = "";

	// analagous to the variable names, it's used 
	string symbol = ""; 

	// for type checks
	string type = "";


	// pointer to the object
	Object* obj = nullptr;

	//lists the symbols of objects that has to be updated
	//after this object changes
	vector<string> dependency;

	bool filled = 1;

	//colors for background of command line
	int r = 128, g = 128, b = 128;

	// definition of where the comand line is;
	double x, y, width=300, height=22, margin = 3;

	//constructor
	CommandLine(double _x, double _y) {
		x = _x;
		y = _y;
	}
	//setter
	void set_location(double _x, double _y) {
		x = _x;
		y = _y;
	}

	//is neede to determine wether you clicked at it (to edit) or not
	bool is_in(double _x, double _y) {
		_y = Height - _y;
		return (_x > x && _x < x + width && _y > y && _y < y + height);
	}

	/* after this.command was edited, this function parses it,
	* recreating object the command defines. In case of error
	* command line bocomes red and nothing is being created	*/
	void Compile();

	//Draws the command line on the screen;
	void Draw();
};