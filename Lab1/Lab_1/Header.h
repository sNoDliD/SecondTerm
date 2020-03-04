#ifndef MAIN_HEADER_ALL_CPP
#define MAIN_HEADER_ALL_CPP

#include "Menu.h"
#include <iostream>
#include <string>
#include <time.h>
#include <initializer_list>


#pragma region UsingAndTypedef

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::to_string;


typedef unsigned char byte;
typedef unsigned short int byte2;

#pragma endregion


#pragma region Constants

const size_t g_nameSize = 27;

const char g_pathToDataBases[] = "DataBases/";

const char g_storeBase[] = "Store.bin";

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

#pragma pack(push, 1)
struct Date { 
	byte2 year : 12;
	byte mounth : 5;
	byte day : 6;
	byte hours : 5;
	byte minutes : 6;

	explicit Date();

	bool Correct();

	bool SetDate(int day, int mounth, int year, int hours, int min);

	friend std::ostream& operator<< (std::ostream&, const Date&);
	friend std::istream& operator>> (std::istream& in, Date& data);

	friend bool operator < (Date& first, Date& second);

	string ToString();

	void Randomaze();

	int DaysBetween(Date another);

	int DaysSinceChristmas();
};
#pragma pack (pop)

#pragma pack(push, 1)
class Product {
public:
	size_t id;					//4
	char name[g_nameSize];			//27
	float count;			//4
	Date date;				//6
	byte2 expirationDate;	//2
	size_t storeId;			//4
	Units units;			//1

	Product();

	string ToString();

	void Randomaze();
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
	char name[g_nameSize];	//27
	char adress[g_nameSize];	//27
	float rating;			//4
	size_t maxProductCount;	//4

	Store();

	void Randomaze();

	string ToString();
};
#pragma pack(pop)

#pragma endregion


#pragma region GetStatic

size_t ShopId();
size_t ShopMaxCount();
void SetShop(size_t shopId);

Mode WorkMode();
void SetWorkMode(Mode mode);

#pragma endregion


#pragma region Menu

int StartMenu();

bool AllProductCorrect(Date& date);

int Demonstration();

int Benchmark();

#pragma endregion


#pragma region FileWork

void CreatePathTxt(const char* txtPath);
void CreatePathBin(const char* binPath);
void CreatePathStore(const char* storeBase);

void SetLastIdBin();

void DeletePathBin(); 
bool FreeVector();
bool FreeShopBin(size_t shopId);
bool FreeShopTxt(size_t shopId); 
bool FreeShops(const char* pathStore, bool reCreate = true);

bool AppendProductVector(Product* product);
Product* TakeProductVector(size_t indexInVector);

bool AppendProductTxt(ProductString* product);
ProductString* TakeProductTxt(size_t indexInFile);

void AppendStore(Store* store);
Store* TakeStore(size_t indexInFile);

bool AppendProductBin(Product* product);
Product* TakeProductBin(size_t indexInFile);

bool AddVectorRandom(size_t n = 1);
bool AddTxtRandom(size_t n = 1);
bool AddBinRandom(size_t n = 1);

bool ModifyVector(size_t id, Product* product);
bool DeleteVector(size_t id);

bool ModifyBin(size_t id, Product* product);
bool DeleteBin(size_t id);

bool ModifyTxt(size_t id, ProductString* product);
bool DeleteTxt(size_t id);

size_t ReorganizeVector();

#pragma endregion


#pragma region AddFunctions

void Initialization();
void MemoryFree();

bool ClearIfBreak(bool condition = false);
void InputStr(char* str);
void InputStr(Date& str, const bool withoutTime = false);
void InputStr(size_t& str);
void InputStr(byte2& str);
void InputStr(string& str);

string FloatToString(float str, size_t accuracy = 3);

void Capitalize(string& str);
void Capitalize(char* str);

bool SubString(const string& main, const string& compare);
bool SubString(const char* main, const char* compare);

void StringRandom(string& str, size_t minSize = 5, size_t maxSize = g_nameSize);
void StringRandom(char* str, size_t minSize = 5, size_t maxSize = g_nameSize);

bool SetValue(const char* preMessage, Units& value); 
void SetValue(float& value, Units& units);

#pragma endregion


#pragma region Template World

template <typename Tproduct, typename T>
bool IsSubName(Tproduct* product, T& str) {
	bool deletedProduct = product->id == 0 || product->storeId != ShopId();
	if (!deletedProduct && SubString(product->name, str))
		return true;
	return false;
}

template <typename Tproduct, typename T>
bool IsMore(Tproduct* product, T& count) {
	bool deletedProduct = product->id == 0 || product->storeId != ShopId();
	if (!deletedProduct && product->count >= count)
		return true;
	return false;
}

template <typename Tproduct>
bool IsDied(Tproduct* product, Date& date) {
	bool deletedProduct = product->id == 0 || product->storeId != ShopId();
	if (!deletedProduct && product->date.DaysBetween(date) >= product->expirationDate)
		return true;
	return false;
}

template <typename T>
bool ZeroToTen(T& str) {
	if (str >= 0 && str <= 10)
		return true;
	return false;
}

template <typename T>
bool Positive(T& str) {
	if (str > 0)
		return true;
	return false;
}

template <typename T>
void InputStr(T& str) {
	cin >> str;
	while (ClearIfBreak()) {
		SetColor(6, "\tIncorrect input. Try again\n");
		cin >> str;
	}
	ClearIfBreak(true);
}

template <typename T>
void SetValue(const char* preMessage, T& value, bool (*condition)(T&) = nullptr,
	const char*errorMessage = "\tIncorrect input. Try again\n", const char* endMessage = "(perfect)\n\n") {
	cout << preMessage;
	InputStr(value);
	while (condition && !condition(value)) {
		SetColor(6, errorMessage);
		InputStr(value);
	}
	cout << endMessage;
}

template <typename T>
T SwitchFunc(int mode, std::initializer_list<T> Func) {
	int size = Func.size();
	if (mode <= 0 || mode > size)
		return nullptr;
	return *(Func.begin() + mode - 1);
}

template <typename T>
int SetIndex(T element, std::initializer_list<T> list) {
	size_t size = list.size();
	for (size_t i = 0; i < size; i++) {
		if (element == *(list.begin() + i))
			return i + 1;
	}
	return 0;
}

template <typename Tproduct, typename... T>
size_t ShowByCondition(bool (*Condition)(Tproduct*, T&...) = nullptr, T&... data) {
	size_t totalFind = 0, i = 0;
	int index = SetIndex(WorkMode(), { Mode::VECTOR, Mode::BIN });
	auto TakeProduct = SwitchFunc(index, { TakeProductVector, TakeProductBin });
	Tproduct* product;

	while (true) {
		if (TakeProduct)
			product = (Tproduct*)TakeProduct(i++);
		else
			product = (Tproduct*)TakeProductTxt(i++);

		if (product == nullptr) break;
		bool deletedProduct = product->id == 0 || product->storeId != ShopId();
		if (!deletedProduct && (Condition == nullptr || Condition(product, data...))) {
			cout << product->ToString() << endl;
			totalFind++;
		}
		if (WorkMode() != Mode::VECTOR) delete product;
	}
	return totalFind;
}

#pragma endregion

#endif 