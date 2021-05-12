#include "command_line.h"

//NEVER erase from that vector.
vector<CommandLine> commands;

CommandLine::CommandLine(double _x, double _y) {
	x = _x;
	y = _y;
	index = commands.size()-1;
}

void CommandLine::DeleteObject() {
	for (size_t i = 0; i < dependencies.size(); i++) {
		for (size_t j = 0; j < commands[i].dependent_from_this.size(); j++) {
			if (commands[i].dependent_from_this[j] == index) {
				commands[i].dependent_from_this.erase(commands[i].dependent_from_this.begin() + j);
				break;
			}
		}
	}
	delete obj;
	obj = nullptr;
}

void CommandLine::Compile() {

	type = "";
	symbol = "";
	
	std::istringstream iss(command);
	string keyword;

	if (command == "") {
		DeleteObject();
		goto success;
	}

parse_start:
	cout << "Compiling a command!" << endl;
	iss >> keyword;
	if (keyword == "point") {
		double x, y;
		iss >> x >> y;
		if (iss.fail()) {
			iss.clear();
			goto error;
		}
		if (type != "point") {
			DeleteObject();
			obj = new Point(x, y);
			type = "point";
		}
		else {
			((Point*)obj)->set(x, y);
		}		
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
	else if (keyword == "triangle") {
		string p1, p2, p3;
		iss >> p1 >> p2 >> p3;
		CommandLine* pp1 = nullptr, * pp2 = nullptr, * pp3 = nullptr;
		for (size_t i = 0; i < commands.size(); i++) {
			if (commands[i].symbol == p1 && commands[i].type == "point") pp1 = &(commands[i]);
			if (commands[i].symbol == p2 && commands[i].type == "point") pp2 = &(commands[i]);
			if (commands[i].symbol == p3 && commands[i].type == "point") pp3 = &(commands[i]);
		}
		if (pp1 == nullptr || pp2 == nullptr || pp3 == nullptr) {
			goto error;
		}
		obj = new Triangle(*(Point*)(pp1->obj), *(Point*)(pp2->obj), *(Point*)(pp3->obj));
		pp1->dependent_from_this.push_back(index);
		pp2->dependent_from_this.push_back(index);
		pp3->dependent_from_this.push_back(index);
		dependencies.push_back(pp1->index);
		dependencies.push_back(pp2->index);
		dependencies.push_back(pp3->index);

		type = "triangle";
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
			if (commands[i].symbol == circle1 && commands[i].type == "circle") c1 = (Circle*)commands[i].obj;
			if (commands[i].symbol == circle2 && commands[i].type == "circle") c2 = (Circle*)commands[i].obj;
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

void CommandLine::CompileDependencies() {
	for (size_t i = 0; i < dependent_from_this.size(); i++) {
		commands[dependent_from_this[i]].Compile();
	}
};


void CommandLine::Draw() {
	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
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