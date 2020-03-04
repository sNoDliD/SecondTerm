#include "Header.h"

static vector<Product> g_arr;

static size_t ProductsInShopNow(size_t shopId) {
    size_t result = 0;

    for (auto product : g_arr)
        if (product.id != 0 && product.storeId == shopId)
            result++;

    return result;
}

static size_t GetLastId() {
	return g_arr.size();
}

bool AppendProductVector(Product* product) {
    if (ProductsInShopNow(ShopId()) >= ShopMaxCount()) return false;
    product->id = GetLastId() + 1;
	g_arr.push_back(*product);
    return true;
}

Product* TakeProductVector(size_t indexInVector) {
	if (indexInVector >= g_arr.size()) return nullptr;
	return &g_arr[indexInVector];
}

bool AddVectorRandom(size_t n) {
    Product* newProduct = new Product();

    for (size_t i = 0; i < n; i++) {
        newProduct->Randomaze();
        if (!AppendProductVector(newProduct)) {
            delete newProduct;
            return false;
        }
    }

    delete newProduct;
    return true;
}

bool ModifyVector(size_t id, Product* product) {
    if (id > g_arr.size() || g_arr[id - 1].id == 0) return false;
    if (g_arr[id - 1].storeId != ShopId()) return false;
    g_arr[id - 1] = *product;
    g_arr[id - 1].id = id;

    return true;
}

bool DeleteVector(size_t id) {
    if (id > g_arr.size() || g_arr[id - 1].id == 0) return false;
    if (g_arr[id - 1].storeId != ShopId()) return false;
    if (g_arr[id - 1].id != 0) {
        g_arr[id - 1].id = 0;
        return true;
    }
    return false;
}

size_t ReorganizeVector() {
    size_t now = 0;

    for (size_t i = 0, len = GetLastId(); i < len; i++) 
        if (g_arr[i].id != 0) {
            g_arr[i].id = now + 1;
            g_arr[now++] = g_arr[i];
        }

    for (size_t i = now, len = GetLastId(); i < len; i++)
        g_arr.pop_back();
    return GetLastId();
}

bool FreeVector() {
    for (size_t len = GetLastId(); len > 0; len--)
        g_arr.pop_back();

    return true;
}