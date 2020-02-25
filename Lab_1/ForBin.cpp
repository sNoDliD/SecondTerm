#include "Header.h"
#include <cstring>

char* path = nullptr;
char* pathStore = nullptr;
int lastIdStore = 0;
int lastIdProduct = 0;

void CreatePathBin(const char* binBase) {
    size_t len = strlen(pathToDataBases) + strlen(binBase) + 5;
    if (path) 
        delete[] path;
    path = new char[len];
    strcpy_s(path, len, pathToDataBases);
    strcat_s(path, len, binBase);
    strcat_s(path, len, ".bin");
}

void CreatePathStore() {
    size_t len = strlen(storeBase) + 1;
    pathStore = new char[len];
    strcpy_s(pathStore, len, storeBase);
}

void DeletePathBin() {
    delete[] path;
    delete[] pathStore;
}

void SetLastIdBin() {
    Product* product = new Product();
    FILE* file;
    fopen_s(&file, path , "rb");
    if (file == 0) {
        fopen_s(&file, path, "ab");
        lastIdProduct = 0;
    }
    else {
        fseek(file, 0 - sizeof(Product), SEEK_END);
        fread(product, sizeof(Product), 1, file);
        lastIdProduct = product->id; //set default = 0
    }
    if (file != 0)
        fclose(file);
    delete product;
}

int GetLastIdBin() {
    return ++lastIdProduct;
}

void SetLastIdStore() {
    Store* s = new Store();
    FILE* file;
    fopen_s(&file, pathStore, "rb");
    if (file == 0) {
        fopen_s(&file, pathStore, "wb");
        lastIdStore = 0;
    }
    else {
        fseek(file, 0 - sizeof(Store), SEEK_END);
        fread(s, sizeof(Store), 1, file);
        lastIdStore = s->id; //set default = 0
    }
    if (file != 0)
        fclose(file);
    delete s;
}

int GetLastIdStore() {
    return ++lastIdStore;
}

void AppendProductBin(Product* product) {
    FILE* file;
    fopen_s(&file, path, "ab");
    if (file != 0) {
        fwrite(product, sizeof(Product), 1, file);
        fclose(file);
    }
    else
        throw -1;
}

Product* TakeProductBin(int indexInFile) {
    if (lastIdProduct == 0) return nullptr;

    Product* product = new Product();
    FILE* file;
    fopen_s(&file, path, "rb"); 

    if (file != 0) {
        fseek(file, indexInFile * sizeof(Product), SEEK_SET);
        fread(product, sizeof(Product), 1, file);
        if (feof(file)) {
            delete product;
            product = nullptr;
        }
        fclose(file);
    }
    else
        throw - 1;
    return product;
}

void AppendStore(Store* store) {
    FILE* file;
    fopen_s(&file, pathStore, "ab");
    if (file != 0) {
        fwrite(store, sizeof(Store), 1, file);
        fclose(file);
    }
    else
        throw -1;
}

Store* TakeStore(int indexInFile) {
    if (lastIdStore == 0) return nullptr;

    Store* store = new Store();
    FILE* file;
    fopen_s(&file, pathStore, "rb"); 

    if (file != 0) {
        fseek(file, indexInFile * sizeof(Store), SEEK_SET);
        fread(store, sizeof(Store), 1, file);
        if (feof(file)) {
            delete store;
            store = nullptr;
        }
        fclose(file);
    }
    else
        throw - 1;
    return store;
}

void modify(Store* a, int id) {
    FILE* file;
    fopen_s(&file, pathStore, "r+b");

    if (file != 0) {
        fseek(file, (id - 1) * sizeof(Store), SEEK_SET);
        fwrite(new Store(), sizeof(Store), 1, file);
        fclose(file);
    }
    else
        throw - 1;
}

void AddBinRandom(int n) {
    Product* newProduct = new Product();

    for (int i = 0; i < n; i++) {
        newProduct->Randomaze(GetLastIdBin());
        AppendProductBin(newProduct);
    }

    delete newProduct;
}