#pragma once

#include <stdlib.h> //resolves some stupid redefinition problem
#include "glut.h"
#include <vector>

using namespace std;

class Object {
public:
	//int red = 128, green = 128, blue = 128; 
	int red = rand()%128+128, green = rand() % 128 + 128, blue = rand() % 128 + 128;
	bool filled = 0;
	virtual void Draw() const{}
	void set_look(int r, int g, int b, bool fill = 1) { red = r; green = g; blue = b; filled = fill; }
};

class ObjectList : public vector<Object> {
	void Draw() {
		for (size_t i = 0; i < this->size(); i++) {
			(*this)[i].Draw();
		}
	}
	/*explicit operator vector<Object>;
	ObjectList(const vector<Object>& v) {
		this->resize(v.size());
		for (size_t i = 0; i < v.size(); i++)
		{
			(*this)[i] = v[i];
		}
	}*/
};
