#include "Header.h"
#include <cmath>
#include <iostream>
#include <string>


void StartMenu() {
	Menu menu("Choose your mode:", {
		MenuItem("Demonstration", Demonstration),
		MenuItem("Benchmark", Benchmark)
		});
	menu.DoMenu();
}

int Demonstration(){

	return (int)MenuMode::REPEATE;
}
