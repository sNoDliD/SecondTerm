#include "Header.h"
#include <cstring>

char* path;
char* pathStore;
int lastIdStore = 0;
int lastIdProduct = 0;

void createPathBin() {
    pathStore = new char[strlen(pathToDataBases) + strlen(storeBase) + 1];
    strcpy_s(pathStore, strlen(pathToDataBases) + 1, pathToDataBases);
    strcat_s(pathStore, strlen(pathToDataBases) + strlen(storeBase) + 1, storeBase);

    path = new char[strlen(pathToDataBases) + strlen(binBase) + 1];
    strcpy_s(path, strlen(pathToDataBases) + 1, pathToDataBases);
    strcat_s(path, strlen(pathToDataBases) + strlen(binBase) + 1, binBase);
}

void deletePathBin() {
    delete path;
    delete pathStore;
}

void setLastIdStore() {
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

int getLastIdStore() {
    return ++lastIdStore;
}

void writeToFileBin(Store* store) {
    FILE* file;
    fopen_s(&file, pathStore, "ab");
    if (file != 0) {
        fwrite(store, sizeof(Store), 1, file);
        fclose(file);
    }
    else
        throw -1;
}

Store* readFromFileBin(int count) {
    if (lastIdStore == 0) return nullptr;

    Store* s = new Store();
    FILE* file;
    fopen_s(&file, pathStore, "rb"); 


    if (file != 0) {
        fseek(file, count * sizeof(Store), SEEK_SET);
        fread(s, sizeof(Store), 1, file);
        if (feof(file)) {
            delete s;
            s = nullptr;
        }
        fclose(file);
    }
    else
        throw - 1;
    return s;
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