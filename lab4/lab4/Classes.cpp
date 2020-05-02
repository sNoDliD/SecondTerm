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
		return vector<int>({this->getValue()});

	vector<int> result;

	for (auto& child : this->childs) {
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
			auto x = child->remove(value);
		}
	}
	//for (auto& child : this->childs) {
	//	if (child.getValue() == value) {
	//		for (auto& valueGet : child.getAllValues()) {
	//			if (valueGet != value) {
	//				extra.push_back(valueGet);
	//			}
	//		}
	//		//
	//	}
	//	else {
	//		auto x = child.remove(value);
	//	}
	//}

	return extra;
}

IntTree::IntTree() : isEmpty(true), head(0) {}

void IntTree::add(int value, float probability)
{
	if (this->isEmpty) {
		this->head = IntNode(value);
		this->isEmpty = false;
	}
	else {
		IntNode* current = &this->head;

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
	this->head.print(0);
}

void IntTree::removeAll(int value, float probability)
{
	if (this->head.getValue() == value) {
		this->isEmpty = true;
	}

	for (auto& addValue : this->head.remove(value)) {
		if (addValue != value) {
			this->add(addValue, probability);
		}
	}
}