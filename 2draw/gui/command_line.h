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
#include "../polygon.h"

using namespace std;

extern GLint Width, Height;

// this class manages command lines, that define all 
// geometrical objects in programm,
//
// it primitively parses commands, creates objects,
// keeps track of dependencies, 
class CommandLine {
public:
	string command = "";

	// analagous to the variable names, it's used 
	string symbol = ""; 

	// for type checks
	string type = "";

	// pointer to the object
	Object* obj = nullptr;


	//index int in vector<CommandLine> commands, usefull for dependencies management
	size_t index = 0; 

	//lists the indexes (in vector<CommandLine> commands)
	//of objects that has to be updated
	//after this object changes
	vector<size_t> dependent_from_this;

	//lists the indexes of objects in which dependent_on field
	//chould be cleared after deletion of this object
	vector<size_t> dependencies;
	bool filled = 0;

	//colors for background of command line
	int r = 128, g = 128, b = 128;

	// definition of where the comand line is;
	double x, y, width=300, height=26;

	//constructor
	CommandLine(double _x, double _y);

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

	void DeleteObject();
	void AddDependancy(CommandLine& other);
	void AddDependancy(CommandLine* other);
	void ClearDependencies();

	/* after this.command was edited, this function can read it,
	* recreating object the command defines. In case of error
	* command line bocomes red and nothing is being created	*/
	void Compile();

	// this calls Compile() on everything from dependant_from_this
	void CompileDependencies();

	//Draws the command line box on the screen;
	void Draw();
};