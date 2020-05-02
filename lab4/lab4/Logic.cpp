#include "MainHeader.h"
#include "Menu.h"

const int INTERACTIVE_MODE = 1;
const int DEMONSTRATION_MODE = 0;

IntTree intTree;

static int intTreePrint(int mode)
{
	return int(MenuMode::REPEATE);
}

static int intTreeAdd(int mode)
{
	return int(MenuMode::REPEATE);
}

static int intTreeRemove(int mode)
{
	return int(MenuMode::REPEATE);
}

static int intTreeMenu(int mode)
{
	initializer_list<size_t> order;
	if (mode == DEMONSTRATION_MODE) order = { 2, 1, 3, 1 };

	Menu menu("Choose function:", {
		MenuItem("Print", intTreePrint, mode),
		MenuItem("Add", intTreeAdd, mode),
		MenuItem("Remove", intTreeRemove, mode) });
	menu.DoMenu(order);

	return int(MenuMode::REPEATE);
}

static int interactive(int mode)
{
	initializer_list<size_t> order;
	if (mode == DEMONSTRATION_MODE) order = { 3, 1, 2 };

	Menu menu("Choose tree:", {
		MenuItem("Int Tree", intTreeMenu, mode),
		MenuItem("Bin Tree"),
		MenuItem("Catalogs Tree") });
	menu.DoMenu(order);

	return int(MenuMode::REPEATE);
}

void EnterPoint() 
{
	Menu menu("Choose mode:", {
		MenuItem("Interactive", interactive, INTERACTIVE_MODE),
		MenuItem("Demonstation", interactive, DEMONSTRATION_MODE) });
	menu.DoMenu();

	system("cls");
	cout << "Program completed successfully" << endl;
}

