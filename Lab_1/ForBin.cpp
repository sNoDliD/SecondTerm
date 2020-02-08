#include "Header.h"
#include <cstring>

void writeToFileBin() {
    char* path = new char[strlen(pathToDataBases) + strlen(binBase) + 1];
    strcpy_s(path, strlen(pathToDataBases) + 1, pathToDataBases);
    strcat_s(path, strlen(pathToDataBases) + strlen(binBase) + 1, binBase);

    //FILE* in = fopen("input.txt", "r");
    //FILE* out = fopen("output.txt", "w");
    //float a, b, c;
    //while (fscanf(in, "abc /%f,%f,%f\n", &a, &b, &c) == 3)
    //    fprintf(out, "text %7.3f %7.3f %7.3f\n", a, b, c);
}

//char str[] = "Police Academy";
//char key[] = "aeiou";
//
//std::cout << "Поиск гласных букв в строке " << """ << str << ""n";
//char* pch = strpbrk(str, key);                            // первый поиск
//
//while (pch != NULL)                                         // пока есть гласные буквы в строке
//{
//    std::cout << *pch << " ";                               // печать гласного символа
//    pch = strpbrk(pch + 1, key);                                // поиск гласных букв
//}
//
//std::cout << "n";
