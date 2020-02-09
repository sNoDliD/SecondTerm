#include <Windows.h>
#include "Header.h"
#include <conio.h>
#include <vector>

using std::vector;
void SetColor(int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(text));
}



class MenuItem
{
	friend class Menu; //incapsulation: to protect variables of MenuItem from another classes except Menu
private:
	int num = 0;
	string nameMenuItem;
	void (*FuncMenuItem)();

public:
	MenuItem(string title = "#", int numofitems = 0, void (*funcofitem)()=0)
	{
		nameMenuItem = title;
		num = numofitems;
		FuncMenuItem = funcofitem;
	}
};

class Menu : MenuItem
{

private:
	int numofitems;
	string title;
	vector<MenuItem> menuItems;
	void getView_menuItems(int key)
	{
		SetColor(0, 3);
		cout << title << "\n\n";
		SetColor(15, 0);
		int j = 0;
		for (vector <MenuItem> ::iterator i = menuItems.begin(); i < menuItems.end(); i++)
		{
			j++;
			if (key == j)
			{
				SetColor(0, 6);
				cout << i->nameMenuItem << '\n';
				SetColor(15, 0);
			}
			else
			{
				cout << i->nameMenuItem << '\n';
			}
		}

		SetColor(0, 7);
		cout << "\n0 - back/exit" << endl;
		SetColor(15, 0);
	}
public:

	Menu(vector <MenuItem> items, string title = "#"){
		this->title = title;
		set_menuItems(items);
	}

	void set_menuItems(vector <MenuItem> items) {
		numofitems = items.size();
		menuItems = items;
	}
	int Show_Menu() {
		int key = 1, code = 0;
		while (code != 13)
		{
			system("cls");

			if (key == 0) key = numofitems;
			if (key == (numofitems + 1)) key = 1;

			getView_menuItems(key);

			code = _getch();

			if (code == 80)
				key++;
			if (code == 72)
				key--;

			if (code == 48)
				return 0;
		}
		system("cls");

		return key;
	}
	void Do_Menu() {

		while (true)
		{
			int ans = Show_Menu();
			if (ans == 0)
				return;
			menuItems[ans - 1].FuncMenuItem();

		}
	}
};


void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}



void f1() {
	cout << 1;
	system("pause");
}
void f2() {
	cout << 2;
}
void f3() {
	cout << 3;
}
void doMenu() {
	vector <MenuItem> all;
	all.push_back(MenuItem("title1", 1, f1));
	all.push_back(MenuItem("title2", 2, f2));
	all.push_back(MenuItem("title3", 3, f3));
	
	Menu* menu = new Menu(all, "random text");
	(*menu).Do_Menu();
	delete menu;
}