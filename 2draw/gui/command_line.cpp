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
	if (obj != nullptr) {
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

void CommandLine::error() {
	//make the command line red to show that's an error occurred
	err = true;
	return;
}
void CommandLine::Compile() {

	editing = false;
	err = false;

	// empty command case
	if (command == "") {
		symbol = "";
		DeleteObject();
		//r = 128; g = 128; b = 128; // make command line gray
		return;
	}

	std::istringstream iss(command);
	string keyword;

	bool symbol_is_there = 0; // have we already read the symbol

	while (1) {

		/*
		The scheme of command compiling is
		explained in details in the "triangle" block

		this scheme more or less applies to every object with their specifics
		*/

		iss >> keyword;

		/*POINT*/
		if (keyword == "point" || (symbol != "" && keyword == "p")) {
			//expected syntax:
			//point_name point x_coordinate y_coordinate
			//or
			//point_name point
			//or
			//point_name p
			//
			//in last two cases x_coordinate and y_coordinate is
			//choosen randomly from -250 to 250

			int x, y;
			iss >> x >> y;

			// case when x and y were not specified or the typo occurred
			if (iss.fail()) {
				iss.clear();
				//randomize coordinates
				x = rand() % 500 - 250;
				y = rand() % 500 - 250;
				//then rewrite command for it to it's not shortened form 
				if (symbol != "")
					command = symbol + " ";
				else
					command = "";
				command = command + "point " + to_string(x) + " " + to_string(y);
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
			break;
		}


		/*CIRCLE STUFF*/
		else if (keyword == "circle") {

			//expected syntax:
			//
			//circle_name circle x_coordinate y_coordinate radius
			//or
			//circle_name circle point_name radius
			//or
			//circle_name circle point_name_in_center point_name_on_circumference

			DeleteObject();
			int x, y, r;
			string p1, p2;
			iss >> p1;

			// if there are two coordinates and radius
			try {
				x = stoi(p1);
				iss >> y >> r;
				if (iss.fail()) {
					iss.clear();
					err = true; 
					return;
				}
				obj = new Circle(x, y, r);
			}
			// if there are center point and radius
			catch (std::invalid_argument) {
				iss >> p2;
				try {
					r = stoi(p2);
					CommandLine* pp1 = nullptr;
					pp1 = find_by_symbol(p1);
					if (pp1 == nullptr) {
						err = true; 
						return;
					}
						

					obj = new Circle(*(Point*)(pp1->obj), r);

					AddDependency(pp1);

				}
				// if there are center point and other point on circumference
				catch (const std::exception&) {
					CommandLine* pp1 = nullptr;
					CommandLine* pp2 = nullptr;

					pp1 = find_by_symbol(p1);
					pp2 = find_by_symbol(p2);

					if (pp1 == nullptr || pp2 == nullptr) {
						err = true; 
						return;
					}
					obj = new Circle(*(Point*)(pp1->obj), distance(*(Point*)(pp1->obj), *(Point*)(pp2->obj)));
					AddDependency(pp1);
					AddDependency(pp2);
				}
			}

			type = "circle";
			break;
		}


		else if (keyword == "center") {

			//expected syntax:
			//point_name center circle_name

			string p;
			iss >> p;
			CommandLine* pp = nullptr;
			pp = find_by_symbol(p, "circle");
			if (pp == nullptr) {
				err = true; 
				return;
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
			command = symbol + " " + keyword + " " + p + " : " + to_string(int(((Point*)(obj))->x)) + " " + to_string(int(((Point*)(obj))->y));
			AddDependency(pp);
			break;
		}


		/*LINE STUFF*/
		else if (keyword == "line") {

			//expected syntax:
			//line_name line point_name1 point_name2

			string p1, p2;
			iss >> p1 >> p2;

			CommandLine* pp1, * pp2;
			pp1 = find_by_symbol(p1);
			pp2 = find_by_symbol(p2);

			if (pp1 == nullptr || pp2 == nullptr) { 
				err = true; 
				return; 
			}


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
			break;
		}


		else if (keyword == "intersection") {

			//expected syntax:
			//point_name intersection line_name1 line_name2

			string line1; string line2;
			iss >> line1; iss >> line2;

			CommandLine* cline1; CommandLine* cline2;


			cline1 = find_by_symbol(line1, "line");
			if (cline1 == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			cline2 = find_by_symbol(line2, "line");
			if (cline2 == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (((Line*)(cline1->obj))->is_parallel_to(*(Line*)(cline2->obj))) {
				err = true; 
				return;
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
			command = symbol + " " + keyword + " " + line1 + " " + line2 + " : " + to_string(int(((Point*)(obj))->x)) + " " + to_string(int(((Point*)(obj))->y));
			AddDependency(cline1);
			AddDependency(cline2);
			break;
		}


		else if (keyword == "perpendicular") {

			//expected syntax:
			//line_name1 perpendicular line_name2 point_name

			string line;
			string point;

			iss >> line;
			iss >> point;

			CommandLine* cline; CommandLine* cpoint;

			cline = find_by_symbol(line, "line");
			if (cline == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			cpoint = find_by_symbol(point, "point");
			if (cpoint == nullptr) {
				DeleteObject();
				err = true; 
				return;
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
			break;
		}


		else if (keyword == "parallel") {

			//expected syntax:
			//line_name1 parallel line_name2 point_name

			string line; string point;
			iss >> line; iss >> point;

			CommandLine* cline; CommandLine* cpoint;


			cline = find_by_symbol(line, "line");
			if (cline == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			cpoint = find_by_symbol(point, "point");
			if (cpoint == nullptr) {
				DeleteObject();
				err = true; 
				return;
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

			break;
		}


		/*TRIANGLE STUFF*/
		else if (keyword == "triangle") {

			//expected syntax:
			//triangle_name triangle point_name1 point_name2 point_name3

			// command requires three symbols to a points
			string p1, p2, p3;
			iss >> p1 >> p2 >> p3;

			// if symbols reading fails, we delete object completely
			if (iss.fail()) {
				iss.clear();
				DeleteObject();
				err = true; 
				return;
			}

			//then we get pointers to command lines that has type we need (here it is point)
			CommandLine* pp1, * pp2, * pp3;
			pp1 = find_by_symbol(p1);
			pp2 = find_by_symbol(p2);
			pp3 = find_by_symbol(p3);

			//case where we didn't find all we need
			if (pp1 == nullptr || pp2 == nullptr || pp3 == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			//if all is good, then if it's initialy was a triangle
			//we just update it without any deletions, because that would
			//mess up all every object that were dependent from this triangle
			if (type == "triangle") {
				ClearDependencies();
				((Triangle*)(obj))->set(*(Point*)(pp1->obj), *(Point*)(pp2->obj), *(Point*)(pp3->obj));
			}
			else {
				DeleteObject();
				obj = new Triangle(*(Point*)(pp1->obj), *(Point*)(pp2->obj), *(Point*)(pp3->obj));
				type = "triangle";
			}

			//it's nessesary to add all dependencies so when we move a point
			//our triangle will be updated
			AddDependency(pp1);
			AddDependency(pp2);
			AddDependency(pp3);
			break;
		}

		/*POINTS IN TRIANGLE*/
		else if (keyword == "incenter") {

			string tr;
			iss >> tr;

			CommandLine* trp;


			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				DeleteObject();
				err = true;
				return;
			}

			if (!((Triangle*)(trp->obj))->exists()) {
				err = true; 
				return;
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
			command = symbol + " " + keyword + " " + tr + " : " + to_string(int(((Point*)(obj))->x)) + " " + to_string(int(((Point*)(obj))->y));
			AddDependency(trp);
			break;
		}


		else if (keyword == "centroid") {

			string tr;
			iss >> tr;

			CommandLine* trp;


			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				DeleteObject();
				err = true;
				return;
			}

			if (!((Triangle*)(trp->obj))->exists()) {
				err = true; 
				return;
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
			command = symbol + " " + keyword + " " + tr + " : " + to_string(int(((Point*)(obj))->x)) + " " + to_string(int(((Point*)(obj))->y));
			AddDependency(trp);
			break;
		}


		else if (keyword == "orthocenter") {

			string tr;
			iss >> tr;

			CommandLine* trp;


			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (!((Triangle*)(trp->obj))->exists()) {
				err = true; 
				return;
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
			command = symbol + " " + keyword + " " + tr + " : " + to_string(int(((Point*)(obj))->x)) + " " + to_string(int(((Point*)(obj))->y));
			AddDependency(trp);
			break;
		}


		/*LINES IN TRIANGLE*/
		else if (keyword == "bisectrix") {

			//expected syntax:
			//line_name bisectrix triangle_name point_name_of_vertex

			string tr; string ver;
			iss >> tr; iss >> ver;

			CommandLine* trp; CommandLine* vertex;

			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (!((Triangle*)(trp->obj))->exists()) {
				err = true; 
				return;
			}

			// we look for a point only in triangles vertexes
			vertex = find_by_symbol_among(ver, trp->dependencies);
			if (vertex == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (type != "line") {
				DeleteObject();
				obj = new Line(((Triangle*)(trp->obj))->get_bisectrix(*(Point*)(vertex->obj)));
				type = "line";
			}
			else {
				ClearDependencies();
				*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_bisectrix(*(Point*)(vertex->obj));
			}

			AddDependency(trp);
			// we don't add a vertex as a dependency because
			// triangle is aleready dependent from it

			break;
		}


		else if (keyword == "altitude") {

			//expected syntax:
			//line_name altitude triangle_name point_name_of_vertex

			//for more comments look at "bisectrix" block

			string tr; string ver;
			iss >> tr; iss >> ver;

			CommandLine* trp; CommandLine* vertex;


			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (!((Triangle*)(trp->obj))->exists()) {
				err = true; 
				return;
			}

			vertex = find_by_symbol_among(ver, trp->dependencies);
			if (vertex == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (type != "line") {
				DeleteObject();
				obj = new Line(((Triangle*)(trp->obj))->get_altitude(*(Point*)(vertex->obj)));
				type = "line";
			}
			else {
				ClearDependencies();
				*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_altitude(*(Point*)(vertex->obj));
			}

			AddDependency(trp);
			break;
		}


		else if (keyword == "midline") {

			//expected syntax:
			//line_name midline triangle_name point_name_of_vertex

			//for more comments look at "bisectrix" block

			string tr; string ver;
			iss >> tr; iss >> ver;

			CommandLine* trp; CommandLine* vertex;


			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (!((Triangle*)(trp->obj))->exists()) {
				err = true; 
				return;
			}

			vertex = find_by_symbol_among(ver, trp->dependencies);
			if (vertex == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (type != "line") {
				DeleteObject();
				obj = new Line(((Triangle*)(trp->obj))->get_midline(*(Point*)(vertex->obj)));
				type = "line";
			}
			else {
				ClearDependencies();
				*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_midline(*(Point*)(vertex->obj));
			}

			AddDependency(trp);
			break;
		}


		else if (keyword == "perpbis") {

			//expected syntax:
			//line_name perpbis triangle_name point_name_of_vertex

			//for more comments look at "bisectrix" block

			string tr; string ver;
			iss >> tr; iss >> ver;

			CommandLine* trp; CommandLine* vertex;


			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (!((Triangle*)(trp->obj))->exists()) {
				err = true; 
				return;
			}

			vertex = find_by_symbol_among(ver, trp->dependencies);
			if (vertex == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (type != "line") {
				DeleteObject();
				obj = new Line(((Triangle*)(trp->obj))->get_perp_bis(*(Point*)(vertex->obj)));
				type = "line";
			}
			else {
				ClearDependencies();
				*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_perp_bis(*(Point*)(vertex->obj));
			}

			AddDependency(trp);
			break;
		}


		/*CIRCLES OF TRIANGLE*/
		else if (keyword == "incircle") {

			//expected syntax:
			//circle_name incircle triangle_name

			string tr;
			iss >> tr;
			CommandLine* trp;
			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) { 
				err = true; 
				return; 
			}

			if (type != "circle") {
				DeleteObject();
				obj = new Circle(((Triangle*)(trp->obj))->get_inscribed_circle());
				type = "circle";
			}
			else {
				ClearDependencies();
				*((Circle*)(obj)) = (((Triangle*)(trp->obj))->get_inscribed_circle());
			}

			AddDependency(trp);
			break;
		}


		else if (keyword == "circumcircle") {

			//expected syntax:
			//circle_name circumcircle triangle_name

			string tr;
			iss >> tr;
			CommandLine* trp;
			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				err = true; 
				return;
			}

			if (type != "circle") {
				DeleteObject();
				obj = new Circle(((Triangle*)(trp->obj))->get_circumcircle());
				type = "circle";
			}
			else {
				ClearDependencies();
				*((Circle*)(obj)) = (((Triangle*)(trp->obj))->get_circumcircle());
			}

			AddDependency(trp);
			break;
		}


		else if (keyword == "excircle") {

			//expected syntax:
			//circle_name excircle triangle_name point_name_of_vertex

			string tr; string ver;
			iss >> tr; iss >> ver;

			CommandLine* trp; CommandLine* vertex;


			trp = find_by_symbol(tr, "triangle");
			if (trp == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (!((Triangle*)(trp->obj))->exists()) {
				err = true; 
				return;
			}

			// we look for a point only among triangle vertexes
			vertex = find_by_symbol_among(ver, trp->dependencies);
			if (vertex == nullptr) {
				DeleteObject();
				err = true; 
				return;
			}

			if (type != "circle") {
				DeleteObject();
				obj = new Circle(((Triangle*)(trp->obj))->get_excircle(*(Point*)(vertex->obj)));
				obj->filled = filled;
				type = "circle";
			}
			else {
				ClearDependencies();
				*((Circle*)(obj)) = ((Triangle*)(trp->obj))->get_excircle(*(Point*)(vertex->obj));
			}

			AddDependency(trp);
			// we don't add a vertex as a dependency because
			// triangle is aleready dependent from it

			break;
		}


		/*POLYGON STUFF*/
		else if (keyword == "polygon") {

			//expected syntax:
			//polygon_name polygon point_name1 ... point_nameN
			//(number of points is arbutrary)

			string p1;

			// currently nothing could be dependent from polygon
			// so we always delete it instead of erasing all it's vertexes

			DeleteObject();
			obj = new Polygon();

			while (!iss.eof()) {

				iss >> p1;

				CommandLine* pp1;
				pp1 = find_by_symbol(p1);

				if (pp1 == nullptr) {
					DeleteObject();
					err = true; 
					return;
				}

				((Polygon*)(obj))->append(*(Point*)(pp1->obj));
				AddDependency(pp1);
			}

			type = "polygon";
			break;
		}


		else if (keyword == "convex_hull" || keyword == "convex") {


			//expected syntax:
			//polygon_name convex_hull point_name1 ... point_nameN
			// or
			//polygon_name convex point_name1 ... point_nameN
			//
			//(number of points is arbutrary)

			string p1;

			// currently nothing could be dependent from polygon
			// so we always delete it instead of erasing all it's vertexes
			DeleteObject();
			obj = new Polygon();

			vector<Point> v;
			while (!iss.eof()) {
				iss >> p1;
				CommandLine* pp1;
				pp1 = find_by_symbol(p1);
				if (pp1 == nullptr) {
					err = true; 
					return;
				}
				v.push_back(*(Point*)(pp1->obj));
				AddDependency(pp1);
			}
			*(Polygon*)(obj) = convex_hull(v);

			type = "polygon";
			break;
		}

		/*ELSE*/
			//that's the case when we didn't recognize any command
			//and if we didn't already defined a symbol
			//we say that what we have read is our symbol
		else if (!symbol_is_there) {
			symbol_is_there = true;
			if (symbol != keyword && is_the_symbol_defined(keyword)) {
				err = true; 
				return;
			}
			symbol = keyword; 
			// after that, loop repeats, reads new keyword, but symbol_is_there is true
		}

		//first word is read as symbol, but next word is still not recognized or something else gone wrong
		else {
			DeleteObject();
			err = true; 
			return;
		}
	}
		
	
	obj->filled = filled;

	//randomize object colors
	obj->red = 128 + rand() % 128;
	obj->green = 128 + rand() % 128;
	obj->blue = 128 + rand() % 128;

	CompileDependencies();

	// make command line gray
	//r = 128; g = 128; b = 128; 
	return;
}

void CommandLine::CompileDependencies() {
	for (size_t i = 0; i < dependent_from_this.size(); i++) {
		commands[dependent_from_this[i]].Compile();
	}
};

void CommandLine::Draw() {
	glShadeModel(GL_SMOOTH);

	glColor3ub(255, 255, 255);
	if (obj != nullptr) {
		string measure = to_string((int)(obj->measure));
		glRasterPos2f(x - 80, Height - y - 20);
		for (int i = 0; i < measure.length(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, measure[i]);
		}
	}

	
	glBegin(GL_POLYGON);

	int r, g, b;
	if (editing) {
		r = 64;
		g = 64;
		b = 192;
	} else if (err) {
		r = 192;
		g = 0;
		b = 0;
	} else if (obj != nullptr) {
		r = obj->red;
		g = obj->green;
		b = obj->blue;
	} else {
		r = g = b = 128;
	}

	glColor3ub(r, g, b);
	glVertex2f(x, Height - (y));
	glVertex2f(x + width, Height - y);
	if (err) {
		glColor3ub(r - 64, g, b);
	} else {
		glColor3ub(r - 64, g - 64, b - 64);
	}
	
	glVertex2f(x + width, Height - (y + height));
	glVertex2f(x, Height - (y + height));
	glEnd();

	if (editing || err) {
		r = g = b = 255;
	}
	else {
		r = g = b = 0;
	}

	glColor3ub(r, g, b);
	glRasterPos2f(x+3, Height - y - 20);
	for (int i = 0; i < command.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, command[i]);
	}
}