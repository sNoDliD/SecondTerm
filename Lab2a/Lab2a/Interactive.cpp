#include "Header.h"


#pragma region Declaration

int ChoiceMode();
int Interactive(int listType);

#pragma endregion


#pragma region Start

void StartMenu() {
	OnVector<int> a;
	a.Insert(1, 3);
	a.Insert(2, 3);
	a.Insert(3, 3);
	a.Insert(4, 3);
	a.Insert(5, -1);
	cout << a.Remove(1);
	system("pause");

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
	SetWorkMode(Mode(listType));
	
	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Create empty"));
	all->push_back(MenuItem("Insert"));
	all->push_back(MenuItem("Remove"));
	all->push_back(MenuItem("Get"));
	all->push_back(MenuItem("Set"));
	
	Menu* menu = new Menu("Interactive mode", all);
	menu->DoMenu();
	delete menu;

	return (int)MenuMode::REPEATE;
}

#pragma endregion

#pragma region Action



#pragma endregion
