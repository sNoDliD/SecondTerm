#include "Header.h"


static int Create();
static int All();
static int Find();

static int Pause() {
	if (IsDemo()) Sleep(pauseTime);
	else system("pause");

	return (int)MenuMode::REPEATE;
}

class CircularList {
private:
	
	//number will be >= 0
	size_t mod(int& number, size_t circle) {
		if (circle == 0) {
			number = 0;
			return 0;
		}
		else {
			number = (int)fmod(number, circle);
			if (number < 0) number += circle;
			return number;
		}
	}

	class Node {
	private:
		size_t value;
		Node* next;
		Node* shortcut = nullptr;
		bool isVisited = false;

	public:
		Node(size_t value, Node* next = nullptr) : value(value), next(next) {}

		friend class CircularList;
	};

	size_t size = 0;
	Node* head = nullptr;

public:

	CircularList(size_t n = 0, float p_add = 0.5f) {
		Create(n, p_add);
	}

	~CircularList() {
		Free();
	}

	void Create(size_t n, float p_add) {
		Free();
		if (n == 0) return;
		Insert(n, 0);
		if (n == 1) return;

		if (p_add < 0 || p_add > 1.0f)
			p_add = (float)rand() / (RAND_MAX + 1);

		for (Insert(1, 0); --n > 1; Insert(n, 1));

		Node** shortcutList = new Node*[size];

		Node* current = head;
		for (size_t i = 0; i < size; i++) {
			shortcutList[i] = current;
			current = current->next;
		}

		for (size_t i = 0; i < size; i++) {
			if ((float)rand() / RAND_MAX < p_add) 
				current->shortcut = shortcutList[rand() % size];
			current = current->next;
		}

		delete[] shortcutList;
	}

	void Insert(size_t element, int index) {
		mod(--index, size++);

		Node* insert = new Node(element);

		if (!head) {
			head = insert;
			head->next = head;
			return;
		}

		Node* preInsert = head;
		if (index == size - 2) head = insert;

		for (size_t i = 0; i < (size_t)index; i++)
			preInsert = preInsert->next;

		insert->next = preInsert->next;
		preInsert->next = insert;
	}

	void Free() {
		if (!head) return;
		Node* current = head;

		Node* debugHead = head;
		size_t debugSize = size;

		Node* afterCurrent = current->next;
		while (true) {
			delete current;
			current = afterCurrent;
			if (--size == 0) break;
			afterCurrent = current->next;
		}

		head = nullptr;
	}

	size_t Find(size_t element, float p_follow) {
		if (size == 0 || element > size)  return 0;

		if (p_follow < 0 || p_follow >= 1.0f)
			p_follow = (float)rand() / (RAND_MAX + 1);

		size_t result = 0;

		Node* current = head;
		for (size_t i = rand() % size; i > 0; i--)
			current = current->next;

		while (current->value != element) {
			result++;

			if (current->shortcut && (float) rand() / RAND_MAX < p_follow) {
				current = current->shortcut;
			}
			else current = current->next;
		}

		return result;
	}

	size_t All(float p_follow) {
		if (size == 0) return 0;

		if (p_follow < 0 || p_follow >= 1.0f)
			p_follow = (float)rand() / (RAND_MAX + 1);

		size_t result = 0;

		size_t lastFind = size;
		bool status = head->isVisited;


		Node* current = head;
		for (size_t i = rand() % size; i > 0; i--)
			current = current->next;

		while (lastFind != 0) {
			result++;

			if (current->isVisited == status) {
				lastFind--;
				current->isVisited = !status;
			}
			if (current->shortcut && (float)rand() / RAND_MAX < p_follow)
				current = current->shortcut;
			else current = current->next;
		}

		return result;
	}

};

static CircularList g_list;

int Task15() {
	initializer_list<size_t> order;
	if (IsDemo()) order = { 1 , 2 , 3, 3 ,1 , 3 , 2, 3};

	Menu menu("Choose: ", {
		MenuItem("Create new", Create),
		MenuItem("Go through all", All),
		MenuItem("Find", Find) });
	menu.DoMenu(order);
	
	return (int)MenuMode::REPEATE;
}

int Create() {
	int size = rand() % 10000 + 1000;;
	float p_add = (float)rand() / (2 * RAND_MAX + 1) + 0.5f;
	if (IsDemo()) {
		SleepPrint(to_string(size), "Enter size of your list: ");
		SleepPrint(FloatToString(p_add), "Enter probability of having shortcut. In interval [0,1]: ");
	}
	else {
		InputStr(size, "Enter size of your list: ", 1);
		InputStr(p_add, "Enter probability of having shortcut. In interval [0,1]: ", 0.0f, 1.0f);
	}

	g_list.Create(size, p_add);

	cout << "Created" << endl;
	return Pause();
}

int All() {
	float p_follow = (float)rand() / (2 * RAND_MAX + 1) + 0.1f;
	int n = rand() % 60 + 30;
	if (IsDemo()) {
		SleepPrint(FloatToString(p_follow), "Enter probability to pass on shortcut. In interval [0,1]: ");
		SleepPrint(to_string(n), "Enter the number of repetitions: ");
	}
	else {
		InputStr(p_follow, "Enter probability to pass on shortcut. In interval [0,1]: ", 0.0f, 1.0f);
		InputStr(n, "Enter the number of repetitions: ", 1, (int)1e3);
	}
	size_t min, max, total;
	min = max = total = g_list.All(p_follow);

	for (size_t i = 1; i < (size_t)n; i++) {
		cout << i << ", ";
		size_t current = g_list.All(p_follow);
		if (min > current) min = current;
		if (max < current) max = current;
		total += current;
	}

	cout << "\n\tAvarage: " << AddChar(total/n);
	cout << "\n\tMin:     " << AddChar(min);
	cout << "\n\tMax:     " << AddChar(max) << endl;

	return Pause();
}

int Find() {
	int element = rand() % 100 + 1;
	float p_follow = (float)rand() / (2 * RAND_MAX + 1) + 0.1f;
	int n = rand() % 500 + 100;
	if (IsDemo()) {
		SleepPrint(to_string(element), "Enter element for search: ");
		SleepPrint(FloatToString(p_follow), "Enter probability to pass on shortcut. In interval [0,1]: ");
		SleepPrint(to_string(n), "Enter the number of repetitions: ");
	}
	else {
		InputStr(element, "Enter element for search: ", 1);
		InputStr(p_follow, "Enter probability to pass on shortcut. In interval [0,1]: ", 0.0f, 1.0f);
		InputStr(n, "Enter the number of repetitions: ", 1, (int)1e3);
	}
	size_t min, max, total;
	min = max = total = g_list.Find(element ,p_follow);

	for (size_t i = 1; i < (size_t)n; i++) {
		cout << i << ", ";
		size_t current = g_list.Find(element, p_follow);
		if (min > current) min = current;
		if (max < current) max = current;
		total += current;
	}

	cout << "\n\tAvarage: " << AddChar(total / n);
	cout << "\n\tMin:     " << AddChar(min);
	cout << "\n\tMax:     " << AddChar(max) << endl;

	return Pause();
}