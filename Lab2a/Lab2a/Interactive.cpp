#include "Header.h"


#pragma region Declaration

static int ChoiceMode();

static int Interactive(int listType);

static int Create(int listType);

static int Insert(int listType);

static int Remove(int listType);

static int Get(int listType);

static int Set(int listType);

static int View(int listType);

#pragma endregion


#pragma region Lists

static FixedSize<IP> g_fixedSize;
static OnVector<IP> g_onVector;
static CircularList<IP> g_CircularList;

#pragma endregion


#pragma region Start

void StartMenu() {
	Menu menu("Choose your mode:", {
		MenuItem("Interactive", ChoiceMode) ,
		MenuItem("Demonstration", nullptr) ,
		MenuItem("Benchmark", nullptr) });
	menu.DoMenu();
}

int ChoiceMode() {
	Menu menu("Choose type of your list", {
		MenuItem("Fixed size", Interactive, (int)Mode::FIXEDSIZE) ,
		MenuItem("Base on vector", Interactive, (int)Mode::VECTOR) ,
		MenuItem("Linked", Interactive, (int)Mode::LINKEDLIST) });
	menu.DoMenu();

	return (int)MenuMode::REPEATE;
}

int Interactive(int listType) {
	Menu menu("Interactive mode", {
		MenuItem("View", View, listType),
		MenuItem("Create empty", Create, listType),
		MenuItem("Insert", Insert, listType),
		MenuItem("Remove", Remove, listType),
		MenuItem("Get", Get, listType),
		MenuItem("Set", Set, listType) });
	menu.DoMenu();

	return (int)MenuMode::REPEATE;
}

#pragma endregion


#pragma region Action

int View(int listType) {

	switch (Mode(listType)) {
	case Mode::FIXEDSIZE:
		cout << g_fixedSize.ToString("\n", true);
		break;
	case Mode::VECTOR:
		cout << g_onVector.ToString("\n", true);
		break;
	case Mode::LINKEDLIST:
		cout << g_CircularList.ToString("\n", true);
	}

	cout << endl;
	system("pause");
	return (int)MenuMode::REPEATE;
}

int Create(int listType) {
	
	switch (Mode(listType)){
	case Mode::FIXEDSIZE:
		InputStr(listType, "Input maximum size: ", 0);
		g_fixedSize.CreateEmpty((size_t)listType);
		break;
	case Mode::VECTOR:
		g_onVector.CreateEmpty();
		break;
	case Mode::LINKEDLIST:
		g_CircularList.CreateEmpty();
	}

	return (int)MenuMode::REPEATE;
}

int Insert(int listType) {
	IP element = InputIP();
	int index;
	InputStr(index, "Input index in list: ");

	switch (Mode(listType)) {
	case Mode::FIXEDSIZE:
		g_fixedSize.Insert(element, index);
		break;
	case Mode::VECTOR:
		g_onVector.Insert(element, index);
		break;
	case Mode::LINKEDLIST:
		g_CircularList.Insert(element, index);
	}

	cout << "\nSuccess\n";
	system("pause");
	return (int)MenuMode::REPEATE;
}

int Remove(int listType) {
	int index;
	InputStr(index, "Input index in list: ");
	IP deleted;
	switch (Mode(listType)) {
	case Mode::FIXEDSIZE:
		deleted = g_fixedSize.Remove(index);
		break;
	case Mode::VECTOR:
		deleted = g_onVector.Remove(index);
		break;
	case Mode::LINKEDLIST:
		deleted = g_CircularList.Remove(index);
	}

	cout <<"\n"<< to_string(deleted) <<" successfully deleted\n";
	system("pause");
	return (int)MenuMode::REPEATE;
}

int Get(int listType) {
	int index;
	InputStr(index, "Input index in list: ");
	IP select;
	switch (Mode(listType)) {
	case Mode::FIXEDSIZE:
		select = g_fixedSize.Get(index);
		break;
	case Mode::VECTOR:
		select = g_onVector.Get(index);
		break;
	case Mode::LINKEDLIST:
		select = g_CircularList.Get(index);
	}

	cout << "\n" << to_string(select) << "\n";

	system("pause");
	return (int)MenuMode::REPEATE;
}

int Set(int listType) {
	IP element = InputIP();
	int index;
	InputStr(index, "Input index in list: ");

	switch (Mode(listType)) {
	case Mode::FIXEDSIZE:
		g_fixedSize.Set(element, index);
		break;
	case Mode::VECTOR:
		g_onVector.Set(element, index);
		break;
	case Mode::LINKEDLIST:
		g_CircularList.Set(element, index);
	}

	cout << "\nSuccess\n";
	system("pause");

	return (int)MenuMode::REPEATE;
}

#pragma endregion
