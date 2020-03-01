#include "Header.h"

static vector<Product> g_arr;

size_t GetLastIdVector() {
	return g_arr.size();
}

void AppendProductVector(Product* product) {
    product->id = GetLastIdVector() + 1;
	g_arr.push_back(*product);
}

Product* TakeProductVector(size_t indexInVector) {
	if (indexInVector >= g_arr.size())
		return nullptr;
	return &g_arr[indexInVector];
}

void AddVectorRandom(size_t n) {
    Product* newProduct = new Product();

    for (size_t i = 0; i < n; i++) {
        newProduct->Randomaze();
        AppendProductVector(newProduct);
    }

    delete newProduct;
}

bool ModifyVector(size_t id, Product* product) {
    if (id > g_arr.size() || g_arr[id - 1].id == 0)
        return false;
    g_arr[id - 1] = *product;
    g_arr[id - 1].id = id;

    return true;
}

bool DeleteVector(size_t id) {
    if (id > g_arr.size() || g_arr[id - 1].id == 0)
        return false;
    if (g_arr[id - 1].id != 0) {
        cout << '\n' << g_arr[id - 1].ToString();
        g_arr[id - 1].id = 0;
        return true;
    }
    return false;
}

void Reorganize() {
    //Todo: create...
}