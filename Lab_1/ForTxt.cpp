#include "Header.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

string path;
int lastId = 0;

int lastTakeId = 0;
size_t lastTakeBytes = 0;

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
            if (enterCounter == 1 * 2) {
                in.close();
                in.open(path);
                i += 2;
                in.seekg(i, in.end);
                in >> lastId;
                break;
            }
            if (i < -10) {
                lastId = 0;
                break;
            }
            in.close();
            in.open(path);
            continue;
        }
        if (enterCounter == 2 * 2) {    //why it read '\n' twice...?
            in >> lastId;
            break;
        }
    }
    in.close();
}

int GetLastIdTxt() {
    return ++lastId;
}

void AppendProductTxt(ProductString* product) {
    ofstream out(path, std::iostream::app);
    out << *product;

    out.close();
}

ProductString* TakeProductTxt(int indexInFile) {
    ifstream in;
    in.open(path);
    if (!in.is_open())
        return nullptr;
    ProductString* product = new ProductString();
    int i = 0;
    if (indexInFile > lastTakeId) {
        i = lastTakeId + 1;
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
        lastTakeId = indexInFile;
        lastTakeBytes = in.tellg();
    }
    in.close();
    return product;
}

void AddTxtRandom(int n) {
	ProductString* newProduct = new ProductString();

    for (int i = 0; i < n; i++) {
        newProduct->Randomaze();
        AppendProductTxt(newProduct);
    }

	delete newProduct;
}

//
//if (remove(argv[1]) == -1)
//printf("Remove Error");
////
//if (rename(argv[1], argv[2]) != 0)
//printf("Rename Error");