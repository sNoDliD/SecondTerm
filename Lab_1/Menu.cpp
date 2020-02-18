#include <Windows.h>
#include "Header.h"
#include <conio.h>
#include <vector>


using std::vector;

int shopId = 0;
Mode workMode = Mode::WAIT;

void SetColor(int color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(color));
}

void SetColor(int color, const char* str){
	SetColor(color);
	cout << str << endl;
	SetColor();
}


class MenuItem
{
	friend class Menu;
private:
	int index = 0;
	string nameMenuItem;
	int (*ItemsFunc)() = nullptr;
	void (*ItemsFuncIntReturn)(int) = nullptr;
	int returnValue = -1;

public:
	MenuItem(string title = "#", int (*funcofitem)()= nullptr, int value = -1)
	{
		returnValue = value;
		nameMenuItem = title;
		ItemsFunc = funcofitem;
	}
	MenuItem(string title, void (*funcofitem)(int))
	{
		nameMenuItem = title;
		ItemsFuncIntReturn = funcofitem;
	}
};

class Menu : MenuItem
{

private:
	int itemsCount;
	string title;
	vector<MenuItem> menuItems;
	void getView_menuItems(int key){
		SetColor();
		cout << title << "\n\n";

		int j = 1;
		for (vector <MenuItem> ::iterator i = menuItems.begin(); i < menuItems.end(); i++, j++){
			if (key == j){
				SetColor(48);
				cout <<" >> "<< i->nameMenuItem << '\n';
				SetColor();
			}
			else{
				cout <<"    "<< i->nameMenuItem << '\n';
			}
		}

		SetColor(6, "\nPress ESC to go back or exit");
	}

public:
	Menu(string title = "#", vector <MenuItem>* items = new vector<MenuItem>){
		this->title = title;
		set_menuItems(*items);
		delete items;
	}

	void set_menuItems(vector <MenuItem> items) {
		itemsCount = items.size();
		menuItems = items;
		for (int i = 0, n = items.size(); i < n; ++i)
			menuItems[i].index = i + 1;
	}

	int Show_Menu() {
		int key = 1, code = 0;
		while (code != 13){
			system("cls");

			if (key <= 0) key = itemsCount;
			if (key > itemsCount) key = 1;

			getView_menuItems(key);

			code = _getch();

			if (code == 80)
				key++;
			if (code == 72)
				key--;

			if (code == 27)
				return 0;
		}
		system("cls");

		return key;
	}
	int Do_Menu() {

		while (true)
		{
			int ans = Show_Menu();
			bool isEmpty = itemsCount < 1;
			if (ans == 0 || isEmpty)
				return -1;

			bool withoutFunc = (menuItems[ans - 1].ItemsFunc == 0 &&
				menuItems[ans - 1].ItemsFuncIntReturn == 0);
			if (withoutFunc) {
				return menuItems[ans - 1].returnValue;
			}
			//if functhion return 0 refresh menu, else return value
			if (menuItems[ans - 1].ItemsFunc != 0) {
				int result = menuItems[ans - 1].ItemsFunc();
				if (result != 0)
					return result;
			}
			else {
				cout << "0 func, do another";
				system("pause");

			}


		}
	}
};


void f1() {
	string name = "";

	while (true)
	{
		int a = _getch();
		switch (a)
		{
		case 224:
		{
			int b = _getch();
			switch (b)
			{
			case 72: //up
			case 80: //down
			case 77: 
			case 75: 
				break;
			case 224: //p
				name += 'p';
				break;
			case 8: //backspace
				break;
			case 27: //esc
				break;
			case 13: //enter
				break;
			default:
				name += "p";
				name += char(b);
				break;
			}
			break;
		}
		case 8: //backspace
			if(name.length() > 0)
				name.pop_back();
			break;
		case 27: //esc
			return;
			break;
		case 13: //enter
			break;
		default:
			name += a;
			break;
		}
		system("cls");
		cout <<name<< endl << "ESC to exit";

		COORD cr;
		HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);
		cr.X = name.size();
		cr.Y = 0;
		SetConsoleCursorPosition(hnd, cr);
	}
}

