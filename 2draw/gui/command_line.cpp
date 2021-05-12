#include "command_line.h"

vector<CommandLine> commands;

void CommandLine::Compile() {
	cout << "Compiling a command!" << endl;

	type = "";
	symbol = "";
	delete obj;
	obj = nullptr;
	std::istringstream iss(command);
	string keyword;

	if (command == ""){
		goto success;
	}
	
parse_start:

	iss >> keyword;
	if (keyword == "point") {
		double x, y;
		iss >> x >> y;
		if (iss.fail()) {
			iss.clear();
			goto error;
		}
		obj = new Point(x, y);
		type = "point";

	}
	else if (keyword == "circle") {
		double x, y, r;
		iss >> x >> y >> r;
		if (iss.fail()) {
			iss.clear();
			goto error;
		}
		obj = new Circle(x, y, r);
		type = "circle";
	}
	else if (keyword == "intersection") {
		string circle1, circle2;
		iss >> circle1 >> circle2;
		if (circle1 == circle2) {
			goto error;
		}
		Circle* c1 = nullptr;
		Circle* c2 = nullptr;
		for (size_t i = 0; i < commands.size(); i++) {
			if (commands[i].symbol == circle1 && commands[i].type == "circle") {
				c1 = (Circle*)commands[i].obj;
			}
			if (commands[i].symbol == circle2 && commands[i].type == "circle") {
				c2 = (Circle*)commands[i].obj;
			}
		}
		if (c1 == nullptr || c2 == nullptr) {
			goto error;
		}
		vector<Point> pp = c1->intersections(*c2);
		cout << pp.size();
		obj = new Line(pp[0], pp[1]);
		type = "line";
	}
	else if (symbol != keyword) {
		symbol = keyword;
		goto parse_start;
	}
	else {
		goto error;
	}
	obj->filled = filled;
	goto success;

error:
	r = 192; g = 32; b = 0;
	return;
success:
	if (symbol == "") {
		symbol = command;
	}
	r = 128; g = 128; b = 128;
	return;

}

void CommandLine::Draw() {
	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);/*rand() % 128 + 128*/
	glVertex2f(x - margin, Height - (y - margin));
	glVertex2f(x + width + margin, Height - (y - margin));
	glVertex2f(x + width + margin, Height - (y + height));
	glVertex2f(x - margin, Height - (y + height));
	glEnd();

	glColor3ub(255, 255, 255);
	glRasterPos2f(x, Height - y - 12);
	for (int i = 0; i < command.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, command[i]);
	}
}