#ifndef MY_TREE_LIST_IN_ONE_HEADER
#define MY_TREE_LIST_IN_ONE_HEADER

#include <cmath>
#include <iostream>

//number will be >= 0
static size_t mod(int& number, size_t circle) {
	if (circle == 0) {
		number = 0;
		return 0;
	}
	else {
		number = fmod(number, circle);
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

	void CreateEmpty(size_t size) {
		if (arr) delete[] arr;
		last = 0;
		this->size = size;
		arr = new T[arr];
	}

	void Insert(T element, int index) {
		if (last >= size) throw "Over than size...";
		mod(index, last);

		for (size_t i = last++; i > index; i--)
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
	void Print() {
		for (auto a : arr) {
			std::cout << a << " ";
		}
		std::cout << std::endl;
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
		Print();
	}

	T Remove(int index) {
		if (arr.size() == 0) throw "Empty list...";
		mod(index, arr.size());

		auto result = arr.erase(arr.begin() + index, arr.begin() + index + 1);
		Print();
		return result[0];
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

#endif // !MY_TREE_LIST_IN_ONE_HEADER

