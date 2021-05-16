#pragma once
#include <string>;
struct Action {
	size_t index = 0;
	std::string prev_command = "";
	std::string new_command = "";

	Action() {};
	Action(size_t i, const string& p, const string& n) {
		index = i;
		prev_command = p;
		new_command = n;
	}
};