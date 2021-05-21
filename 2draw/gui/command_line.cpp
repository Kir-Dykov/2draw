#include "command_line.h"
/*
Actual avaliable commands that you can just type in right now

a point 400 400
b point
c point
tr triangle a b c
c1 circle 300 400 50
c2 circle a 60
c3 circle a b
c4 incircle t
c5 circumcircle t
l1 line a b
l2 bisectrix t a
pg1 polygon a b c ... n
pg2 convex a b c ... n
p intersection l1 l2
l perpendicular l1 p
p incenter triangle1
p centroid triangle1
p orthocenter triangle1
c6 excircle triangle1 p
l altitude triangle1 p
l midline triangle1 p
l perpbis triangle1 p
p center circle1
l parallel l1 p1
l perpendicular l1 p1
*/

//NEVER erase from that vector.
//it will break indexes inside CommandLine's
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

void CommandLine::AddDependency(CommandLine& other) {
	other.dependent_from_this.push_back(index);
	dependencies.push_back(other.index);
}

void CommandLine::AddDependency(CommandLine* other) {
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

bool is_the_symbol_defined(const string& symb) {
	for (size_t i = 0; i < commands.size(); i++)
		if (commands[i].symbol == symb)
			return true;

	return false;
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
	if (iss.fail()) {
		goto error;
	}

	if (keyword == "point" || (symbol!="" && keyword == "p")) {
		int x, y;
		iss >> x >> y;
		if (iss.fail()) {
			iss.clear();
			x = rand() % 500 - 250;
			y = rand() % 500 - 250;
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
			ClearDependencies();
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

				AddDependency(pp1);

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
				AddDependency(pp1);
				AddDependency(pp2);
			}
		}
		
		type = "circle";
	}



	else if (keyword == "center") {
		string p;
		iss >> p;
		CommandLine* pp = nullptr;
		pp = find_by_symbol(p, "circle");
		if (pp == nullptr) {
			goto error;
		}

		if (type != "point") {
			DeleteObject();
			obj = new Point(((Circle*)(pp->obj))->center.x, ((Circle*)(pp->obj))->center.y);
			type = "point";
		}
		else {
			ClearDependencies();
			((Point*)obj)->set(((Circle*)(pp->obj))->center.x, ((Circle*)(pp->obj))->center.y);
		}

		AddDependency(pp);
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

		AddDependency(pp1);
		AddDependency(pp2);
		AddDependency(pp3);

		type = "triangle";
	}



	else if (keyword == "line") {
		string p1, p2;
		iss >> p1 >> p2;

		CommandLine*pp1,*pp2;
		pp1 = find_by_symbol(p1);
		pp2 = find_by_symbol(p2);

		if (pp1 == nullptr || pp2 == nullptr) goto error;


		if (type == "line") {
			ClearDependencies();
			((Line*)(obj))->set(*(Point*)(pp1->obj), *(Point*)(pp2->obj));
		}
		else {
			DeleteObject();
			obj = new Line(*(Point*)(pp1->obj), *(Point*)(pp2->obj));
			type = "line";
		}

		AddDependency(pp1);
		AddDependency(pp2);
		
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

		AddDependency(trp);

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

		AddDependency(trp);

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
			AddDependency(pp1);
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
			AddDependency(pp1);
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

		if (!((Triangle*)(trp->obj))->exists()) {
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

		AddDependency(trp);

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

		if (((Line*)(cline1->obj))->is_parallel_to(*(Line*)(cline2->obj))) {
			//DeleteObject()
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

		AddDependency(cline1);
		AddDependency(cline2);

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

		AddDependency(cline);
		AddDependency(cpoint);

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

		AddDependency(cline);
		AddDependency(cpoint);

		type = "line";
	}



	else if (keyword == "incenter") {

		string tr;
		iss >> tr;

		CommandLine* trp;


		trp = find_by_symbol(tr, "triangle");
		if (trp == nullptr) {
			DeleteObject();
			goto error;
		}

		if (!((Triangle*)(trp->obj))->exists()) {
			goto error;
		}

		if (type != "point") {
			DeleteObject();
			obj = new Point(((Triangle*)(trp->obj))->get_intersec_bis());
			type = "point";
		}
		else {
			ClearDependencies();
			*((Point*)(obj)) = ((Triangle*)(trp->obj))->get_intersec_bis();
		}

		AddDependency(trp);

		type = "point";
	}



	else if (keyword == "centroid") {

		string tr;
		iss >> tr;

		CommandLine* trp;


		trp = find_by_symbol(tr, "triangle");
		if (trp == nullptr) {
			DeleteObject();
			goto error;
		}

		if (!((Triangle*)(trp->obj))->exists()) {
			goto error;
		}

		if (type != "point") {
			DeleteObject();
			obj = new Point(((Triangle*)(trp->obj))->get_intersec_med());
			type = "point";
		}
		else {
			ClearDependencies();
			*((Point*)(obj)) = ((Triangle*)(trp->obj))->get_intersec_med();
		}

		AddDependency(trp);

		type = "point";
	}



	else if (keyword == "orthocenter") {

		string tr;
		iss >> tr;

		CommandLine* trp;


		trp = find_by_symbol(tr, "triangle");
		if (trp == nullptr) {
			DeleteObject();
			goto error;
		}

		if (!((Triangle*)(trp->obj))->exists()) {
			goto error;
		}

		if (type != "point") {
			DeleteObject();
			obj = new Point(((Triangle*)(trp->obj))->get_intersec_alt());
			type = "point";
		}
		else {
			ClearDependencies();
			*((Point*)(obj)) = ((Triangle*)(trp->obj))->get_intersec_alt();
		}

		AddDependency(trp);

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

		if (!((Triangle*)(trp->obj))->exists()) {
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

		AddDependency(trp);

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

		if (!((Triangle*)(trp->obj))->exists()) {
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

		AddDependency(trp);

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

		if (!((Triangle*)(trp->obj))->exists()) {
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

		AddDependency(trp);

		type = "line";
	}



	else if (keyword == "perpbis") {

		string tr; string ver;
		iss >> tr; iss >> ver;

		CommandLine* trp; CommandLine* vertex;


		trp = find_by_symbol(tr, "triangle");
		if (trp == nullptr) {
			DeleteObject();
			goto error;
		}

		if (!((Triangle*)(trp->obj))->exists()) {
			goto error;
		}

		vertex = find_by_symbol_among(ver, trp->dependencies);
		if (vertex == nullptr) {
			DeleteObject();
			goto error;
		}

		if (type != "line") {
			DeleteObject();
			obj = new Line(((Triangle*)(trp->obj))->get_perp_bis(*(Point*)(vertex->obj)));

		}
		else {
			ClearDependencies();
			*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_perp_bis(*(Point*)(vertex->obj));
		}

		AddDependency(trp);

		type = "line";
	}



	else if (!symbol_is_there) {
		symbol_is_there = true;
		if (symbol != keyword && is_the_symbol_defined(keyword)) {
			goto error;
		}
		symbol = keyword;
		goto parse_start;
	} 
	


	else 
		goto error;



	success:
		if (obj != nullptr) {
			obj->filled = filled;
			obj->red = 64 + rand() % 192;
			obj->green = 64 + rand() % 192;
			obj->blue = 64 + rand() % 192;
		}
		CompileDependencies();
		r = 128; g = 128; b = 128;
		return;



	error:
		r = 255; g = 64; b =64;
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