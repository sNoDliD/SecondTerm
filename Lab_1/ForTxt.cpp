#include "Header.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::fstream;
using std::streampos;
string path;
size_t lastId = 0;

size_t lastTakeId = 0;
streampos lastTakeBytes = 0;

void CreatePathTxt(const char* txtBase) {
    path = string(pathToDataBases);

    path.append(txtBase);
    path.append(".txt");
}

void SetLastIdTxt() {
    ofstream out(path, std::iostream::app);
    out.close();

    ifstream in(path);
    int i = 0, enterCounter = 0;
    while (true){
        in.seekg(i--, in.end);
        char c = in.get();
        if (c == '\n')
            enterCounter++;
        if (in.fail()) {
            in.close();
            in.open(path);
            if (enterCounter == 1 * 2) {
                i += 2;
                in.seekg(i, in.end);
                in >> lastId;
                break;
            }
            if (i < -10) {
                lastId = 0;
                break;
            }
            continue;
        }
        if (enterCounter == 2 * 2) {    //why it read '\n' twice...?
            in >> lastId;
            break;
        }
    }
    in.close();
}

size_t GetLastIdTxt() {
    return ++lastId;
}

void AppendProductTxt(ProductString* product) {
    ofstream out(path, std::iostream::app);
    if(product->id != 0)
        out << *product;
    out.close();
}

ProductString* TakeProductTxt(size_t indexInFile) {
    ifstream in;
    in.open(path);
    if (!in.is_open())
        return nullptr;
    ProductString* product = new ProductString();
    size_t i = 0;
    if (indexInFile > lastTakeId - 1) {
        i = lastTakeId;
        in.seekg(lastTakeBytes, in.beg);
    }
    for (; i <= indexInFile; i++) {
        if (in.eof()) {
            delete product;
            product = nullptr; 
            break;
        }
        in >> *product;
    }
    if (!in.eof()) {
        lastTakeId = indexInFile + 1;
        lastTakeBytes = in.tellg();
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
    if (id == 0 || id > lastId)
        return false;
    bool result = false;

    string pathOld = path;
    string newPath = pathOld.erase(path.length() - 4) + "(clone).txt";
    CopyFileTxt(path.c_str(), newPath.c_str());

    ofstream out(path);
    ifstream in(newPath);
    lastId = lastTakeId = 0;
    lastTakeBytes = 0;
    ProductString* product = new ProductString();
    while (true){
        product->id = 0;
        in >> *product;
        if (product->id == 0)
            break;
        if (product->id == id) {
            result = true;
            cout << '\n' << product->ToString();
            if (productModify->id != 0) {
                productModify->id = ++lastId;
                out << *productModify;
            }
        }
        else {
            product->id = ++lastId;
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
