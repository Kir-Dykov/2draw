#include "command_line.h"
/*
Actual avaliable commands that you can just type in right now

a point 400 400
b point
c point
t triangle a b c
c1 circle 300 400 50
c2 circle a 60
c3 circle a b
c4 incircle t
c5 circumcircle t
l1 line a b
*/

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
		CompileDependencies(); //to cause there errors as it should
		ClearDependencies();
		delete obj;
		obj = nullptr;
	}
}

void CommandLine::AddDependancy(CommandLine& other) {
	other.dependent_from_this.push_back(index);
	dependencies.push_back(other.index);
}

void CommandLine::AddDependancy(CommandLine* other) {
	other->dependent_from_this.push_back(index);
	dependencies.push_back(other->index);
}

void CommandLine::ClearDependencies() {
	for (size_t i = 0; i < dependencies.size(); i++) {
		for (size_t j = 0; j < commands[dependencies[i]].dependent_from_this.size(); j++) {
			if (commands[dependencies[i]].dependent_from_this[j] == index) {
				commands[dependencies[i]].dependent_from_this.erase(commands[dependencies[i]].dependent_from_this.begin() + j);
				break;
			}
		}
	}
	dependencies.resize(0);
}

CommandLine* find_by_symbol(const string& symb, const string& type = "point") {
	for (size_t i = 0; i < commands.size(); i++)
		if (commands[i].symbol == symb && commands[i].type == type) 
			return &(commands[i]);

	return nullptr;
}

void CommandLine::Compile() {

	bool symbol_is_there = 0;

	std::istringstream iss(command);
	string keyword;

	if (command == "") {
		symbol = "";
		DeleteObject();
		goto success;
	}

	
	parse_start:

	iss >> keyword;
	if (keyword == "point") {
		int x, y;
		iss >> x >> y;
		if (iss.fail()) {
			iss.clear();
			x = rand() % 100 + Width/2;
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
				pp1 = find_by_symbol(p1);
				if (pp1 == nullptr)
					goto error;

				obj = new Circle(*(Point*)(pp1->obj), r);

				AddDependancy(pp1);

			}
			// if there are center point and other point on circumference
			catch (const std::exception&)
			{
				CommandLine* pp1 = nullptr;
				CommandLine* pp2 = nullptr;

				pp1 = find_by_symbol(p1);
				pp2 = find_by_symbol(p2);

				if (pp1 == nullptr || pp2 == nullptr) {
					goto error;
				}
				obj = new Circle(*(Point*)(pp1->obj), distance(*(Point*)(pp1->obj), *(Point*)(pp2->obj)));
				AddDependancy(pp1);
				AddDependancy(pp2);
			}
		}
		
		obj->filled = filled;
		type = "circle";
	}
	else if (keyword == "triangle") {
		
		string p1, p2, p3;
		iss >> p1 >> p2 >> p3;

		CommandLine*pp1,*pp2,*pp3 ;
		pp1 = find_by_symbol(p1);
		pp2 = find_by_symbol(p2);
		pp3 = find_by_symbol(p3);

		if (pp1 == nullptr || pp2 == nullptr || pp3 == nullptr) goto error;
		
		if (type == "triangle"){
			ClearDependencies();
			((Triangle*)(obj))->set(*(Point*)(pp1->obj), *(Point*)(pp2->obj), *(Point*)(pp3->obj));
		}
		else {
			DeleteObject();
			obj = new Triangle(*(Point*)(pp1->obj), *(Point*)(pp2->obj), *(Point*)(pp3->obj));
			obj->filled = filled;
		}

		AddDependancy(pp1);
		AddDependancy(pp2);
		AddDependancy(pp3);

		type = "triangle";
	}
	else if (keyword == "line") {
		string p1, p2;
		iss >> p1 >> p2;

		CommandLine*pp1,*pp2;
		pp1 = find_by_symbol(p1);
		pp2 = find_by_symbol(p2);

		if (pp1 == nullptr || pp2 == nullptr) goto error;

		DeleteObject();
		obj = new Line(*(Point*)(pp1->obj), *(Point*)(pp2->obj));
		obj->filled = filled;

		AddDependancy(pp1);
		AddDependancy(pp2);

		type = "line";
	}
	else if (keyword == "incircle") {
		
		string tr;
		iss >> tr;
		CommandLine* trp;
		trp = find_by_symbol(tr, "triangle");
		if (trp == nullptr) goto error;

		if (type != "circle") {
			DeleteObject();
			obj = new Circle(((Triangle*)(trp->obj))->get_inscribed_circle());
			obj->filled = filled;
		}
		else {
			ClearDependencies();
			*((Circle*)(obj))=(((Triangle*)(trp->obj))->get_inscribed_circle());
		}

		AddDependancy(trp);

		type = "circle";
	}
	else if (keyword == "circumcircle") {

		string tr;
		iss >> tr;
		CommandLine* trp;
		trp = find_by_symbol(tr, "triangle");
		if (trp == nullptr) goto error;

		if (type != "circle") {
			DeleteObject();
			obj = new Circle(((Triangle*)(trp->obj))->get_circumcircle());
			obj->filled = filled;
		}
		else {
			ClearDependencies();
			*((Circle*)(obj)) = (((Triangle*)(trp->obj))->get_circumcircle());
		}

		AddDependancy(trp);

		type = "circle";
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
	r = 255; g = 64; b =64;
	return;
success:
	CompileDependencies();
	r = 128; g = 128; b = 128;
	return;

}

void CommandLine::CompileDependencies() {
	for (size_t i = 0; i < dependent_from_this.size(); i++) {
		commands[dependent_from_this[i]].Compile();
	}
};

void CommandLine::Draw() {
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	glVertex2f(x, Height - (y));
	glVertex2f(x + width, Height - y);
	glColor3ub(r - 64, g - 64, b - 64);
	glVertex2f(x + width, Height - (y + height));
	glVertex2f(x, Height - (y + height));
	glEnd();

	glColor3ub(255, 255, 255);
	glRasterPos2f(x+3, Height - y - 20);
	for (int i = 0; i < command.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, command[i]);
	}
}