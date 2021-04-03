#pragma once
#include <string>

class MenuPos {
public:
	std::string name;
	int (*entry)();
	MenuPos(std::string _name, int (*_entry)()) { name = _name; entry = _entry; }
	int execute() { return entry(); }

};

int menu_main();