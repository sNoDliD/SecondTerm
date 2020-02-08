#include <Windows.h>
#include "Header.h"

void SetColor(int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(text));
}

void doMenu() {
    HANDLE hOut;
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    COORD NewSBSize;
    int Status;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hOut, &SBInfo);
    NewSBSize.X = SBInfo.dwSize.X - 2;
    NewSBSize.Y = SBInfo.dwSize.Y;

    Status = SetConsoleScreenBufferSize(hOut, NewSBSize);
    if (Status == 0)
    {
        Status = GetLastError();
        cout << "SetConsoleScreenBufferSize() failed! Reason : " << Status << endl;
        exit(Status);
    }

    GetConsoleScreenBufferInfo(hOut, &SBInfo);

    cout << "Screen Buffer Size : ";
    cout << SBInfo.dwSize.X << " x ";
    cout << SBInfo.dwSize.Y << endl;
}
//#include <iostream>
//#include <string>
//#include <vector>
//#include <conio.h>
////#include <math.h>
////#include "structures.h"
//
//using namespace std;
//
//class MenuItem
//{
//	friend class Menu; //incapsulation: to protect variables of MenuItem from another classes except Menu
//private:
//	//User user;
//	string user;
//	int num = 0;
//	string nameMenuItem;
//	void (*FuncMenuItem)() = 0;
//	//void (*FuncMenuItem2)(User& user) = 0;
//	void (*FuncMenuItem2)(string& user) = 0;
//
//public:
//	//constructors
//	MenuItem()
//	{}
//
//	MenuItem(string title, int numofitems, void (*funcofitem)())
//	{
//		nameMenuItem = title;
//		num = numofitems;
//		FuncMenuItem = funcofitem;
//	}
//
//	//MenuItem(string title, int numofitems, void (*funcofitem)(User& user), User& user)
//	MenuItem(string title, int numofitems, void (*funcofitem)(string& user), string& user)
//	{
//		this->user = user;
//		nameMenuItem = title;
//		num = numofitems;
//		FuncMenuItem2 = funcofitem;
//	}
//
//	/*User getUser()
//	{
//		return user;
//	}*/
//};
//
//class Menu : MenuItem
//{
//
//private:
//	int numofitems;
//	string title;
//	vector<MenuItem> menuItems;
//	void getView_menuItems(int key);
//public:
//	//constructors
//	Menu()
//	{
//		this->title = "#";
//		numofitems = 0;
//	}
//
//	Menu(int numofitems, string title)
//	{
//		this->numofitems = numofitems;
//		this->title = title;
//	}
//
//	//Menu(int numofitems, string title, User& user)
//	Menu(int numofitems, string title, string& user)
//	{
//		this->numofitems = numofitems;
//		this->title = title + user + "!";
//	}
//
//	void set_menuItems(vector <MenuItem> items);
//	int Show_Menu();
//	void Do_Menu();
//};
//
////functions
//
////make main menu
//void MainMenu();
//
////admin menu
////void AdminMenu(User&);
//void AdminMenu(string&);
//
////user menu
//void UserMenu(string&);
//
//HANDLE hConsole, hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//
//void SetColor(int text, int background)
//{
//	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
//}
//
////draw menu
//void Menu::Do_Menu()
//{
//
//	while (true)
//	{
//		int ans = Show_Menu();
//		if (ans == 0)
//			return;
//
//		if (menuItems[ans - 1].FuncMenuItem2 != 0)
//			menuItems[ans - 1].FuncMenuItem2(menuItems[ans - 1].user);
//		else
//			menuItems[ans - 1].FuncMenuItem();
//
//	}
//}
//
////setter
//void Menu::set_menuItems(vector <MenuItem> items)
//{
//	menuItems = items;
//}
//
//
//int Menu::Show_Menu()
//{
//	int key = 1, code = 0;
//	while (code != 13)
//	{
//		system("cls");
//
//		if (key == 0) key = numofitems;
//		if (key == (numofitems + 1)) key = 1;
//
//		getView_menuItems(key);
//
//		code = _getch();
//
//		if (code == 80)
//			key++;
//		if (code == 72)
//			key--;
//
//		if (code == 48)
//			return 0;
//	}
//	system("cls");
//
//	return key;
//}
//
////getter
//void Menu::getView_menuItems(int key)
//{
//	SetColor(0, 3);
//	std::cout << title << std::endl << std::endl;
//	SetColor(15, 0);
//	int j = 0;
//	for (vector <MenuItem> ::iterator i = menuItems.begin(); i < menuItems.end(); i++)
//	{
//		j++;
//		if (key == j)
//		{
//			SetColor(0, 6);
//			//std::cout << i->num << ". ";
//			std::cout << i->nameMenuItem << std::endl;
//			SetColor(15, 0);
//		}
//		else
//		{
//			//std::cout << i->num << ". ";
//			std::cout << i->nameMenuItem << std::endl;
//		}
//	}
//
//	SetColor(0, 7);
//	std::cout << std::endl << "0 - back/exit" << std::endl;
//	SetColor(15, 0);
//}
//
