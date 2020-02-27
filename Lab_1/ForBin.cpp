#include "Header.h"
#include <cstring>

char* path = nullptr;
char* pathStore = nullptr;
size_t lastIdStore = 0;
size_t lastIdProduct = 0;

void CopyFileBin(const char* path, const char* newPath) {
    FILE* infile;
    fopen_s(&infile, path, "rb");
    FILE* outfile;
    fopen_s(&outfile, newPath, "wb");
    char c;
    if (infile != 0 && outfile != 0) {
        while (true) {
            fread_s(&c, 1, sizeof(char), 1, infile);
            if (feof(infile))
                break;
            fwrite(&c, sizeof(char), 1, outfile);
        }
        fclose(infile);
        fclose(outfile);
    }
    else
        throw - 1;
}

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
    FILE* file;
    fopen_s(&file, path, "ab");
    if (file != 0)
        fclose(file);
    else
        throw - 1;

    size_t len = strlen(path) + strlen("(clone)") + 1;
    char* newPath = new char[len];
    strcpy_s(newPath, len, path);
    newPath[strlen(path) - 4] = '\0';
    strcat_s(newPath, len, "(clone).bin");
    CopyFileBin(path, newPath);

    FILE* outfile;
    fopen_s(&outfile, path, "wb");
    FILE* infile;
    fopen_s(&infile, newPath, "rb");

    lastIdProduct = 0;
    if (infile != 0 && outfile != 0) {
        Product* temp = new Product;;
        while (true) {
            fread_s(temp, sizeof(Product), sizeof(Product),1, infile);
           
            if (feof(infile))
                break;
            if (temp->id != 0) {
                temp->id = ++lastIdProduct;
                fwrite(temp, sizeof(Product), 1, outfile);
            }
        }
        if (temp != nullptr)
            delete temp;
        fclose(infile);
        fclose(outfile);
    }
    else
        throw - 1;
    remove(newPath);
    delete[] newPath;
}

size_t GetLastIdBin() {
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

size_t GetLastIdStore() {
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

Product* TakeProductBin(size_t indexInFile) {
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

Store* TakeStore(size_t indexInFile) {
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

void AddBinRandom(size_t n) {
    Product* newProduct = new Product();

    for (size_t i = 0; i < n; i++) {
        newProduct->Randomaze(GetLastIdBin());
        AppendProductBin(newProduct);
    }

    delete newProduct;
}

bool ModifyBin(size_t id, Product* product) {
    if (id == 0 || id > lastIdProduct)
        return false;
    bool result = false;

    FILE* file;
    fopen_s(&file, path, "r+b");
    if(file != 0) {
        Product* temp = new Product;
        fseek(file, (id - 1) * sizeof(Product), SEEK_SET);
        fread(temp, sizeof(Product), 1, file);
        fseek(file, 0 - sizeof(Product), SEEK_CUR);
        if (temp->id != 0) {
            fwrite(product, sizeof(Product), 1, file);
            cout << '\n' << temp->ToString();
            result = true;
        }
        delete temp;
        fclose(file);
    }
    else
        throw - 1;

    return result;
}

bool DeleteBin(size_t id) {
    Product* product = new Product;
    bool result = ModifyBin(id, product);
    delete product;

    return result;
}