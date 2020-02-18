#include "Header.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

string path;
int lastId = 0;

void CreatePathTxt() {
    path = string(pathToDataBases);
    path.append(txtBase);
}


void SetLastIdTxt() {
    int i = 0;
    ProductString* product;
    ofstream out(path, std::iostream::app);
    out.close();
    while (true) {
        ProductString* product = TakeProductTxt(i++);
        if (product == nullptr)
            break;
        lastId = product->id;
        delete product;
    }
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
    ProductString* product = new ProductString;
    ifstream in;
    in.open(path);
    for (int i = 0; i <= indexInFile; i++)
        in >> *product;
    if (in.eof()) {
        delete product;
        product = nullptr;
    }
    in.close();
    return product;
}



//
//if (remove(argv[1]) == -1)
//printf("Remove Error");
////
//if (rename(argv[1], argv[2]) != 0)
//printf("Rename Error");