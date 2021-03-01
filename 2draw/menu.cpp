#include "tests/hello_world.h"
#include "tests/polygon_tests.h"

#include<string>
#include<conio.h>
#include<windows.h>
#include<iostream>

#include <vector>
#include "menu.hpp"

// add your menu positions here
// first parameter is the name of your position that is printed
// second parameter is the name of a function that is to be executed
std::vector<MenuPos> menu_positions = {
		MenuPos("Hello World Programm", hello_world_main),
		MenuPos("Polygon testing", polygon_main),
		
};

std::ostream& operator<<(std::ostream& os, const MenuPos& mp) { os << mp.name; return os; }

void draw_menu() {
	system("cls");
	std::cout << "Press a number of needed option (Esc to exit):\n";
	for (unsigned int i = 0; i < menu_positions.size(); i++){
		std::cout << i << ". " << menu_positions[i] << std::endl;
	}
}

int menu_main(){
	if (menu_positions.size() > 10) {
		std::cout << "too many menu positions! (must be <=10) \n abort...\n";
		_getch();
		exit(0);
	}
	
	int code;
	for (;;) {
		draw_menu();
		code = _getch();
		if (code-48 >= 0 && code-48 <= menu_positions.size()-1){
			system("cls");
			menu_positions[code - 48].execute();
			std::cout << "\n\npress any key to continue: ";
			code = _getch();
		}
		else if (code == 27) {
			exit(0);
		}
	}

	return 0;
}
