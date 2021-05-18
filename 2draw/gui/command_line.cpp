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
l2 bisectix t a
pg1 polygon a b c ... n
pg2 convex a b c ... n
p intersection l1 l2
l perpendicular l1 p
tr incenter triangle1
tr centroid triangle1
tr orthocenter triangle1
cr excircle tr p
l altitude tr p
l midline tr p

*/

//NEVER erase from that vector.
//it will break indexes in CommandLine's
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

CommandLine* find_by_symbol_among(const string& symb, const vector<size_t>& v, const string& type = "point") {
	for (size_t i = 0; i < v.size(); i++)
		if (commands[v[i]].symbol == symb && commands[v[i]].type == type)
			return &(commands[v[i]]);

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
	if (keyword == "point" || (symbol!="" && keyword == "p")) {
		int x, y;
		iss >> x >> y;
		if (iss.fail()) {
			iss.clear();
			x = rand() % 100 - 50;
			y = rand() % 100 - 50;
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
		}
		else {
			ClearDependencies();
			*((Circle*)(obj)) = (((Triangle*)(trp->obj))->get_circumcircle());
		}

		AddDependancy(trp);

		type = "circle";
	}
	else if (keyword == "polygon") {
		string p1;
		DeleteObject();
		obj = new Polygon();
		while (!iss.eof()) {
			iss >> p1;
			CommandLine* pp1;
			pp1 = find_by_symbol(p1);
			if (pp1 == nullptr) {
				DeleteObject();
				goto error;
			}
			((Polygon*)(obj))->append(*(Point*)(pp1->obj));
			AddDependancy(pp1);
		}
		/*
		if (((Polygon*)(obj))->is_selfintersecting();) {
			DeleteObject();
			goto error;
		}*/
		//cout << ((Polygon*)(obj))->area() << endl;
		type = "polygon";
	}
	else if (keyword == "convex_hull" || keyword == "convex") {
		string p1;
		DeleteObject();
		obj = new Polygon();
		vector<Point> v;
		while (!iss.eof()) {
			iss >> p1;
			CommandLine* pp1;
			pp1 = find_by_symbol(p1);
			if (pp1 == nullptr) {
				goto error;
			}
			v.push_back(*(Point*)(pp1->obj));
			AddDependancy(pp1);
		}
		*(Polygon*)(obj) = convex_hull(v);

		type = "polygon";
	}
	else if (keyword == "bisectrix") {

		string tr; string ver;
		iss >> tr; iss >> ver;

		CommandLine* trp; CommandLine* vertex;
		

		trp = find_by_symbol(tr, "triangle");
		if (trp == nullptr) {
			DeleteObject();
			goto error;
		}

		vertex = find_by_symbol_among(ver, trp->dependencies);
		if (vertex == nullptr) {
			DeleteObject();
			goto error;
		}

		if (type != "line") {
			DeleteObject();
			obj = new Line(((Triangle*)(trp->obj))->get_bisectrix(*(Point*)(vertex->obj)));
			obj->filled = filled;
		}
		else {
			ClearDependencies();
			*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_bisectrix(*(Point*)(vertex->obj));
		}

		AddDependancy(trp);

		type = "line";
	}
	else if (keyword == "intersection") {

		string line1; string line2;
		iss >> line1; iss >> line2;

		CommandLine* cline1; CommandLine* cline2;
		

		cline1 = find_by_symbol(line1, "line");
		if (cline1 == nullptr) {
			DeleteObject();
			goto error;
		}

		cline2 = find_by_symbol(line2, "line");
		if (cline2 == nullptr) {
			DeleteObject();
			goto error;
		}

		if (type != "point") {
			DeleteObject();
			obj = new Point(((Line*)(cline1->obj))->intersection(*(Line*)(cline2->obj)));
			type = "point";
		}
		else {
			ClearDependencies();
			*((Point*)(obj)) = ((Line*)(cline1->obj))->intersection(*(Line*)(cline2->obj));
		}

		AddDependancy(cline1);
		AddDependancy(cline2);

		type = "point";
	}
	else if (keyword == "perpendicular") {

	string line; string point;
	iss >> line; iss >> point;

	CommandLine* cline; CommandLine* cpoint;


	cline = find_by_symbol(line, "line");
	if (cline == nullptr) {
		DeleteObject();
		goto error;
	}

	cpoint = find_by_symbol(point, "point");
	if (cpoint == nullptr) {
		DeleteObject();
		goto error;
	}

	if (type != "line") {
		DeleteObject();
		obj = new Line(((Line*)(cline->obj))->perp2point_on_line(*(Point*)(cpoint->obj)));
		type = "line";
	}
	else {
		ClearDependencies();
		*((Line*)(obj)) = ((Line*)(cline->obj))->perp2point_on_line(*(Point*)(cpoint->obj));
	}

	AddDependancy(cline);
	AddDependancy(cpoint);

	type = "line";
	}
	else if (keyword == "parallel") {

	string line; string point;
	iss >> line; iss >> point;

	CommandLine* cline; CommandLine* cpoint;


	cline = find_by_symbol(line, "line");
	if (cline == nullptr) {
		DeleteObject();
		goto error;
	}

	cpoint = find_by_symbol(point, "point");
	if (cpoint == nullptr) {
		DeleteObject();
		goto error;
	}

	if (type != "line") {
		DeleteObject();
		obj = new Line(((Line*)(cline->obj))->parallel(*(Point*)(cpoint->obj)));
		type = "line";
	}
	else {
		ClearDependencies();
		*((Line*)(obj)) = ((Line*)(cline->obj))->parallel(*(Point*)(cpoint->obj));
	}

	AddDependancy(cline);
	AddDependancy(cpoint);

	type = "line";
	}
	else if (keyword == "incenter") {

	string triangle;
	iss >> triangle;

	CommandLine* ctriangle;


	ctriangle = find_by_symbol(triangle, "triangle");
	if (ctriangle == nullptr) {
		DeleteObject();
		goto error;
	}

	if (type != "point") {
		DeleteObject();
		obj = new Point(((Triangle*)(ctriangle->obj))->get_intersec_bis());
		type = "point";
	}
	else {
		ClearDependencies();
		*((Point*)(obj)) = ((Triangle*)(ctriangle->obj))->get_intersec_bis();
	}

	AddDependancy(ctriangle);

	type = "point";
	}
	else if (keyword == "centroid") {

	string triangle;
	iss >> triangle;

	CommandLine* ctriangle;


	ctriangle = find_by_symbol(triangle, "triangle");
	if (ctriangle == nullptr) {
		DeleteObject();
		goto error;
	}

	if (type != "point") {
		DeleteObject();
		obj = new Point(((Triangle*)(ctriangle->obj))->get_intersec_med());
		type = "point";
	}
	else {
		ClearDependencies();
		*((Point*)(obj)) = ((Triangle*)(ctriangle->obj))->get_intersec_med();
	}

	AddDependancy(ctriangle);

	type = "point";
	}
	else if (keyword == "orthocenter") {

	string triangle;
	iss >> triangle;

	CommandLine* ctriangle;


	ctriangle = find_by_symbol(triangle, "triangle");
	if (ctriangle == nullptr) {
		DeleteObject();
		goto error;
	}

	if (type != "point") {
		DeleteObject();
		obj = new Point(((Triangle*)(ctriangle->obj))->get_intersec_alt());
		type = "point";
	}
	else {
		ClearDependencies();
		*((Point*)(obj)) = ((Triangle*)(ctriangle->obj))->get_intersec_alt();
	}

	AddDependancy(ctriangle);

	type = "point";
	}
	else if (keyword == "excircle") {

	string tr; string ver;
	iss >> tr; iss >> ver;

	CommandLine* trp; CommandLine* vertex;


	trp = find_by_symbol(tr, "triangle");
	if (trp == nullptr) {
		DeleteObject();
		goto error;
	}

	vertex = find_by_symbol_among(ver, trp->dependencies);
	if (vertex == nullptr) {
		DeleteObject();
		goto error;
	}

	if (type != "circle") {
		DeleteObject();
		obj = new Circle(((Triangle*)(trp->obj))->get_excircle(*(Point*)(vertex->obj)));
		obj->filled = filled;
	}
	else {
		ClearDependencies();
		*((Circle*)(obj)) = ((Triangle*)(trp->obj))->get_excircle(*(Point*)(vertex->obj));
	}

	AddDependancy(trp);

	type = "circle";
	}
	else if (keyword == "altitude") {

	string tr; string ver;
	iss >> tr; iss >> ver;

	CommandLine* trp; CommandLine* vertex;


	trp = find_by_symbol(tr, "triangle");
	if (trp == nullptr) {
		DeleteObject();
		goto error;
	}

	vertex = find_by_symbol_among(ver, trp->dependencies);
	if (vertex == nullptr) {
		DeleteObject();
		goto error;
	}

	if (type != "line") {
		DeleteObject();
		obj = new Line(((Triangle*)(trp->obj))->get_altitude(*(Point*)(vertex->obj)));
		
	}
	else {
		ClearDependencies();
		*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_altitude(*(Point*)(vertex->obj));
	}

	AddDependancy(trp);

	type = "line";
	}
	else if (keyword == "midline") {

	string tr; string ver;
	iss >> tr; iss >> ver;

	CommandLine* trp; CommandLine* vertex;


	trp = find_by_symbol(tr, "triangle");
	if (trp == nullptr) {
		DeleteObject();
		goto error;
	}

	vertex = find_by_symbol_among(ver, trp->dependencies);
	if (vertex == nullptr) {
		DeleteObject();
		goto error;
	}

	if (type != "line") {
		DeleteObject();
		obj = new Line(((Triangle*)(trp->obj))->get_midline(*(Point*)(vertex->obj)));

	}
	else {
		ClearDependencies();
		*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_midline(*(Point*)(vertex->obj));
	}

	AddDependancy(trp);

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
	r = 255; g = 64; b =64;
	return;
success:
	if (obj != nullptr) {
		obj->filled = filled;
		obj->red = rand() % 192 + 64;
		obj->green = rand() % 192 + 64;
		obj->blue = rand() % 192 + 64;
	}
	

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