#include "Header.h"
#include <cmath>
#include <iostream>
#include <string>


template <typename T>
class OnVector {
	vector<T> arr;

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

public:

	//T should have method: std::string to_string(T)
	std::string ToString(std::string delimiter = " ", bool numerated = false) {
		std::string result = "";

		if (arr.size() == 0) return "List is empty";

		size_t numerator = 0;
		for (auto now : arr) {
			if (numerated) result += to_string(numerator++) + ": ";
			result += to_string(now) + delimiter;
		}

		for (size_t i = delimiter.size(); i > 0; i--)
			result.pop_back();

		return result;
	}

	OnVector() {
		arr = vector<T>();
	}

	void CreateEmpty() {
		arr = vector<T>();
	}

	void Insert(T element, int index) {
		mod(index, arr.size());

		arr.insert(arr.begin() + index, element);
	}

	T Remove(int index) {
		if (arr.size() == 0) throw "Empty list...";
		mod(index, arr.size());

		T result = arr[index];
		arr.erase(arr.begin() + index, arr.begin() + index + 1);

		return result;
	}

	T Get(int index) {
		if (arr.size() == 0) throw "Empty list...";
		mod(index, arr.size());

		return arr[index];
	}

	void Set(T value, int index) {
		if (arr.size() == 0) throw "Empty list...";
		mod(index, arr.size());

		arr[index] = value;
	}

	template <typename... Ttail>
	OnVector<T> CreateNew(bool(*Condition)(T, Ttail...), Ttail... tail) {
		OnVector<T> result;
		for (size_t len = arr.size(); len > 0; --len) {
			if (Condition(arr[len - 1], tail...))
				result.Insert(arr[len - 1], 0);
		}
		return result;
	}
};

static OnVector<int> g_list;

static int Generate();
static int Add();
static int Choose();
static int Show();

static bool Negative(int element);
static bool More(int element, int compare);
static bool Odd(int element);


int Task7() {
	initializer_list<size_t> order;
	if (IsDemo()) order = { 1 , 2 , 4, 3, 1, 3, 3, 4 };

	Menu menu("Select:", {
		MenuItem("Generate random list", Generate),
		MenuItem("Add element", Add),
		MenuItem("Choose condition", Choose),
		MenuItem("Show all", Show) });
	menu.DoMenu(order);

	return (int)MenuMode::REPEATE;
}

int Generate() {
	g_list.CreateEmpty();

	for (size_t i = rand() % 30; i > 0; i--)
		g_list.Insert(rand() % 100 - 50, 1);

	return Show();
}

int Add() {
	int element = rand() % 100 - 50, index = rand() % 100 - 50;
	if (IsDemo()) {
		SleepPrint(to_string(element), "Enter element: ");
		SleepPrint(to_string(index), "Enter index: ");
	}
	else {
		InputStr(element, "Enter element: ");
		InputStr(index, "Enter index: ");
	}

	g_list.Insert(element, index);

	return Show();
}

static void CreateNewList(int result) {
	OnVector<int> newList;

	if (result == 1) {
		int compare = rand() % 50 - 25;
		if (IsDemo())
			SleepPrint(to_string(compare), "More that what: ");
		else 
			InputStr(compare, "More that what: ");
		newList = g_list.CreateNew(More, compare);
	}
	else if (result == 2)
		newList = g_list.CreateNew(Odd);
	else if (result == 3)
		newList = g_list.CreateNew(Negative);

	Menu menu("New list: " + newList.ToString(", "), {
		MenuItem("Take it", nullptr, 1),
		MenuItem("Skip", nullptr, 2) });
	result = menu.DoMenu({ (size_t)IsDemo() * (rand() % 2 + 1) });

	if (result == 1) g_list = newList;
}

int Choose() {
	Menu menu("Select:", {
		MenuItem("More then", nullptr, 1),
		MenuItem("Odd", nullptr, 2),
		MenuItem("Negative", nullptr, 3) });
	int result = menu.DoMenu({ (size_t)IsDemo() * (rand() % 3 + 1) });

	if (result != (int)MenuMode::EXIT)
		CreateNewList(result);

	return (int)MenuMode::REPEATE;
}

int Show() {
	cout << "Your list: " << g_list.ToString(", ") << endl;

	if (IsDemo()) Sleep(pauseTime);
	else system("pause");

	return (int)MenuMode::REPEATE;
}

bool Negative(int element) {
	return element < 0;
}

bool More(int element, int compare) {
	return element > compare;
}

bool Odd(int element) {
	return element % 2 != 0;
}