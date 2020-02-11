#include "Header.h"

#pragma region Product

Product::Product() {
	id = 0;
	for (byte i = 0; i < nameSize; ++i) {
		name[i] = '0';
	}
	name[nameSize - 1] = '\0';
	count = 0;
	date = Date();
	units = Units(0);
	expirationDate = 0;
	storeId = 0;
}

Product::~Product(){
	cout << "Memory has been cleaned" << endl;
}

#pragma endregion


#pragma region ProductString

ProductString::ProductString() {
	id = 0;
	name = "";
	count = 0;
	date = Date();
	units = Units(0);
	expirationDate = 0;
	storeId = 0;
}

ProductString::~ProductString(){
	cout << "Memory has been cleaned" << endl;
}

std::ostream& operator<< (std::ostream& out, const ProductString& product){
	out << product.id << '\n';						//<< "id: " 
	out << product.name << '\n';					//<< "name: " 
	out << product.date << '\n';					//<< "date: "
	out << product.count << '\n';					//<< "coutnt: " 
	out << product.expirationDate << '\n';			//<< "expirationDate: " 
	out << (int)product.units << '\n';				//<< "units: "
	out << product.storeId << endl;					//<< "storeId: " 

	return out;
}

#pragma endregion


#pragma region Date

Date::Date() {
	year = 0;
	mounth = 0;
	day = 0;
	hours = 0;
	minutes = 0;
}


template< typename T>
void addChar(std::ostream& out, byte count, T value, char returnValue = '0') {
	char* result = new char[count + 1];
	byte now = 0;
	//Todo: start from end
	for (int i = 0; i < count - 1; ++i) {
		if (value < 10 * (i + 1)) {
			*(result + now++) = returnValue;
		}
	}
	*(result + now) = '\0';
	out << result << (int)value;
	delete[] result;
}

std::ostream& operator<< (std::ostream& out, const Date& date) {
	/* dd.mm.yyyy hh:mm

	char delimiterFirst = '.';
	char delimiterSecond = ':';

	addChar(out, 2, date.day);
	out << delimiterFirst;
	addChar(out, 2, date.mounth);
	out << delimiterFirst;
	addChar(out, 4, date.year);
	out << ' ';
	addChar(out, 2, date.hours);
	out << delimiterSecond;
	addChar(out, 2, date.minutes);
	*/
	out << (int)date.day << ' ' << (int)date.mounth << ' ' <<
		date.year << ' ' << (int)date.hours << ' ' << (int)date.minutes;

	return out;
}

#pragma endregion


#pragma region Shop

Store::Store() {
	id = 0;
	maxProductCount = 0;
	rating = 0;
}

Store::~Store() {
	cout << "Memory from store has been cleaned" << endl;
}

#pragma endregion
