#include "MainHeader.h"

IntTree intTree;
BinTree binTree;

static int intTreePrint(int mode)
{
	intTree.print();
	return sleep(mode);
}

static int intTreeAdd(int mode)
{
	int value = input<int>(mode, "Enter new value: ", -100, 100);
	float probabilite = input<float>(mode, "Enter probabilite: ", 0, 1);

	intTree.add(value, probabilite);
	cout << "Success\n";
	return sleep(mode);
}

static int intTreeRemove(int mode)
{
	int value = input<int>(mode, "Enter erase value: ", -100, 100);
	float probabilite = input<float>(mode, "Enter probabilite: ", 0, 1);

	intTree.removeAll(value, probabilite);
	cout << "Success\n";
	return sleep(mode);
}

static int intTreeMenu(int mode)
{
	intTree = IntTree{};
	initializer_list<size_t> order;
	if (mode == DEMONSTRATION_MODE) order = { 2, 2, 2, 2, 2, 2, 2, 1, 3 , 3, 1 };

	Menu menu("Choose function:", {
		MenuItem("Print", intTreePrint, mode),
		MenuItem("Add", intTreeAdd, mode),
		MenuItem("Remove", intTreeRemove, mode) });
	menu.DoMenu(order);

	return int(MenuMode::REPEATE);
}

static int binTreePrint(int mode) {
	binTree.print();
	return sleep(mode);
}

static int binTreeAdd(int mode) {
	int value = input<int>(mode, "Enter new value: ", -100, 100);

	binTree.add(value);
	cout << "Success\n";
	return sleep(mode);
}

static int binTreePreorderPrint(int mode) {
	binTree.preorderPrint();
	return sleep(mode);
}

static int binTreeMenu(int mode) {
	binTree = BinTree{};
	initializer_list<size_t> order;
	if (mode == DEMONSTRATION_MODE) order = { 2, 2, 2, 2, 2, 2, 2, 1, 3 };

	Menu menu("Choose function:", {
		MenuItem("Print", binTreePrint, mode),
		MenuItem("Add", binTreeAdd, mode),
		MenuItem("Preorder Print", binTreePreorderPrint, mode) });
	menu.DoMenu(order);

	return int(MenuMode::REPEATE);
}

static int interactive(int mode)
{
	initializer_list<size_t> order;
	if (mode == DEMONSTRATION_MODE) order = {1, 2};

	Menu menu("Choose tree:", {
		MenuItem("Int Tree", intTreeMenu, mode),
		MenuItem("Bin Tree", binTreeMenu, mode)});
	menu.DoMenu(order);

	return int(MenuMode::REPEATE);
}

void EnterPoint() 
{
	srand(time(0));
	
	Menu menu("Choose mode:", {
		MenuItem("Interactive", interactive, INTERACTIVE_MODE),
		MenuItem("Demonstation", interactive, DEMONSTRATION_MODE) });
	menu.DoMenu();

	system("cls");
	cout << "Program completed successfully" << endl;
}

