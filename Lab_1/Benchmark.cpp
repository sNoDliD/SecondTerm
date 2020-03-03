#include "Header.h"

int Benchmark() {
	Menu* menu = new Menu("Benchmark...");
	menu->DoMenu();
	delete menu;
	return (int)MenuMode::REPEATE;
}
