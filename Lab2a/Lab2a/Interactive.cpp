#include "Header.h"


#pragma region Declaration

static int Demonstration();

static int ChoiceMode();

static int Interactive(int listType);

static int Create(int listType);

static int Insert(int listType);

static int Remove(int listType);

static int Get(int listType);

static int Set(int listType);

static int View(int listType);

static bool isDemo = false;

static void Pause() {
	std::cout << std::endl;
	if (isDemo) Sleep(1500);
	else system("pause");
}

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
		MenuItem("Demonstration", Demonstration) ,
		MenuItem("Benchmark", Benchmark) });
	menu.DoMenu();
}

int ChoiceMode() {
	initializer_list<size_t> order;
	if (isDemo) order = { 2, 1, 3 };

	Menu menu("Choose type of your list", {
		MenuItem("Fixed size", Interactive, (int)Mode::FIXEDSIZE) ,
		MenuItem("Base on vector", Interactive, (int)Mode::VECTOR) ,
		MenuItem("Linked", Interactive, (int)Mode::LINKEDLIST) });
	menu.DoMenu(order);

	return (int)MenuMode::REPEATE;
}

int Interactive(int listType) {
	initializer_list<size_t> order;
	if (isDemo) order = { 1,2,3,3,3,4,5,6,1,2,1,3,3,3,1 };

	Menu menu("Interactive mode", {
		MenuItem("View", View, listType),
		MenuItem("Create empty", Create, listType),
		MenuItem("Insert", Insert, listType),
		MenuItem("Remove", Remove, listType),
		MenuItem("Get", Get, listType),
		MenuItem("Set", Set, listType) });
	menu.DoMenu(order);

	return (int)MenuMode::REPEATE;
}

int Demonstration() {
	isDemo = true;
	ChoiceMode();
	isDemo = false;

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

	Pause();
	return (int)MenuMode::REPEATE;
}

int Create(int listType) {
	
	switch (Mode(listType)){
	case Mode::FIXEDSIZE:
		cout << "Input maximum list's size: ";
		if (isDemo) {
			listType = rand() % 100;
			SleepPrint(to_string(listType), coutSleep, coutPause);
		}
		else InputStr(listType, "", 0);

		g_fixedSize.CreateEmpty((size_t)listType);
		break;
	case Mode::VECTOR:
		g_onVector.CreateEmpty();
		break;
	case Mode::LINKEDLIST:
		g_CircularList.CreateEmpty();
	}

	cout << "Empty list was created";
	Pause();
	return (int)MenuMode::REPEATE;
}

int Insert(int listType) {
	IP element = InputIP(isDemo * (rand() % 2 + 1));

	int index = rand() % 20 - 10;
	cout << "Input index in list: ";
	if (isDemo)	SleepPrint(to_string(index), coutSleep, coutPause);
	else InputStr(index);


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

	cout << "\nSuccess";
	Pause();
	return (int)MenuMode::REPEATE;
}

int Remove(int listType) {
	IP deleted;

	int index = rand() % 20 - 10;
	cout << "Input index in list: ";
	if (isDemo) SleepPrint(to_string(index), coutSleep, coutPause);
	else InputStr(index);

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

	cout <<"\n"<< to_string(deleted) <<" successfully deleted";

	Pause();
	return (int)MenuMode::REPEATE;
}

int Get(int listType) {
	IP select;

	int index = rand() % 20 - 10;
	cout << "Input index in list: ";
	if (isDemo) SleepPrint(to_string(index), coutSleep, coutPause);
	else InputStr(index);

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

	cout << "\n" << to_string(select);

	Pause();
	return (int)MenuMode::REPEATE;
}

int Set(int listType) {
	IP element = InputIP(isDemo * (rand() % 2 + 1));

	int index = rand() % 20 - 10;
	cout << "Input index in list: ";
	if (isDemo) SleepPrint(to_string(index), coutSleep, coutPause);
	else InputStr(index);

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

	cout << "\nSuccess";

	Pause();
	return (int)MenuMode::REPEATE;
}

#pragma endregion
