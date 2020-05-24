#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Menu.h"
#include <ctime>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;
using std::size_t;


const int INTERACTIVE_MODE = 1;
const int DEMONSTRATION_MODE = 0;


class IntNode
{
public:
	IntNode(int value);

	int getValue();
	vector<IntNode> childs;

	void addChild(int value);
	void print(size_t gapCount = 0);
	vector<int> remove(int value);

private:
	vector<int> getAllValues();
	int value;
};


class IntTree
{
public:
	IntTree();
	~IntTree();
	void add(int value, float probability);
	void print();
	void removeAll(int value, float probability);

private:
	IntNode* head;
};

struct BinNode
{
	int value;
	BinNode* left;
	BinNode* right;

	BinNode(int value);
	~BinNode();
	void add(int value);
	void preorderPrint();
	void print(size_t gapCount);
};
class BinTree
{
public:
	BinTree();
	~BinTree();

	void add(int value);
	void print();
	void preorderPrint();

private:
	BinNode* head;
};

void EnterPoint();

template <typename T>
T input(int mode, string preMessage, T minValue, T maxValue) {
	T value = maxValue;
	if (maxValue < minValue) {
		maxValue = minValue;
		minValue = value;
	}

	cout << preMessage;
	while (true) {
		if (mode == INTERACTIVE_MODE) {
			cin >> value;
			while (cin.fail() || cin.bad())
			{
				cin.clear();
				cin.ignore(INT64_MAX, '\n');
				cout << "Incorrect input. Try again: ";
				cin >> value;
			}
			cin.ignore(INT64_MAX, '\n');
		}
			
		else {
			Sleep(300);
			value = T((double)rand() / RAND_MAX * (maxValue - minValue) + minValue);
			cout << value << endl;
			Sleep(1000);
		}

		if (value <= maxValue && value >= minValue)
			break;
		cout << "Value should be [" << minValue << ", " << maxValue << "]\n";
	}
	return value;
}


static int sleep(int mode) {
	if (mode == INTERACTIVE_MODE)
		system("pause");
	else
		Sleep(700);

	return int(MenuMode::REPEATE);
}
