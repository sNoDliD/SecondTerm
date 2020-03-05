#ifndef MY_TREE_LIST_IN_ONE_HEADER
#define MY_TREE_LIST_IN_ONE_HEADER

#include <cmath>
#include <iostream>
#include <string>

//number will be >= 0
static size_t mod(int& number, size_t circle) {
	if (circle == 0) {
		number = 0;
		return 0;
	}
	else {
		number = (int) fmod(number, circle);
		if (number < 0) number += circle;
		return number;
	}
}

template <typename T>
class FixedSize {
	T* arr = nullptr;
	size_t last = 0;
	size_t size;
public:
	FixedSize(size_t size = 0) :size(size) {
		arr = new T[size];
	}

	~FixedSize() {
		if(arr) delete[] arr;
	}

	//T should have method: std::string to_string(T)
	std::string ToString(std::string delimiter = " ") {
		std::string result = "";

		if (size == 0) return "List is empty";

		for (size_t i = 0; i < last; i++)
			result += to_string(arr[i]) + delimiter;

		for (size_t i = delimiter.size(); i > 0; i--)
			result.pop_back();

		return result;
	}

	void CreateEmpty(size_t size) {
		if (arr) delete[] arr;
		last = 0;
		this->size = size;
		arr = new T[size];
	}

	void Insert(T element, int index) {
		if (last >= size) throw "Over than size...";
		mod(index, last);

		for (size_t i = last++; i > (size_t)index; i--)
			arr[i] = arr[i - 1];

		arr[index] = element;
	}

	T Remove(int index) {
		if (last == 0) throw "Empty list...";
		mod(index, last--);

		T result = arr[index];
		for (size_t i = index; i < last; i++)
			arr[i] = arr[i + 1];

		return result;
	}

	T Get(int index) {
		if (last == 0) throw "Empty list...";
		mod(index, last);

		return arr[index];
	}

	void Set(T value, int index) {
		if (last == 0) throw "Empty list...";
		mod(index, last);

		arr[index] = value;
	}
};

template <typename T>
class OnVector {
	vector<T> arr;
public:

	//T should have method: std::string to_string(T)
	std::string ToString(std::string delimiter = " ") {
		std::string result = "";

		if (arr.size() == 0) return "List is empty";

		for (auto now : arr)
			result += to_string(now) + delimiter;

		for (size_t i = delimiter.size(); i > 0; i--)
			result.pop_back();

		return result;
	}

	OnVector() {
		arr = vector<T>();
	}

	void CreateEmpty(size_t size = 0) {
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
};


template <typename T>
class CircularList;

template <typename T>
class Node{
private:
	T value;
	Node<T>* next;

public:
	Node(T value, Node<T>* next = nullptr) : value(value), next(next) {}

	friend class CircularList<T>;
};

template <typename T>
class CircularList {
private:
	size_t size;
	Node<T>* head;
public:

	CircularList() : size(0), head(nullptr) {}

	~CircularList() {
		Free();
	}

	//T should have method: std::string to_string(T)
	std::string ToString(std::string delimiter = " ") {
		std::string result = "";
		Node<T>* now = head;

		if (size == 0) return "List is empty";

		do {
			result += to_string(now->value) + delimiter;
			now = now->next;
		} while (now != head);

		for (size_t i = delimiter.size(); i > 0; i--)
			result.pop_back();

		return result;
	}

	void CreateEmpty(size_t size = 0) {
		Free();
		this->size = 0;
		head = nullptr;
	}

	void Insert(T element, int index) {
		mod(--index, size++);

		Node<T>* insert = new Node<T>(element);
		if (!head) {
			head = insert;
			head->next = head;
			return;
		}

		Node<T>* preInsert = head;
		if (index == size - 2) head = insert;

		for (size_t i = 0; i < (size_t) index; i++)
			preInsert = preInsert->next;

		insert->next = preInsert->next;
		preInsert->next = insert;
	}

	T Remove(int index) {
		if (size == 0) throw "Empty list...";
		mod(--index, size);

		T result = Get(index + 1);

		Node<T>* preRemove = head;
		for (size_t i = 0; i < (size_t)index; i++)
			preRemove = preRemove->next;

		Node<T>* afterRemove = preRemove->next->next;
		delete preRemove->next;
		preRemove->next = afterRemove;

		size--;

		return result;
	}

	T Get(int index) {
		if (size == 0) throw "Empty list...";
		mod(index, size);

		Node<T>* current = head;
		for (size_t i = 0; i < (size_t)index; i++)
			current = current->next;

		return current->value;
	}

	void Set(T value, int index) {
		if (size == 0) throw "Empty list...";
		mod(index, size);

		Node<T>* current = head;
		for (size_t i = 0; i < (size_t)index; i++)
			current = current->next;

		current->value = value;
	}

	void Free() {
		if (!head) return;
		Node<T>* current = head;
		Node<T>* afterCurrent = current->next;
		do {
			delete current;
			current = afterCurrent;
			afterCurrent = current->next;
		} while (--size > 0);
		head = nullptr;
	}

};

#endif // !MY_TREE_LIST_IN_ONE_HEADER

