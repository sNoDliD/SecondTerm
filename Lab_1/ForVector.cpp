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

void AddVectorRandom(int n) {
    Product* newProduct = new Product();

    for (int i = 0; i < n; i++) {
        newProduct->Randomaze(GetLastIdVector() + 1);
        AppendProductVector(newProduct);
    }

    delete newProduct;
}