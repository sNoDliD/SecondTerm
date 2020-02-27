#ifndef MAIN_HEADER_ALL_CPP
#define MAIN_HEADER_ALL_CPP

#include <iostream>
#include <string>
#include <time.h>

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
//const char pathToStores[] = "Stores/";
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

struct Date { // byte -> int (cheak on benchmark)
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

	int DaysBetween(Date another);
	int DaysSinceChristmas();
	void Randomaze();
};

#pragma pack(push, 1)
class Product {
public:
	size_t id;					//4
	char name[nameSize];			//27
	float count;			//4
	Date date;				//6
	byte2 expirationDate;	//2
	size_t storeId;			//4
	Units units;			//1

	Product();

	string ToString();

	void Randomaze(size_t id);
};
#pragma pack (pop)

class ProductString {
public:
	size_t id;					//4
	string name;
	float count;			//4
	Date date;				//6
	byte2 expirationDate;	//2
	size_t storeId;			//4
	Units units;			//1

	ProductString();

	string ToString();

	void Randomaze();

	friend std::ostream& operator<< (std::ostream&, const ProductString&);
	friend std::istream& operator>> (std::istream& in, ProductString& product);

};

#pragma pack (push, 1)
class Store {
public:
	size_t id;					//4
	char name[nameSize] = { '\0' };	//27
	char adress[nameSize] = { '\0' };	//27
	float rating;			//4
	size_t maxProductCount;	//4

	Store();

	void Randomaze();
};
#pragma pack(pop)

#pragma endregion


#pragma region Menu
size_t ShopId();
void SetColor(int color = 14);
void SetColor(int color , const char* str);

int StartMenu();

#pragma endregion


#pragma region FileHeader

void CreatePathTxt(const char* txtPath);
void CreatePathBin(const char* binPath);
void CreatePathStore();
void DeletePathBin();

void SetLastIdStore();
size_t GetLastIdStore();

void SetLastIdBin();
size_t GetLastIdBin();

size_t GetLastIdVector();

void SetLastIdTxt();
size_t GetLastIdTxt();

void AppendProductVector(Product* product);
Product* TakeProductVector(size_t indexInVector);

void AppendProductTxt(ProductString* product);
ProductString* TakeProductTxt(size_t indexInFile);

void AppendStore(Store*);
Store* TakeStore(size_t indexInFile);

void AppendProductBin(Product* product);
Product* TakeProductBin(size_t indexInFile);

void AddVectorRandom(size_t n = 1);
void AddTxtRandom(size_t n = 1);
void AddBinRandom(size_t n = 1);

bool ModifyVector(size_t id, Product* product);
bool DeleteVector(size_t id);

bool ModifyBin(size_t id, Product* product);
bool DeleteBin(size_t id);

bool ModifyTxt(size_t id, ProductString* product);
bool DeleteTxt(size_t id);
#pragma endregion


#pragma region AddFunctions

void Initialization();
void MemoryFree();

void InputStr(char* str);
void InputStr(Date& str);
void InputStr(size_t& str);
template <typename T>
void InputStr(T& str) {
	cin >> str;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT64_MAX, '\n');
		SetColor(6, "\tIncorrect input. Try again");
		cin >> str;
	}
	cin.clear();
	cin.ignore(INT64_MAX, '\n');
}

string FloatToString(float str, const size_t accuracy = 3);

void Capitalize(string& str);
void Capitalize(char* str);

bool SubString(const string& main, const string& compare);
bool SubString(const char* main, const char* compare);

void StringRandom(string& str, size_t minSize = 5, size_t maxSize = nameSize);
void StringRandom(char* str, size_t minSize = 5, size_t maxSize = nameSize);

#pragma endregion

#endif //MAIN_HEADER_ALL_CPP
