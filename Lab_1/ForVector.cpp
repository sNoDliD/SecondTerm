#include "Header.h"
#include <vector> 

using std::vector;

vector<Product> arr;

size_t GetLastIdVector() {
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

void AddVectorRandom(size_t n) {
    Product* newProduct = new Product();

    for (size_t i = 0; i < n; i++) {
        newProduct->Randomaze(GetLastIdVector() + 1);
        AppendProductVector(newProduct);
    }

    delete newProduct;
}

bool ModifyVector(size_t id, Product* product) {
    if (id > arr.size() || arr[id - 1].id == 0)
        return false;
    arr[id - 1] = *product;
    arr[id - 1].id = id;

    return true;
}

bool DeleteVector(size_t id) {
    if (id > arr.size() || arr[id - 1].id == 0)
        return false;
    if (arr[id - 1].id != 0) {
        cout << '\n' << arr[id - 1].ToString();
        arr[id - 1].id = 0;
        return true;
    }
    return false;
}