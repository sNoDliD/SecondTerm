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

const char* UnitsToString(int unitId);

struct Date {
	byte2 year : 12;
	byte mounth : 5;
	byte day : 6;
	byte hours : 5;
	byte minutes : 6;
	Date();
	bool SetDate(int day, int mounth, int year, int hours, int min);
	friend std::ostream& operator<< (std::ostream&, const Date&);
	friend std::istream& operator>> (std::istream& in, Date& data);
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

	string ToString();

	friend std::ostream& operator<< (std::ostream&, const ProductString&);
	friend std::istream& operator>> (std::istream& in, ProductString& product);

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
int StartMenu();
int Interactive();
int Demonstration();
int Benchmark();
int ShopChoice();
int ShopCreate();
int Add();
int ShowAll();

#pragma endregion


#pragma region FileHeader

void CreatePathTxt();
void CreatePathBin();
void DeletePathBin();

void SetLastIdStore();
int GetLastIdStore();

void SetLastIdBin();
int GetLastIdBin();

int GetLastIdVector();

void SetLastIdTxt();
int GetLastIdTxt();

void AppendProductVector(Product* product);
Product* TakeProductVector(size_t indexInVector);

void AppendProductTxt(ProductString* product);
ProductString* TakeProductTxt(int indexInFile);

void AppendStore(Store*);
Store* TakeStore(int indexInFile);

void AppendProductBin(Product* product);
Product* TakeProductBin(int indexInFile);

#pragma endregion


#pragma region AddFunctions
void Initialization();
void MemoryFree();

void InputStr(char*);
void InputStr(Date&);
template <typename T>
void InputStr(T& str);
template void InputStr<int>(int&);
template void InputStr(float&);
template void InputStr(byte2&);

string FloatToString(float str, const size_t accuracy = 3);

#pragma endregion

#endif //MAIN_HEADER_ALL_CPP