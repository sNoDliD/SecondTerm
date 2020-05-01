#pragma once

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::vector;

class IntNode
{
public:
	IntNode();
	~IntNode();
	int getValue();
private:
	int value;
	vector<IntNode> childs;
};


class IntTree
{
public:
	IntTree(float probability = 0.5f);
	~IntTree();
	void add(int value);
	void print();
	void removeAll(int value);

private:
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