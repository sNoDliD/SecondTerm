#include "Header.h"

static bool isDemo = false;
static int Demonstration();
static int Interactive();

bool IsDemo() {
	return isDemo;
}

void StartMenu() {
	Menu menu("Choose your mode:", {
		MenuItem("Interactive", Interactive),
		MenuItem("Demonstration", Demonstration) });
	menu.DoMenu();
}

int Interactive() {
	initializer_list<size_t> order;
	if (IsDemo()) order = { 3, 1, 2 };

	Menu menu("Choose task:", {
		MenuItem("7", Task7),
		MenuItem("15", Task15),
		MenuItem("25", Task25), });
	menu.DoMenu(order);

	return (int)MenuMode::REPEATE;
}

int Demonstration() {
	isDemo = true;
	Interactive();
	isDemo = false;

	return (int)MenuMode::REPEATE;
}