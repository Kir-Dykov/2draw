#pragma once

#include <stdlib.h> //resolves some stupid redefinition problem
#include "GL/glut.h"
#include <vector>

using namespace std;

class Object {
public:
	//int red = 128, green = 128, blue = 128; 
	int red = rand()%192+64, green = rand()%192+64, blue = rand()%192+64;
	bool filled = 0;
	virtual void Draw() const{}
	void set_look(int r, int g, int b, bool fill = 1) { red = r; green = g; blue = b; filled = fill; }
};