#include "Header.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::streampos;

void SetLastIdTxt();

static string g_path;
static size_t g_lastId = 0;

static size_t g_lastTakeId = 0;
static streampos g_lastTakeBytes = 0;

void CreatePathTxt(const char* txtBase) {
    g_path = string(g_pathToDataBases);

    g_path.append(txtBase);
    g_path.append(".txt");

    SetLastIdTxt();
}

void SetLastIdTxt() {
    ofstream out(g_path, std::iostream::app);
    out.close();

    ifstream in(g_path);
    short enterCounter = 0, i = -1;
    char c = '\0';
    while (true){
        in.seekg(i--, in.end);
        in.get(c);
        if (c == '\n')
            enterCounter++;
        if (in.fail()) {
            in.close();
            in.open(g_path);
            if (enterCounter == 1 * 2) {
                i += 2;
                in.seekg(i, in.end);
                in >> g_lastId;
                break;
            }
            if (i < -10) {
                g_lastId = 0;
                break;
            }
            continue;
        }
        if (enterCounter == 2 * 2) {    //why it read '\n' twice...?
            in >> g_lastId;
            break;
        }
    }
    in.close();
}

static size_t GetLastId(bool increase = false) {
    if (increase) g_lastId++;
    return g_lastId;
}

bool AppendProductTxt(ProductString* product) {
    ofstream out(g_path, std::iostream::app); 
    if (!out.is_open()) throw - 1;
    if (GetLastId() >= ShopMaxCount()) return false;
    product->id = GetLastId(true);
    out << *product;
    out.close();
    return true;
}

ProductString* TakeProductTxt(size_t indexInFile) {
    ifstream in;
    in.open(g_path);
    if (!in.is_open())
        return nullptr;
    ProductString* product = new ProductString();
    size_t i = 0;
    if (indexInFile > g_lastTakeId - 1) {
        i = g_lastTakeId;
        in.seekg(g_lastTakeBytes, in.beg);
    }
    for (; i <= indexInFile; i++) {
        in >> *product;
        if (in.eof()) {
            delete product;
            product = nullptr; 
            break;
        }
    }
    if (!in.eof()) {
        g_lastTakeId = indexInFile + 1;
        g_lastTakeBytes = in.tellg();
    }
    in.close();
    return product;
}

bool AddTxtRandom(size_t n) {
    ofstream out(g_path, std::iostream::app);
    if (!out.is_open()) throw - 1;
	ProductString* newProduct = new ProductString();

    for (size_t i = 0; i < n; i++) {
        newProduct->Randomaze();
        if (GetLastId() >= ShopMaxCount()){
            delete newProduct;
            out.close();
            return false;
        }
        newProduct->id = GetLastId(true);
        out << *newProduct;
    }

	delete newProduct;
    out.close();
    return true;
}

static void CopyFileTxt(const char* path, const char* newPath) {
    ifstream infile(path);
    ofstream outfile(newPath);
    char c;
    while (true) {
        infile.get(c);
        if (infile.eof())
            break;
        outfile.put(c);
    }
    outfile.close();
    infile.close();
}

bool ModifyTxt(size_t id, ProductString* productModify) {
    if (id == 0 || id > g_lastId)
        return false;
    bool result = false;

    string pathOld = g_path;
    string newPath = pathOld.erase(g_path.length() - 4) + "(clone).txt";
    CopyFileTxt(g_path.c_str(), newPath.c_str());

    ofstream out(g_path);
    ifstream in(newPath);
    g_lastId = g_lastTakeId = 0;
    g_lastTakeBytes = 0;
    ProductString* product = new ProductString();

    while (true){
        product->id = 0;
        in >> *product;
        if (product->id == 0) break;
        if (product->id == id) {
            result = true;
            if (productModify->id != 0) {
                productModify->id = ++g_lastId;
                out << *productModify;
            }
        }
        else {
            product->id = ++g_lastId;
            out << *product;
        }
    }

    delete product;
    in.close();
    out.close();
    remove(newPath.c_str());
    return result;
}

bool DeleteTxt(size_t id) {
    ProductString* product = new ProductString;
    bool result = ModifyTxt(id, product);
    delete product;

    return result;
}

bool FreeShopTxt(size_t shopId) {
    size_t len = strlen(g_pathToDataBases) + strlen(to_string(shopId).c_str()) + 5;
    char* path = new char[len];
    strcpy_s(path, len, g_pathToDataBases);
    strcat_s(path, len, to_string(shopId).c_str());
    strcat_s(path, len, ".txt");

    int resust = remove(path);
    delete[] path;
    if (resust == 0) return true;
    return false;
}