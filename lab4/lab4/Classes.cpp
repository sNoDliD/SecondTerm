#include "MainHeader.h"

IntNode::IntNode(int value) : value(value), childs() {}

int IntNode::getValue()
{
	return this->value;
}

void IntNode::addChild(int value)
{
	this->childs.push_back(IntNode(value));
}

vector<int> IntNode::getAllValues()
{
	if (this->childs.empty())
		return vector<int>();

	vector<int> result;

	for (auto& child : this->childs) {
		result.push_back(child.getValue());

		for (auto& value : child.getAllValues()) {
			result.push_back(value);
		}
	}
	return result;
}

void IntNode::print(size_t gapCount)
{
	for (size_t i = 0; i < gapCount; i++) {
		cout << "--";
	}
	cout << "> " << this->getValue() << endl;

	for (auto& i : this->childs) {
		i.print(gapCount + 1);
	}
}

vector<int> IntNode::remove(int value)
{
	if (this->childs.empty())
		return vector<int>();

	vector<int> extra;

	for (size_t i = this->childs.size(); i > 0; i--) {
		auto child = &this->childs[i - 1];
		if (child->getValue() == value) {
			for (auto& valueGet : child->getAllValues()) {
				if (valueGet != value) {
					extra.push_back(valueGet);
				}
			}
			this->childs.erase(this->childs.begin() + i - 1);
		}
		else {
			for (auto& removedValue : child->remove(value) ){
				extra.push_back(removedValue);
			}
		}
	}

	return extra;
}

IntTree::IntTree() : head(nullptr) {}

IntTree::~IntTree()
{
	if (this->head)
		delete this->head;
}

void IntTree::add(int value, float probability)
{
	if (!this->head) {
		this->head = new IntNode(value);
	}
	else {
		IntNode* current = this->head;

		while (true) {
			size_t childsCount = current->childs.size();
			if (childsCount == 0 || (float)rand() / RAND_MAX < probability) {
				current->addChild(value);
				return;
			}

			current = &(current->childs[rand() % childsCount]);
		}
	}
}


void IntTree::print()
{
	if (this->head)
		this->head->print(0);
	else
		cout << "IntTree is empty\n";

}

void IntTree::removeAll(int value, float probability)
{
	if (!this->head)
		return;

	auto all = this->head->remove(value);
	
	if (this->head->getValue() == value) {
		delete this->head;
	}
	for (auto& addValue : all) {
		if (addValue != value) {
			this->add(addValue, probability);
		}
	}
}

BinNode::BinNode(int value) : value(value), left(nullptr), right(nullptr)
{}

BinNode::~BinNode()
{
	if (this->left)
		delete this->left;
	if (this->right)
		delete this->right;
}

void BinNode::add(int value)
{
	if (value < this->value) {
		if (!this->left)
			this->left = new BinNode{ value };
		else
			this->left->add(value);
	}
	else {
		if (!this->right)
			this->right = new BinNode{ value };
		else
			this->right->add(value);
	}
}

BinTree::BinTree() : head(nullptr)
{}

BinTree::~BinTree()
{
	if (this->head)
		delete this->head;
}

void BinTree::add(int value)
{
	if (!this->head)
		this->head = new BinNode{ value };
	else
		this->head->add(value);
}

void BinNode::preorderPrint()
{
	cout << this->value << " ";
	if(this->left)
		this->left->preorderPrint();   
	if(this->right)
		this->right->preorderPrint(); 
}

void BinTree::preorderPrint()
{
	if (this->head)
	{
		this->head->preorderPrint();
	}
	else 
	{
		cout << "BinTree is empty\n";
	}
}
void BinTree::print()
{
	if (this->head) {
		this->head->print(0);
		cout << endl;
	}
	else
		cout << "BinTree is empty\n";
}
void BinNode::print(size_t gapCount)
{
	for (size_t i = 0; i < gapCount; i++) {
		cout << "--";
	}
	cout << "> " << this->value << endl;

	if (this->left)
		this->left->print(gapCount + 1);
	if (this->right)
		this->right->print(gapCount + 1);
}



