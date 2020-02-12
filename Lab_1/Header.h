#ifndef MAIN_HEADER_ALL_CPP
#define MAIN_HEADER_ALL_CPP

#include <iostream>
#include <string>

#pragma region UsingAndTypedef

using std::cout;
using std::endl;
using std::cin;
using std::string;

typedef unsigned char byte;
typedef unsigned short int byte2;

#pragma endregion


#pragma region Constants

const byte nameSize = 27;
const char pathToDataBases[] = "DataBases/";
const char txtBase[] = "Products.txt";
const char binBase[] = "Products.bin";
const char storeBase[] = "Store.bin";

#pragma endregion


#pragma region MyTypes

enum class Mode : byte {
	WAIT,
	VECTOR,
	TXT,
	BIN
};

enum class Units : byte {
	PIECE,
	KILOGRAMMS,
	LITERS,
	BAG
};

const char* uninsString(int unitId);

struct Date {
	byte2 year : 12;
	byte mounth : 5;
	byte day : 6;
	byte hours : 5;
	byte minutes : 6;
	Date();
	bool setDate(int, int, int, int, int);
	friend std::ostream& operator<< (std::ostream&, const Date&);
	string ToString();
};

#pragma pack(push, 1)
class Product {
public:
	int id;					//4
	char name[nameSize];			//27
	float count;			//4
	Date date;				//6
	byte2 expirationDate;	//2
	int storeId;			//4
	Units units;			//1		

	Product();

	string ToString();
};
#pragma pack (pop)

class ProductString {
public:
	int id;					//4
	string name;
	float count;			//4
	Date date;				//6
	byte2 expirationDate;	//2
	int storeId;			//4
	Units units;			//1		

	ProductString();

	~ProductString();

	friend std::ostream& operator<< (std::ostream&, const ProductString&);

};

#pragma pack (push, 1)
class Store {
public:
	int id;					//4
	char name[nameSize] = { '\0' };	//27
	char adress[nameSize] = { '\0' };	//27
	float rating;			//4
	int maxProductCount;	//4

	Store();
};
#pragma pack(pop)

#pragma endregion


#pragma region Menu

void SetColor(int color = 14);
void SetColor(int, const char*);
int startMenu();
int Interactive();
int Demonstration();
int Benchmark();
int ShopChoice();
int ShopCreate();
int Add();
int ShowAll();

#pragma endregion


#pragma region FileHeader

void createPathTxt();
void createPathBin();
void deletePathBin();

void writeToFileTxt(ProductString*);
ProductString* readFromFileTxt();

void writeToFileBin(Store*);
Store* readFromFileBin(int count = 0);

void writeToFileBin(Product* product);
Product* readFromFileBinProduct(int count);

#pragma endregion


#pragma region AddFunctions
void initialization();
void memoryFree();

void setLastIdStore();
int getLastIdStore();

void setLastIdProduct();
int getLastIdProduct();

void InputStr(char*);
void InputStr(Date&);
template <typename T>
void InputStr(T& str);
template void InputStr<int>(int&);
template void InputStr(float&);
template void InputStr(byte2&);


#pragma endregion

#endif //MAIN_HEADER_ALL_CPP