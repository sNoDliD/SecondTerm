#include "Header.h"
using std::to_string;

#pragma region Product

Product::Product() {
	id = 0;
	for (byte i = 0; i < nameSize; ++i) {
		name[i] = '\0';
	}
	name[nameSize - 1] = '\0';
	count = 0;
	date = Date();
	units = Units(0);
	expirationDate = 0;
	storeId = 0;
}

string Product::ToString() {
	string result = "\tProduct #" + to_string(id) + "\n";
	result +="Name: " + string(name) + "\n";
	result +="Amound: " + to_string(count) + " " + uninsString((int)units) +"\n";
	result +="Create: " + date.ToString() + "\n";
	result +="Life time: " + to_string(expirationDate) + " days\n";
	
	return result;
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

bool Date::setDate(int day, int mounth, int year, int hours, int min)
{
	if (mounth > 12 || mounth < 1) return false;
	if (year < 0) return false;
	if (min > 59 || min < 0) return false;
	if (hours > 23 || hours < 0) return false;
	int daysInMounth[12] = { 31,28 + (int)(year % 4 == 0), 31,30,31,30,31,31,30,31,30,31 };
	if (day < 1 || day > daysInMounth[mounth - 1]) return false;

	this->day = day;
	this->mounth = mounth;
	this->year = year;
	this->hours = hours;
	this->minutes = min;

	return true;
}

template< typename T>
string addChar(byte count, T value, char returnValue = '0') {
	string result = "";
	for (int i = 0; i < count - 1; ++i) {
		if ((int)value < pow(10, (i + 1))) {
			result += returnValue;
		}
	}
	result += std::to_string((int)value);
	return result;
}

string Date::ToString(){
	return addChar(2, day) + "." + addChar(2,mounth) + "." + addChar(4, year) + " " 
		+ addChar(2, hours) + ":" + addChar(2,minutes);
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

#pragma endregion
