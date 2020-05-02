#include "Menu.h"

void SetColor(int color){
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
}

bool ShowConsoleCursor(bool active) {
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return false;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return false;
	cci.bVisible = active;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return false;
	return true;
}


MenuItem::MenuItem(string title, int (*FuncOfItem)()){
	nameMenuItem = title;
	Func = FuncOfItem;
}

MenuItem::MenuItem(string title, int (*FuncOfItem)(int), int value){
	returnValue = value;
	nameMenuItem = title;
	IntFunc = FuncOfItem;
}

void Menu::ViewItems() {
	system("cls");
	ShowConsoleCursor(false);
	cout << title << "\n\n";

	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
	firstItemLine = bi.dwCursorPosition.Y;

	for (auto i = menuItems.begin(); i < menuItems.end(); i++)
		cout << "    " << i->nameMenuItem << '\n';
	SetColor(6, "\n", endMessage);
}

void Menu::ReDrawItems(size_t select, size_t update){
	if (update == 0) 
		update = 1;
	system("COLOR 07");

	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cr;

	cr.X = 1;
	cr.Y = (short)(firstItemLine + update - 1);
	SetConsoleCursorPosition(handle, cr);
	cout << "  ";

	cr.X = 0;
	cr.Y = (short)(firstItemLine + menuItems.size() + 1);
	SetConsoleCursorPosition(handle, cr);
	SetColor(FOREGROUND_GREEN | FOREGROUND_RED, endMessage);

	cr.X = 0;
	cr.Y = (short)(firstItemLine + select - 1);
	SetConsoleCursorPosition(handle, cr);
	SetColor(48, " >> ", (menuItems.begin() + select - 1)->nameMenuItem, '\n');
	
}

void Menu::SetMenuItems(std::initializer_list <MenuItem> items) {
	menuItems = items;
	for (int i = 0, n = items.size(); i < n; ++i) {
		menuItems[i].index = i + 1;
	}
}

int Menu::ShowMenu(const size_t& choice, const size_t& selectTime,const size_t& switchTime){
	ViewItems();

	for(size_t key = 1; key <= choice; key++) {
		ReDrawItems(key, key - 1);
		Sleep(switchTime);
	}
	Sleep(selectTime);
	system("cls");
	return choice;
}

int Menu::ShowMenu() {
	ViewItems();
	size_t key = 1;
	int code = 0;
	ReDrawItems(key);

	while (code != 13) {
		code = _getch();

		if (code == 224) {
			code = _getch();
			size_t temp = key;

			if (code == 80 && ++key > menuItems.size())
				key = 1;
			else if (code == 72 && --key == 0) 
				key = menuItems.size();
			ReDrawItems(key, temp);
		}
		else if (code == 27)
			return (int) MenuMode::PressEsc;
	}
	system("cls");
	ShowConsoleCursor(true);
	return key;
}

Menu::Menu(string title, std::initializer_list <MenuItem> items, string endMessage) :
	title(title), endMessage(endMessage) {
	SetMenuItems(items);
}

int Menu::DoMenu(initializer_list<size_t> order, size_t selectTime, size_t totalSwitchTime) {
	int currentKey = 0, ans;

	while (true) {
		if(order.size() == 0) ans = ShowMenu();
		else {
			if (currentKey == order.size())
				return (int)MenuMode::EXIT;
			size_t choice = *(order.begin() + currentKey++);
			
			if (choice != 0)
				ans = ShowMenu(choice, selectTime, Between(totalSwitchTime / choice, 200, 500));
			else ans = ShowMenu();
		}

		bool isEmpty = menuItems.size() == 0;

		if (ans == (int)MenuMode::PressEsc || isEmpty)
			return (int)MenuMode::EXIT;

		bool withoutFunc = (menuItems[ans - 1].Func == nullptr &&
			menuItems[ans - 1].IntFunc == nullptr);
		if (withoutFunc)  return menuItems[ans - 1].returnValue;

		int result;
		if (menuItems[ans - 1].Func != nullptr)
			result = menuItems[ans - 1].Func();
		else 
			result = menuItems[ans - 1].IntFunc(menuItems[ans - 1].returnValue);
		if (result != (int)MenuMode::REPEATE) return result;
	}
}

size_t Between(size_t value, size_t left, size_t right) {
	return max(min(value, right), left);
}

	
