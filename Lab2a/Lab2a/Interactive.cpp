#include "Header.h"


#pragma region Declaration

int ChoiceMode();

int Interactive(int listType);

//int Create(int listType);

int Insert(int listType);

int Remove(int listType);

int Get(int listType);

int Set(int listType);

#pragma endregion


#pragma region Start

void StartMenu() {
	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Interactive", ChoiceMode));
	all->push_back(MenuItem("Demonstration", nullptr));
	all->push_back(MenuItem("Benchmark", nullptr));

	Menu* menu = new Menu("Choose your mode:", all);
	menu->DoMenu();
	delete menu;
}

int ChoiceMode() {
	vector<MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("FixedSize list", Interactive, (int)Mode::FIXEDSIZE));
	all->push_back(MenuItem("List base on vector", Interactive, (int)Mode::VECTOR));
	all->push_back(MenuItem("Linked list", Interactive, (int)Mode::LINKEDLIST));

	Menu* menu = new Menu("Choose type of your list", all);
	menu->DoMenu();
	delete menu;

	return (int)MenuMode::REPEATE;
}

int Interactive(int listType) {	
	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Create empty"));
	all->push_back(MenuItem("Insert", Insert, listType));
	all->push_back(MenuItem("Remove", Remove, listType));
	all->push_back(MenuItem("Get", Get, listType));
	all->push_back(MenuItem("Set", Set, listType));
	
	Menu* menu = new Menu("Interactive mode", all);
	menu->DoMenu();
	delete menu;

	return (int)MenuMode::REPEATE;
}

#pragma endregion

#pragma region Action

template <typename Tlist>
void Create(int listType) {
	int index = SetIndex(Mode(listType), {Mode::FIXEDSIZE, Mode::VECTOR, Mode::LINKEDLIST});


}

int Insert(int listType) {

	return (int)MenuMode::REPEATE;
}

int Remove(int listType) {

	return (int)MenuMode::REPEATE;
}

int Get(int listType) {

	return (int)MenuMode::REPEATE;
}

int Set(int listType) {

	return (int)MenuMode::REPEATE;
}

#pragma endregion
