#ifndef MAIN_HEADER_ALL_CPP
#define MAIN_HEADER_ALL_CPP
#include <iostream>
#include <string>


#pragma region UsingAndTypedef

using std::cout;
using std::endl;
using std::cin;
using std::string;

////#define cout std::cout
//#define endl std::endl

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


#pragma region Menu
void SetColor(int color = 14);
int startMenu();
int Interactive();
int Demonstration();
int Benchmark();
int ShopChoice();
int ShopCreate();
int Add();

#pragma endregion


#pragma region MyTypes

enum class Units : byte {
	PIECE,
	KILOGRAMMS,
	LITERS,
	BAG
};

struct Date {
	byte2 year : 12;
	byte mounth : 5;
	byte day : 6;
	byte hours : 5;
	byte minutes : 6;
	Date();
	//Date(char*);
	friend std::ostream& operator<< (std::ostream&, const Date&);
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

	~Product();
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
	~Store();
};
#pragma pack(pop)

#pragma endregion


#pragma region FileHeader

void createPathTxt();
void createPathBin();
void deletePathBin();

void writeToFileTxt(ProductString*);
ProductString* readFromFileTxt();

void writeToFileBin(Store*);
Store* readFromFileBin(int count = 0);

#pragma endregion


#pragma region AddFunctions

void initialization();
void memoryFree();
void setLastIdStore();
int getLastIdStore();
void InputStr(char*);

template <typename T>
void InputStr(T& str);
template void InputStr(int&);
template void InputStr(float&);


#pragma endregion

#endif //MAIN_HEADER_ALL_CPP