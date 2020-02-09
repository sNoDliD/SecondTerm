#include <Windows.h>
#include "Header.h"
#include <conio.h>
#include <vector>

using std::vector;

void SetColor(int color = 14)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(color));
}

class MenuItem
{
	friend class Menu;
private:
	int index = 0;
	string nameMenuItem;
	void (*ItemsFunc)() = 0;
	void (*ItemsFuncIntReturn)(int) = 0;

public:
	MenuItem(string title = "#", void (*funcofitem)()=0)
	{
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

		SetColor(6);
		cout << "\nPress ESC to go back or exit" << endl;
		SetColor();
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
	void Do_Menu() {

		while (true)
		{
			int ans = Show_Menu();
			bool isEmpty = itemsCount < 1;
			if (ans == 0 || isEmpty )
				return;

			bool withoutFunc = menuItems[ans - 1].ItemsFunc == 0;
			if (withoutFunc)
				return;
			menuItems[ans - 1].ItemsFunc();

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

void Add() {

}

void ShopChoice() {

}

void Interactive() {
	vector <MenuItem>* all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Add", ShopChoice));
	(*all).push_back(MenuItem("Show all", ShopChoice));
	(*all).push_back(MenuItem("Search", ShopChoice));
	(*all).push_back(MenuItem("Modify", ShopChoice));
	(*all).push_back(MenuItem("Delete", ShopChoice));

	Menu* menu = new Menu("Interactive mode", all);
	(*menu).Do_Menu();
	delete menu;
}

void Demonstration() {
	Menu* menu = new Menu("Demonstration...");
	(*menu).Do_Menu();
	delete menu;
}

void Benchmark() {
	Menu* menu = new Menu("Benchmark...");
	(*menu).Do_Menu();
	delete menu;
}

void startMenu() {
	vector <MenuItem>* all = new vector<MenuItem>;
	(*all).push_back(MenuItem("Interactive", Interactive));
	(*all).push_back(MenuItem("Demonstration", Demonstration));
	(*all).push_back(MenuItem("Benchmark", Benchmark));
	
	Menu* menu = new Menu("Choose your mode:", all);
	(*menu).Do_Menu();
	delete menu;
}


//for (auto strList : { "hello", "world" })