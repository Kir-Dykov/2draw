#include "command_line.h"

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

	cout << "wtf" << endl;
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
		if (keyword == "point" || (symbol_is_there == 1 && keyword == "p")) {
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

		// ���� ����� ������ � ���� �
		// name argument line
		else if (keyword == "argument") {
			if (obj != nullptr) {
				DeleteObject();
			}
			else {
				ClearDependencies();
			}

			string obj_t;
			iss >> obj_t;

			CommandLine* ctr;

			ctr = find_by_symbol(obj_t, "line");
			if (ctr == nullptr) {
				DeleteObject();
				err = true;
				return;
			}

			command = symbol + " " + keyword + " " + obj_t + " : deg " + to_string((int)((Line*)(ctr->obj))->get_angle_deg()) + \
				" rad " + to_string(((Line*)(ctr->obj))->get_angle_rad());
			AddDependency(ctr);
			break;
		}


		/*TRIANGLE STUFF*/
		else if (keyword == "triangle" || (symbol_is_there == 1 && keyword == "t")) {

			if(MakeTriangle(iss))
				break;
			else
				return;
		}

		// ���������� ��� ������������
		// name type triangle
		else if (keyword == "type") {
			if (obj != nullptr) {
				DeleteObject();
			}
			else {
				ClearDependencies();
			}

			string obj_t1;
			iss >> obj_t1;

			CommandLine* ctr1;

			ctr1 = find_by_symbol(obj_t1, "triangle");
			if (ctr1 == nullptr) {
				DeleteObject();
				err = true;
				return;
			}

			command = symbol + " " + keyword + " " + obj_t1 + " : " + to_string(((Triangle*)(ctr1->obj))->triangle_type());
			AddDependency(ctr1);
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


		else if (keyword == "median") {

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
				obj = new Line(((Triangle*)(trp->obj))->get_median(*(Point*)(vertex->obj)));
				type = "line";
			}
			else {
				ClearDependencies();
				*((Line*)(obj)) = ((Triangle*)(trp->obj))->get_median(*(Point*)(vertex->obj));
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

			if (!((Triangle*)(trp->obj))->exists()) {
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

			if (type == "polygon") {
				ClearDependencies();
				((Polygon*)(obj))->clear();
			}
			else {
				DeleteObject();
				obj = new Polygon();
			}
			

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

			if (type == "polygon") {
				ClearDependencies();
				((Polygon*)(obj))->clear();
			}
			else {
				DeleteObject();
				obj = new Polygon();
			}

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

			if (v.size() <= 2) {
				err = true;
				return;
			}

			*(Polygon*)(obj) = convex_hull(v);

			type = "polygon";
			break;
		}

		// ����� � ��������� ����� ������ ����� ��������
		// name center_of_mass polygon
		else if (keyword == "center_of_mass") {

			string tr;
			iss >> tr;
			CommandLine* trp;
			trp = find_by_symbol(tr, "polygon");
			if (trp == nullptr) {
				err = true;
				return;
			}

			if (type != "point") {
				DeleteObject();
				obj = new Point(((Polygon*)(trp->obj))->center_of_mass());
				type = "point";
			}
			else {
				ClearDependencies();
				*((Point*)(obj)) = (((Polygon*)(trp->obj))->center_of_mass());
			}
			command = symbol + " " + keyword + " " + tr + " : " + to_string(int(((Point*)(obj))->x)) + " " + to_string(int(((Point*)(obj))->y));
			AddDependency(trp);
			break;
		}

		// �������� �������������� �� ����������, return 1 or 0
		// name is_convex polygon
		else if (keyword == "is_convex") {
			if (obj != nullptr) {
				DeleteObject();
			}
			else {
				ClearDependencies();
			}

			string obj_t1;
			iss >> obj_t1;

			CommandLine* ctr1;

			ctr1 = find_by_symbol(obj_t1, "polygon");
			if (ctr1 == nullptr) {
				DeleteObject();
				err = true;
				return;
			}

			command = symbol + " " + keyword + " " + obj_t1 + " : " + to_string(((Polygon*)(ctr1->obj))->is_convex());
			AddDependency(ctr1);
			break;
		}


		/*NUMBERS AND PROPERTIES*/
		// ����� ������ �������
		// name output obj
		else if (keyword == "info") {

			if (obj != nullptr) {
				DeleteObject();
			}
			else {
				ClearDependencies();
			}

			string obj_t1;
			iss >> obj_t1;

			CommandLine* ctr1;

			ctr1 = find_by_symbol(obj_t1, "circle");
			if (ctr1 != nullptr)
				command = symbol + " " + keyword + " " + obj_t1 + " :center " + to_string((int)((Circle*)(ctr1->obj))->center.x) \
				+ " " + to_string((int)((Circle*)(ctr1->obj))->center.y) + " r " + to_string((int)((Circle*)(ctr1->obj))->radius);
			if (ctr1 == nullptr) {
				ctr1 = find_by_symbol(obj_t1, "line");
				if (ctr1 != nullptr)
					command = symbol + " " + keyword + " " + obj_t1 + " :a " + to_string((int)((Line*)(ctr1->obj))->get_a()) + \
					" ,b " + to_string((int)((Line*)(ctr1->obj))->get_b()) + " ,c " + to_string((int)((Line*)(ctr1->obj))->get_c());
				if (ctr1 == nullptr) {
					DeleteObject();
					err = true;
					return;
				}

			}

			AddDependency(ctr1);
			break;
		}



		else if (keyword == "perimeter") {
			
			if (obj != nullptr) {
				DeleteObject();
			}
			else {
				ClearDependencies();
			}

			string obj_t;
			iss >> obj_t;

			CommandLine* ctr;

			ctr = find_by_symbol(obj_t, "triangle");
			if (ctr != nullptr)
				command = symbol + " " + keyword + " " + obj_t + " : " + to_string((int)((Triangle*)(ctr->obj))->perimeter());
			else {
				ctr = find_by_symbol(obj_t, "circle");
				if (ctr != nullptr)
					command = symbol + " " + keyword + " " + obj_t + " : " + to_string((int)((Circle*)(ctr->obj))->circumference());
				else {
					ctr = find_by_symbol(obj_t, "polygon");
					if (ctr != nullptr)
						command = symbol + " " + keyword + " " + obj_t + " : " + to_string((int)((Polygon*)(ctr->obj))->perimeter());
					else {
						DeleteObject();
						err = true;
						return;
					}
				}
			}
			AddDependency(ctr);
			break;
		}



		else if (keyword == "area") {

			if (obj != nullptr) {
				DeleteObject();
			}
			else {
				ClearDependencies();
			}

			string obj_symbol;
			iss >> obj_symbol;

			CommandLine* ctr;

			ctr = find_by_symbol(obj_symbol, "triangle");
			if (ctr != nullptr) {
				command = symbol + " " + keyword + " " + obj_symbol + " : " + to_string((int)(ctr->obj)->measure);
			} else {
				ctr = find_by_symbol(obj_symbol, "circle");
				if (ctr != nullptr) {
					command = symbol + " " + keyword + " " + obj_symbol + " : " + to_string((int)(ctr->obj)->measure);
				} else {
					ctr = find_by_symbol(obj_symbol, "polygon");
					if (ctr != nullptr) {
						command = symbol + " " + keyword + " " + obj_symbol + " : " + to_string((int)(ctr->obj)->measure);
					} else {
						DeleteObject();
						err = true;
						return;
					}
				}
			}
			AddDependency(ctr);
			break;
		}

		// �������� ����������� �� ����� �������, return 0 or 1
		// name is_in point obj
		else if (keyword == "is_in") {

			if (obj != nullptr) {
				DeleteObject();
			}
			else {
				ClearDependencies();
			}

			string obj_t1; string obj_t2;
			iss >> obj_t1; iss >> obj_t2;

			CommandLine* ctr1; CommandLine* ctr2;

			ctr1 = find_by_symbol(obj_t1);
			if (ctr1 != nullptr) {
				Point tmp = Point(((Point*)(ctr1->obj))->x, ((Point*)(ctr1->obj))->y);
				ctr2 = find_by_symbol(obj_t2, "triangle");
				if (ctr2 != nullptr)
					command = symbol + " " + keyword + " " + obj_t1 + " " + obj_t2 + " : " + to_string((int)((Triangle*)(ctr2->obj))->is_in(tmp));
				if (ctr2 == nullptr) {
					ctr2 = find_by_symbol(obj_t2, "circle");
					if (ctr2 != nullptr)
						command = symbol + " " + keyword + " " + obj_t1 + " " + obj_t2 + " : " + to_string((int)((Circle*)(ctr2->obj))->is_in(tmp));
					if (ctr2 == nullptr) {
						ctr2 = find_by_symbol(obj_t2, "polygon");
						if (ctr2 != nullptr)
							command = symbol + " " + keyword + " " + obj_t1 + " " + obj_t2 + " : " + to_string((int)((Polygon*)(ctr2->obj))->is_in(tmp));
						if (ctr2 == nullptr) {
							ctr2 = find_by_symbol(obj_t2, "line");
							if (ctr2 != nullptr)
								command = symbol + " " + keyword + " " + obj_t1 + " " + obj_t2 + " : " + to_string((int)((Line*)(ctr2->obj))->point_on_Line(tmp));
							if (ctr2 == nullptr) {
								DeleteObject();
								err = true;
								return;
							}
						}
					}
				}
			}
			else {
				DeleteObject();
				err = true;
				return;
			}
			AddDependency(ctr1);
			AddDependency(ctr2);
			break;
		}

		// ���� ������������
		// name angle triangle point 
		// ���� ����� ����� �������
		// name angle line1 line2
		else if (keyword == "angle") {
			if (obj != nullptr) {
				DeleteObject();
			}
			else {
				ClearDependencies();
			}

			string obj_t1; string obj_t2;
			iss >> obj_t1; iss >> obj_t2;

			CommandLine* ctr1; CommandLine* ctr2;

			ctr1 = find_by_symbol(obj_t1, "line");
			ctr2 = find_by_symbol(obj_t2, "line");
			if (ctr1 == nullptr || ctr2 == nullptr) {
				ctr1 = find_by_symbol(obj_t1, "triangle");
				if (ctr1 == nullptr) {
					DeleteObject();
					err = true;
					return;
				}

				ctr2 = find_by_symbol_among(obj_t2, ctr1->dependencies);
				if (ctr2 == nullptr) {
					DeleteObject();
					err = true;
					return;
				}
				command = symbol + " " + keyword + " " + obj_t1 + " " + obj_t2 + " : rad " + to_string(((Triangle*)(ctr1->obj))->get_angle(*(Point*)(ctr2->obj)));
				AddDependency(ctr1);
				AddDependency(ctr2);
				break;
			}
			else {
				Line tmp = Line(((Line*)(ctr2->obj))->get_a(), ((Line*)(ctr2->obj))->get_b(), ((Line*)(ctr2->obj))->get_c());
				command = symbol + " " + keyword + " " + obj_t1 + " " + obj_t2 + " : deg " + to_string((int)((Line*)(ctr1->obj))->get_twoLines_degangle(tmp)) + \
					" rad " + to_string(((Line*)(ctr1->obj))->get_twoLines_radangle(tmp));
				AddDependency(ctr1);
				AddDependency(ctr2);
				break;
			}
			
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

	if (obj != nullptr) {
		obj->filled = filled;
		//randomize object colors
		obj->red = obj->red + rand() % 17 - 8;
		obj->red = max(128, min(255, obj->red));
		obj->green = obj->green + rand() % 17 - 8;
		obj->green = max(128, min(255, obj->green));
		obj->blue = obj->blue + rand() % 17 - 8;
		obj->blue = max(128, min(255, obj->blue));
	}
	CompileDependencies();

	return;
}

void CommandLine::CompileDependencies() {
	for (size_t i = 0; i < dependent_from_this.size(); i++) {
		commands[dependent_from_this[i]].Compile();
	}
};

void CommandLine::Draw() {
	glShadeModel(GL_SMOOTH);

	int r, g, b;
	if (editing) { r = 64; g = 64; b = 192; }
	else if (err) { r = 192; g = b = 0; }
	else if (obj != nullptr) { r = obj->red; g = obj->green; b = obj->blue; }
	else { r = g = b = 128; }

	

	glBegin(GL_POLYGON);

		glColor3ub(r, g, b);

		glVertex2f(x + width, Height - y);
		glVertex2f(x, Height - (y));
		

		if (err) {
			r = max(0, r - 64);
		}
		else {
			r = max(0, r - 64);
			g = max(0, g - 64);
			b = max(0, b - 64);
		}
		if (filled) {
			r /= 2;
			g /= 2;
			b /= 2;
		}
		glColor3ub(r, g, b);
		glVertex2f(x, Height - (y + height));
		if (filled) {
			r /= 2;
			g /= 2;
			b /= 2;
		}
		glVertex2f(x + width, Height - (y + height));

	glEnd();

	if (editing || err) { r = g = b = 255; }
	else { r = g = b = 0; }

	glColor3ub(r, g, b);
	glRasterPos2f(x+3, Height - y - 20);
	for (int i = 0; i < command.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, command[i]);
	}
}

bool CommandLine::MakeTriangle(std::istringstream& iss) {
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
		return false;
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
		return false;
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

	command = symbol + " triangle " + p1 + ' ' + p2 + ' ' + p3;

	//it's nessesary to add all dependencies so when we move a point
	//our triangle will be updated
	AddDependency(pp1);
	AddDependency(pp2);
	AddDependency(pp3);
	return true;
};