#include "Header.h"
#include <cstring>

void SetLastIdBin();
void SetLastIdStore();

static char* g_path = nullptr;
static char* g_pathStore = nullptr;
static size_t g_lastIdStore = 0;
static size_t g_lastIdProduct = 0;

static size_t GetLastId(bool increase = false) {
    if (increase) g_lastIdProduct++;
    return g_lastIdProduct;
}

static void OpenToWork(FILE** file, const char* path) {
    fopen_s(file, path, "ab");
    if (*file == 0) throw - 1;
    fclose(*file);
    fopen_s(file, path, "r+b");
    if (file == 0) throw - 1;
}

void CreatePathBin(const char* binBase) {
    size_t len = strlen(g_pathToDataBases) + strlen(binBase) + 5;
    if (g_path) 
        delete[] g_path;
    g_path = new char[len];
    strcpy_s(g_path, len, g_pathToDataBases);
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
    OpenToWork(&file, g_path);

    size_t pos = 0;
    g_lastIdProduct = 0;
    Product* product = new Product();

    while (true){
        fread_s(product, sizeof(Product), sizeof(Product), 1, file);
        if (feof(file)) break;
        pos++;
        if (product->id != 0) {
            GetLastId(true);
            long delta = pos - GetLastId();
            if (delta > 0) {
                product->id = GetLastId();
                fseek(file, 0 - (delta+1)*sizeof(Product), SEEK_CUR);
                fwrite(product, sizeof(Product), 1, file);
                fseek(file, delta*sizeof(Product), SEEK_CUR);
            }
        }
    }
    fclose(file);
}

bool AppendProductBin(Product* product) {
    if (GetLastId() + 1 > ShopMaxCount()) return false;
    FILE* file;
    OpenToWork(&file, g_path);
    fseek(file, GetLastId()*sizeof(Product), SEEK_SET);

    product->id = GetLastId(true);
    fwrite(product, sizeof(Product), 1, file);
    fclose(file);
    return true;
}

Product* TakeProductBin(size_t indexInFile) {
    if (indexInFile >= GetLastId()) return nullptr;

    Product* product = new Product();
    FILE* file;
    OpenToWork(&file, g_path);

    fseek(file, indexInFile * sizeof(Product), SEEK_SET);
    fread(product, sizeof(Product), 1, file);
    if (feof(file)) {
        delete product;
        product = nullptr;
    }

    fclose(file);
    return product;
}

bool AddBinRandom(size_t n) {
    Product* newProduct = new Product();
    FILE* file;
    OpenToWork(&file, g_path);
    fseek(file, GetLastId() * sizeof(Product), SEEK_SET);

    for (size_t i = 0; i < n; i++) {
        newProduct->Randomaze();
        if (GetLastId() + 1 > ShopMaxCount()) {
            delete newProduct;
            fclose(file);
            return false;
        }
        newProduct->id = GetLastId(true);
        fwrite(newProduct, sizeof(Product), 1, file);
    }

    delete newProduct;
    fclose(file);
    return true;
}

bool ModifyBin(size_t id, Product* product) {
    if (id == 0 || id > GetLastId()) return false;
    bool result = false;

    FILE* file;
    OpenToWork(&file, g_path);
    Product* temp = new Product;

    fseek(file, (id - 1) * sizeof(Product), SEEK_SET);
    fread(temp, sizeof(Product), 1, file);
    fseek(file, 0 - sizeof(Product), SEEK_CUR);

    if (temp->id != 0) {
        if (product->id != 0) product->id = id;
        fwrite(product, sizeof(Product), 1, file);
        result = true;
    }
    delete temp;
    fclose(file);
    return result;
}

bool DeleteBin(size_t id) {
    Product* product = new Product;
    bool result = ModifyBin(id, product);
    delete product;

    return result;
}

bool FreeShopBin(size_t shopId) {
    size_t len = strlen(g_pathToDataBases) + strlen(to_string(shopId).c_str()) + 5;
    char* path = new char[len];
    strcpy_s(path, len, g_pathToDataBases);
    strcat_s(path, len, to_string(shopId).c_str());
    strcat_s(path, len, ".bin");

    int resust = remove(path);
    delete[] path;
    if (resust == 0) return true;
    return false;
}


static size_t GetLastIdStore(bool increase = false) {
    if (increase) g_lastIdStore++;
    return g_lastIdStore;
}

void CreatePathStore(const char* storeBase) {
    size_t len = strlen(storeBase) + 1;
    if (g_pathStore) delete[] g_pathStore;
    g_pathStore = new char[len];
    strcpy_s(g_pathStore, len, storeBase);

    SetLastIdStore();
}

void SetLastIdStore() {
    FILE* file;
    OpenToWork(&file, g_pathStore);
    Store* s = new Store();

    fseek(file, 0 - sizeof(Store), SEEK_END);
    fread(s, sizeof(Store), 1, file);
    g_lastIdStore = s->id; //set default = 0

    fclose(file);
    delete s;
}

void AppendStore(Store* store) {
    FILE* file;
    fopen_s(&file, g_pathStore, "ab");
    if (file == 0) throw - 1;

    store->id = GetLastIdStore(true);
    fwrite(store, sizeof(Store), 1, file);
    fclose(file);

}

Store* TakeStore(size_t indexInFile) {
    if (indexInFile >= GetLastIdStore()) return nullptr;

    Store* store = new Store();
    FILE* file;
    OpenToWork(&file, g_pathStore);

    fseek(file, indexInFile * sizeof(Store), SEEK_SET);
    fread_s(store, sizeof(Store), sizeof(Store), 1, file);
    if (feof(file)) {
        delete store;
        store = nullptr;
    }

    fclose(file);
    return store;
}

bool FreeShops(const char* pathStore, bool reCreate) {
    int resust = remove(pathStore);
    if (resust == 0 && reCreate) {
        CreatePathStore(pathStore);
        return true;
    }
    return false;
}