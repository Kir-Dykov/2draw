#pragma once

#include <stdlib.h> //resolves some stupid redefinition problem
#include "glut.h"
#include <vector>

using namespace std;

class Object {
public:
	int red = 128, green = 128, blue = 128; 
	bool filled = 0;
	virtual void Draw() const{}
	void set_look(int r, int g, int b, bool fill = 1) { red = r; green = g; blue = b; filled = fill; }
};

class ObjectList {
	vector<Object*> list;
public:
	void append(Object& obj) {
		list.push_back(&obj);
	}

	void Draw() {
		for (int i = 0; i < list.size(); i++) list[i]->Draw();
	}

};