void AddTxt() {
	ProductString* newProduct = new ProductString();

	cout << "Enter product's name: ";
	getline(cin, newProduct->name);
	cout << "(perfect)\n\n";

	cout << "Enter product's date in format day.mount.year hours:minutes (15.02.2002 21:10)" << endl;
	InputStr(newProduct->date);
	cout << "(perfect)\n\n";

	cout << "Enter product's expiration days:" << endl;
	InputStr(newProduct->expirationDate);
	cout << "(perfect)\n\n";

	vector <MenuItem>* all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Bag", nullptr, (int)Units::BAG));
	(*all).push_back(MenuItem("Kilogramms", nullptr, (int)Units::KILOGRAMMS));
	(*all).push_back(MenuItem("Liters", nullptr, (int)Units::LITERS));
	(*all).push_back(MenuItem("Piece", nullptr, (int)Units::PIECE));

	Menu* menu = new Menu("Choose units of product", all);
	int unitId = (*menu).Do_Menu();
	delete menu;

	newProduct->units = Units(unitId);

	cout << "Enter product's count in " << UnitsToString(unitId) << ":\n";


	InputStr(newProduct->count);
	if (Units(unitId) == Units::BAG || Units(unitId) == Units::PIECE)
		newProduct->count = (int)newProduct->count;
	system("cls");

	newProduct->storeId = shopId;
	newProduct->id = GetLastIdTxt();

	AppendProductTxt(newProduct);
	cout << newProduct->ToString() << "\n\nSuccess" << endl;
	delete newProduct;
}

void AddVector() {
	Product* newProduct = new Product();

	cout << "Enter product's name: ";
	InputStr(newProduct->name);
	cout << "(perfect)\n\n";

	cout << "Enter product's date in format day.mount.year hours:minutes (15.02.2002 21:10)" << endl;
	InputStr(newProduct->date);
	cout << "(perfect)\n\n";

	cout << "Enter product's expiration days:" << endl;
	InputStr(newProduct->expirationDate);
	cout << "(perfect)\n\n";

	vector <MenuItem>* all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Bag", nullptr, (int)Units::BAG));
	(*all).push_back(MenuItem("Kilogramms", nullptr, (int)Units::KILOGRAMMS));
	(*all).push_back(MenuItem("Liters", nullptr, (int)Units::LITERS));
	(*all).push_back(MenuItem("Piece", nullptr, (int)Units::PIECE));

	Menu* menu = new Menu("Choose units of product", all);
	int unitId = (*menu).Do_Menu();
	delete menu;

	newProduct->units = Units(unitId);

	cout << "Enter product's count in " << UnitsToString(unitId) << ":\n";


	InputStr(newProduct->count);
	if (Units(unitId) == Units::BAG || Units(unitId) == Units::PIECE)
		newProduct->count = (int)newProduct->count;
	system("cls");

	newProduct->storeId = shopId;
	newProduct->id = GetLastIdVector() + 1;

	AppendProductVector(newProduct);
	cout << newProduct->ToString() << "\n\nSuccess" << endl;
	delete newProduct;
}

void AddBin() {
	Product* newProduct = new Product();

	cout << "Enter product's name: ";
	InputStr(newProduct->name);
	cout << "(perfect)\n\n";

	cout << "Enter product's date in format day.mount.year hours:minutes (15.02.2002 21:10)" << endl;
	InputStr(newProduct->date);
	cout << "(perfect)\n\n";

	cout << "Enter product's expiration days:" << endl;
	InputStr(newProduct->expirationDate);
	cout << "(perfect)\n\n";

	vector <MenuItem>* all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Bag", nullptr, (int)Units::BAG));
	(*all).push_back(MenuItem("Kilogramms", nullptr, (int)Units::KILOGRAMMS));
	(*all).push_back(MenuItem("Liters", nullptr, (int)Units::LITERS));
	(*all).push_back(MenuItem("Piece", nullptr, (int)Units::PIECE));

	Menu* menu = new Menu("Choose units of product", all);
	int unitId = (*menu).Do_Menu();
	delete menu;

	newProduct->units = Units(unitId);

	cout << "Enter product's count in " << UnitsToString(unitId) << ":\n";


	InputStr(newProduct->count);
	if (Units(unitId) == Units::BAG || Units(unitId) == Units::PIECE)
		newProduct->count = (int)newProduct->count;
	system("cls");

	newProduct->storeId = shopId;
	newProduct->id = GetLastIdBin();

	AppendProductBin(newProduct);
	cout << newProduct->ToString() << "\n\nSuccess" << endl;
	delete newProduct;
}

int Add() {
	switch (workMode)
	{
	case Mode::VECTOR:
		AddVector();
		break;
	case Mode::TXT:
		AddTxt();
		break;
	case Mode::BIN:
		AddBin();
	}
	system("pause");
	return 0;
}

bool ShowAllVector() {
	Product* a;
	int i = 0;
	bool isProductFind = false;
	while (true) {
		a = TakeProductVector(i);
		if (a == nullptr) break;
		if (a->storeId == shopId) {
			isProductFind = true;
			cout << (*a).ToString() << endl;
		}
		++i;
	}
	delete a;
	return isProductFind;

}

bool ShowAllTxt() {
	ProductString* a;
	int i = 0;
	bool isProductFind = false;
	while (true) {
		a = TakeProductTxt(i++);
		if (a == nullptr) 
			break;
		if (a->storeId == shopId) {
			isProductFind = true;
			cout << (*a).ToString() << endl;
		}
		delete a;
	}
	return isProductFind;
}

