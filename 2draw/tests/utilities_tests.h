#pragma once
#include <iostream>
#include "../utilities.h"

using namespace std;

int utilities_main() {

	cout << "epsilon(double d) :" << endl;
	const double init_g = 2345;
	double g = init_g;

	cout << "let g = " << g << ", then epsilon(g) = " << epsilon(g) << endl;
	
	for (int i = 0; i < 1000000; i++)
		g += 0.5*epsilon(g);

	cout << "if we add 0.5*epsilon(g) to g one billion times, then it's value does not change: g' - g = " << g - init_g << endl;

	for (int i = 0; i < 1000000; i++)
		g += epsilon(g);

	cout << "if we add epsilon(g) to g one billion times, then it's value changes by: g'' - g' = " << g - init_g << endl;

	return 0;
}