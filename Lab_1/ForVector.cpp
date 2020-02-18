#include "Header.h"
#include <vector> 

using std::vector;

vector<Product> arr;

int GetLastIdVector() {
	return arr.size();
}

void AppendProductVector(Product* product) {
	arr.push_back(*product);
}

Product* TakeProductVector(size_t indexInVector) {
	if (indexInVector >= arr.size())
		return nullptr;
	return &arr[indexInVector];
}