#pragma once

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;
using std::size_t;

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

	void add(int value, float probability);
	void print();
	void removeAll(int value, float probability);

private:
	bool isEmpty;
	IntNode head;
};

class BinTree
{
public:
	BinTree();
	~BinTree();

private:

};

class CatalogsTree
{
public:
	CatalogsTree();
	~CatalogsTree();

private:

};

void EnterPoint();