#include "command_line.h"

//NEVER erase from that vector.
vector<CommandLine> commands;

CommandLine::CommandLine(double _x, double _y) {
	x = _x;
	y = _y;
	index = commands.size();
}

void CommandLine::DeleteObject() {
	if (obj != nullptr){
		type = "";
		symbol = "";
		for (size_t i = 0; i < dependencies.size(); i++) {
			
			for (size_t j = 0; j < commands[dependencies[i]].dependent_from_this.size(); j++) {
				if (commands[dependencies[i]].dependent_from_this[j] == index) {
					commands[dependencies[i]].dependent_from_this.erase(commands[dependencies[i]].dependent_from_this.begin() + j);
					break;
				}
			}
		}
		delete obj;
		obj = nullptr;


	}
	
}

void CommandLine::Compile() {

	bool symbol_is_there = 0;

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
		int x, y;
		iss >> x >> y;
		if (iss.fail()) {
			iss.clear();
			x = rand() % 100 + 100;
			y = rand() % 100 + 100;
			if (symbol != "")
				command = symbol + " " + "point" + " " + to_string(x) + " " + to_string(y);
			else
				command = static_cast<string>("point ") + to_string(x) + " " + to_string(y);
		}
		if (type != "point") {
			DeleteObject();
			obj = new Point(x, y);
			type = "point";
		}
		else {
			((Point*)obj)->set(x, y);
			CompileDependencies();
		}
	}
	else if (keyword == "circle") {

		DeleteObject();
		int x, y, r;
		string p1, p2;
		iss >> p1;

		// if there are two coordinated and radius
		try {
			x = stoi(p1);
			iss >> y >> r;
			if (iss.fail()) {
				iss.clear();
				goto error;
			}
			obj = new Circle(x, y, r);
		}
		// if there are center point and radius
		catch(std::invalid_argument) {
			iss >> p2;
			try {
				r = stoi(p2);
				CommandLine* pp1 = nullptr;
				for (size_t i = 0; i < commands.size(); i++) {
					if (commands[i].symbol == p1 && commands[i].type == "point") pp1 = &(commands[i]);
				}
				if (pp1 == nullptr)
					goto error;

				obj = new Circle(*(Point*)(pp1->obj), r);

				pp1->dependent_from_this.push_back(index);
				dependencies.push_back(pp1->index);

			}
			// if there are center point and other point on circumference
			catch (const std::exception&)
			{
				CommandLine* pp1 = nullptr;
				CommandLine* pp2 = nullptr;
				for (size_t i = 0; i < commands.size(); i++) {
					if (commands[i].symbol == p1 && commands[i].type == "point") pp1 = &(commands[i]);
					if (commands[i].symbol == p2 && commands[i].type == "point") pp2 = &(commands[i]);
				}
				if (pp1 == nullptr || pp2 == nullptr) {
					goto error;
				}
				obj = new Circle(*(Point*)(pp1->obj), distance(*(Point*)(pp1->obj), *(Point*)(pp2->obj)));
				pp1->dependent_from_this.push_back(index);
				pp2->dependent_from_this.push_back(index);
				dependencies.push_back(pp1->index);
				dependencies.push_back(pp2->index);
			}
		}
		
		obj->filled = filled;
		type = "circle";
	}
	else if (keyword == "triangle") {		
		DeleteObject();
		string p1, p2, p3;
		iss >> p1 >> p2 >> p3;
		cout << p1 << p2 << p3;
		CommandLine* pp1 = nullptr, * pp2 = nullptr, * pp3 = nullptr;
		for (size_t i = 0; i < commands.size(); i++) {
			if (commands[i].symbol == p1 && commands[i].type == "point") pp1 = &(commands[i]);
			if (commands[i].symbol == p2 && commands[i].type == "point") pp2 = &(commands[i]);
			if (commands[i].symbol == p3 && commands[i].type == "point") pp3 = &(commands[i]);
		}
		if (pp1 == nullptr || pp2 == nullptr || pp3 == nullptr) {
			goto error;
		}
		cout << "im here" << endl;
		obj = new Triangle(*(Point*)(pp1->obj), *(Point*)(pp2->obj), *(Point*)(pp3->obj));
		obj->filled = filled;

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
	else if (!symbol_is_there) {
		symbol_is_there = true;
		symbol = keyword;
		goto parse_start;
	}
	else {
		goto error;
	}

	goto success;

error:
	r = 192; g = 32; b = 0;
	return;
success:
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