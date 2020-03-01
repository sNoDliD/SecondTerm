#include "Header.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::fstream;
using std::streampos;

void SetLastIdTxt();

static string g_path;
static size_t g_lastId = 0;

static size_t g_lastTakeId = 0;
static streampos g_lastTakeBytes = 0;

void CreatePathTxt(const char* txtBase) {
    g_path = string(pathToDataBases);

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

size_t GetLastIdTxt() {
    return ++g_lastId;
}

void AppendProductTxt(ProductString* product) {
    ofstream out(g_path, std::iostream::app);
    product->id = GetLastIdTxt();
    if (product->id != 0 && out.is_open()) {
        out << *product;
    }
    out.close();
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

void AddTxtRandom(size_t n) {
	ProductString* newProduct = new ProductString();

    for (size_t i = 0; i < n; i++) {
        newProduct->Randomaze();
        AppendProductTxt(newProduct);
    }

	delete newProduct;
}

void CopyFileTxt(const char* path, const char* newPath) {
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
