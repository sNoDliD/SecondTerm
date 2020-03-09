#include "Header.h"

class SkipList {

	class Node {
		int value;
		Node* next;
		Node* down = nullptr;
	public :
		Node(int value, Node* next = nullptr) :
			value(value), next(next) {}

		friend class SkipList;
	};

	Node* head;
	size_t height;

	void Free() {
		Node* currentHead = head;
		Node* deleted;
		while (currentHead) {
			Node* current = currentHead->next;

			while (current) {
				deleted = current;
				current = current->next;
				delete deleted;
			}

			deleted = currentHead;
			currentHead = currentHead->down;
			delete deleted;
		}
	}

public:

	SkipList() : height(0) {
		head = new Node(0);
	}

	~SkipList() {
		Free();
	}

	void Print() {
		Node* currentHead = head;
		vector<int> values;
		while (currentHead->down) 
			currentHead = currentHead->down;

		size_t space = 0;
		while (currentHead->next){
			values.push_back(currentHead->next->value);
			if (to_string(values.back()).size() > space)
				space = to_string(values.back()).size();
			currentHead = currentHead->next;
		}
		currentHead = head;		

		while (currentHead){
			Node* current = currentHead->next;
			cout << currentHead->value << ": ";
			size_t posInVector = 0;

			while (current) {
				while (values[posInVector++] != current->value) {
					cout << AddChar("", space + 1);
				}
				cout <<AddChar(current->value,space) << " ";
				current = current->next;
			}
			cout << endl;
			currentHead = currentHead->down;

		}
		cout << endl;
	}

	void Add(int value) {
		Node* add = new Node(value);
		Node* lastAdd = nullptr;

		size_t towerSize = 0;
		while (rand() % 2 == 1)
			towerSize++;

		while (towerSize > height) {
			Node* newHead = new Node(++height);
			newHead->down = head;
			head = newHead;
		}

		Node* current = head;
		size_t currentHeight = height;

		while (current != nullptr){
			if (!current->next || current->next->value >= value) {
				if (currentHeight == towerSize) {
					towerSize--;
					add->next = current->next;
					current->next = add;
					if (lastAdd) lastAdd->down = add;
					lastAdd = add;
					add = new Node(value);
				}
				if (currentHeight == 0) break;
				currentHeight--;
				current = current->down;
			}
			else
				current = current->next;
		}
		delete add;
	}

	bool Cheak(int value) {
		Node* current = head;

		while (current != nullptr) {
			if (!current->next || current->next->value > value) {
				current = current->down;
			}
			else {
				current = current->next;
				if (current->value == value)
					return true;
			}
		}

		return false;
	}

	void Remove(int value) {
		Node* current = head;

		while (current != nullptr) {
			if (!current->next || current->next->value > value)
				current = current->down;
			else if (current->next->value < value)
				current = current->next;
			else {
				Node* deleted = current->next;
				current->next = deleted->next;
				delete deleted;
				current = current->down;
			}
		}

		while (head && head->down) {
			if (!head->next) {
				height--;
				Node* deleted = head;
				head = head->down;
				delete deleted;
			}
			else return;
		}
	}

	void Create() {
		Free();
		height = 0;
		head = new Node(0);
	}
};

static SkipList g_list;

static int Create();
static int Add();
static int View();
static int Find();
static int Remove();

static int Pause() {
	if (IsDemo()) Sleep(pauseTime);
	else system("pause");

	return (int)MenuMode::REPEATE;
}

int Task25() {
	initializer_list<size_t> order;
	if (IsDemo()) order = { 1, 2, 3, 4, 5, 2, 1, 4,4,2 };

	Menu menu("Choose: ", {
		MenuItem("Create random", Create),
		MenuItem("Visualize(use it for n < 30)", View),
		MenuItem("Find", Find),
		MenuItem("Add", Add),
		MenuItem("Remove", Remove) });
	menu.DoMenu(order);

	return (int)MenuMode::REPEATE;
}

int Create() {
	int size = rand() % 10 + 10;;
	if (IsDemo()) {
		SleepPrint(to_string(size), "Enter count of random elements: ");
	}
	else {
		InputStr(size, "Enter count of random elements: ", 1);
	}

	g_list.Create();
	for (; size > 0; size--)
		g_list.Add(rand() % 100 - 50);
	cout << "Created" << endl;

	return Pause();
}

int Add() {
	int value = rand() % 60 - 30;
	if (IsDemo()) {
		SleepPrint(to_string(value), "Enter the add value: ");
	}
	else {
		InputStr(value, "Enter element's value: ");
	}
	g_list.Add(value);

	cout << "Success" << endl;
	return Pause();
}

int Find() {
	int element = rand() % 60 - 30;
	if (IsDemo()) {
		SleepPrint(to_string(element), "Enter element for search: ");
	}
	else {
		InputStr(element, "Enter element for search: ");
	}

	if (g_list.Cheak(element))
		cout << element << " was find" << endl;
	else
		cout << element << " wasn't find" << endl;

	return Pause();
}

int View() {
	g_list.Print();

	return Pause();
}

int Remove() {
	int element = rand() % 60 - 30;
	if (IsDemo()) {
		SleepPrint(to_string(element), "Enter element for delete: ");
	}
	else {
		InputStr(element, "Enter element for delete: ");
	}
	bool find = g_list.Cheak(element);
	g_list.Remove(element);

	if (find) cout << "Element was deleted" << endl;
	else cout << "Element wasn't deleted" << endl;
	return Pause();

}