bool ShowAllBin() {
	Product* a;
	int i = 0;
	bool isProductFind = false;
	while (true) {
		a = TakeProductBin(i++);
		if (a == nullptr) 
			break;
		if (a->storeId == shopId) {
			isProductFind = true;
			cout << a->ToString() << endl;
		}
		delete a;
	}
	return isProductFind;
}

int ShowAll() {
	bool isProductFind = false;
	switch (workMode)
	{
	case Mode::VECTOR:
		isProductFind = ShowAllVector();
		break;
	case Mode::TXT:
		isProductFind = ShowAllTxt();
		break;
	case Mode::BIN:
		isProductFind = ShowAllBin();
		break;
	}
	if (!isProductFind) 
		cout << "Store is empty\n\n";
	system("pause");
	return 0;
}

int Search() {
	vector <MenuItem>* all = new vector<MenuItem>;
	(*all).push_back(MenuItem("By name", nullptr, 1));
	(*all).push_back(MenuItem("By amount", nullptr, 2));
	(*all).push_back(MenuItem("By date", nullptr, 3));

	Menu* menu = new Menu("Search type:", all);
	int type = (*menu).Do_Menu();
	delete menu;

	switch (type)
	{
	case 1:
		cout << "name";
		system("pause");
		break;
	case 2:
		cout << "amount";
		system("pause");
		break;
	case 3:
		cout << "date";
		system("pause");
		break;
	}

	return 0;
}

int Interactive() {
	vector <MenuItem>* all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Choose shop", ShopChoice));
	(*all).push_back(MenuItem("Create new", ShopCreate));

	Menu* menu = new Menu("Choose or create shop:", all);
	shopId = (*menu).Do_Menu();
	delete menu;
	if (shopId == -1)
		return 0;
	all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Vector", nullptr, 1));
	(*all).push_back(MenuItem("Text", nullptr, 2));
	(*all).push_back(MenuItem("Binary",nullptr, 3));

	menu = new Menu("Choose your read/write mode", all);
	int mode = (*menu).Do_Menu();
	delete menu;
	if (mode == -1)
		return 0;
	workMode = Mode(mode);

	all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Add", Add));
	(*all).push_back(MenuItem("Show all", ShowAll));
	(*all).push_back(MenuItem("Search", Search));
	(*all).push_back(MenuItem("Modify"));
	(*all).push_back(MenuItem("Delete"));

	menu = new Menu("Interactive mode", all);
	(*menu).Do_Menu();
	delete menu;
	return 0;
}

int Demonstration() {
	Menu* menu = new Menu("Demonstration...");
	(*menu).Do_Menu();
	delete menu;
	return 0;
}

int Benchmark() {
	Menu* menu = new Menu("Benchmark...");
	(*menu).Do_Menu();
	delete menu;
	return 0;
}

int StartMenu() {
	vector <MenuItem>* all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Interactive", Interactive));
	(*all).push_back(MenuItem("Demonstration", Demonstration));
	(*all).push_back(MenuItem("Benchmark", Benchmark));
	
	Menu* menu = new Menu("Choose your mode:", all);
	(*menu).Do_Menu();
	delete menu;
	return 0;
}

int ShopChoice() {
	vector <MenuItem>* all = new vector<MenuItem>;
	Store* a;
	int i = 0;
	while (true) {
		a = TakeStore(i);
		if (a == nullptr) break;
		(*all).push_back(MenuItem(a->name, nullptr, a->id));
		++i;
	}
	delete a;


	if (i == 0) {
		cout << "Don't find any shops. Create new...\n\n";
		ShopCreate();
		return 0;
	}
	else {
		Menu* menu = new Menu("Choose your mode:", all);
		int result = (*menu).Do_Menu();
		delete menu;
		return result;
	}
}

int ShopCreate() {
	Store* newStore = new Store();

	cout << "Enter shop's name: ";
	InputStr(newStore->name);
	cout << "(perfect)" << endl << endl;

	cout << "Enter shop's adress: ";
	InputStr(newStore->adress);
	cout << "(perfect)" << endl << endl;

	cout << "Enter shop's rating: ";
	InputStr(newStore->rating);
	while (newStore->rating < 0 || newStore->rating > 10) {
		SetColor(6, "\tRating should be in interval [0,10]. Try again");
		InputStr(newStore->rating);
	}
	cout << "(perfect)" << endl << endl;

	cout << "Enter shop's maximum of product count: ";
	InputStr(newStore->maxProductCount);
	while (newStore->maxProductCount < 1) {
		SetColor(6, "\tReal?) Product count should be more than 0. Try again");
		InputStr(newStore->maxProductCount);
	}

	newStore->id = GetLastIdStore();

	AppendStore(newStore);
	delete newStore;
	return 0;
}