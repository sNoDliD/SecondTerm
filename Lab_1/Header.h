#ifndef MAIN_HEADER_ALL_CPP
#define MAIN_HEADER_ALL_CPP
#include <iostream>
#include <string>


#pragma region UsingAndTypedef

using std::cout;
using std::endl;
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
const char storeBase[] = "Store.(winer)";

#pragma endregion


#pragma region Menu

void doMenu();

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
	char name[27];			//27
	float count;			//4
	Date date;				//6
	byte2 expirationDate;	//2
	int storeId;			//4
	Units units;			//1		

	Product();

	~Product();

	friend std::ostream& operator<< (std::ostream&, const Product&);
};
#pragma pack (pop)

class ProductString {


};


class Store {

};

#pragma endregion


#pragma region FileHeader

void createPathTxt();
void createPathBin();
void writeToFileTxt(Product*);
void writeToFileBin();
Product* readFromFileTxt();

#pragma endregion


#pragma region AddFunctions

void initialization();
void memoryFree();

#pragma endregion

#endif //MAIN_HEADER_ALL_CPP