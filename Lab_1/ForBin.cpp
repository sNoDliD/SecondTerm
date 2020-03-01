#include "Header.h"
#include <cstring>

void SetLastIdBin();
void SetLastIdStore();

static char* g_path = nullptr;
static char* g_pathStore = nullptr;
static size_t g_lastIdStore = 0;
static size_t g_lastIdProduct = 0;

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
    if (g_path) 
        delete[] g_path;
    g_path = new char[len];
    strcpy_s(g_path, len, pathToDataBases);
    strcat_s(g_path, len, binBase);
    strcat_s(g_path, len, ".bin");

    SetLastIdBin();
}

void DeletePathBin() {
    delete[] g_path;
    delete[] g_pathStore;
}

void SetLastIdBin() {
    FILE* file;
    fopen_s(&file, g_path, "ab");
    if (file != 0)
        fclose(file);
    else
        throw - 1;

    size_t len = strlen(g_path) + strlen("(clone)") + 1;
    char* newPath = new char[len];
    strcpy_s(newPath, len, g_path);
    newPath[strlen(g_path) - 4] = '\0';
    strcat_s(newPath, len, "(clone).bin");
    CopyFileBin(g_path, newPath);

    FILE* outfile;
    fopen_s(&outfile, g_path, "wb");
    FILE* infile;
    fopen_s(&infile, newPath, "rb");

    g_lastIdProduct = 0;
    if (infile != 0 && outfile != 0) {
        Product* temp = new Product;;
        while (true) {
            fread_s(temp, sizeof(Product), sizeof(Product),1, infile);
           
            if (feof(infile))
                break;
            if (temp->id != 0) {
                temp->id = ++g_lastIdProduct;
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
    return ++g_lastIdProduct;
}

void AppendProductBin(Product* product) {
    FILE* file;
    fopen_s(&file, g_path, "ab");
    if (file != 0) {
        product->id = GetLastIdBin();
        fwrite(product, sizeof(Product), 1, file);
        fclose(file);
    }
    else
        throw -1;
}

Product* TakeProductBin(size_t indexInFile) {
    if (g_lastIdProduct == 0) return nullptr;

    Product* product = new Product();
    FILE* file;
    fopen_s(&file, g_path, "rb"); 

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

void AddBinRandom(size_t n) {
    Product* newProduct = new Product();

    for (size_t i = 0; i < n; i++) {
        newProduct->Randomaze();
        AppendProductBin(newProduct);
    }

    delete newProduct;
}

bool ModifyBin(size_t id, Product* product) {
    if (id == 0 || id > g_lastIdProduct) return false;
    bool result = false;

    FILE* file;
    fopen_s(&file, g_path, "r+b");
    if(file != 0) {
        Product* temp = new Product;
        fseek(file, (id - 1) * sizeof(Product), SEEK_SET);
        fread(temp, sizeof(Product), 1, file);
        fseek(file, 0 - sizeof(Product), SEEK_CUR);
        if (temp->id != 0) {
            product->id = id;
            fwrite(product, sizeof(Product), 1, file);
            result = true;
        }
        delete temp;
        fclose(file);
    }
    else throw - 1;

    return result;
}

bool DeleteBin(size_t id) {
    Product* product = new Product;
    bool result = ModifyBin(id, product);
    delete product;

    return result;
}



void CreatePathStore() {
    size_t len = strlen(storeBase) + 1;
    g_pathStore = new char[len];
    strcpy_s(g_pathStore, len, storeBase);

    SetLastIdStore();
}

void SetLastIdStore() {
    Store* s = new Store();
    FILE* file;
    fopen_s(&file, g_pathStore, "rb");
    if (file == 0) {
        fopen_s(&file, g_pathStore, "wb");
        g_lastIdStore = 0;
    }
    else {
        fseek(file, 0 - sizeof(Store), SEEK_END);
        fread(s, sizeof(Store), 1, file);
        g_lastIdStore = s->id; //set default = 0
    }
    if (file != 0)
        fclose(file);
    delete s;
}

size_t GetLastIdStore() {
    return ++g_lastIdStore;
}

void AppendStore(Store* store) {
    FILE* file;
    fopen_s(&file, g_pathStore, "ab");
    if (file != 0) {
        store->id = GetLastIdStore();
        fwrite(store, sizeof(Store), 1, file);
        fclose(file);
    }
    else
        throw - 1;
}

Store* TakeStore(size_t indexInFile) {
    if (g_lastIdStore == 0) return nullptr;

    Store* store = new Store();
    FILE* file;
    fopen_s(&file, g_pathStore, "rb");

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
