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
	result +="Amount: " + FloatToString(count) + " " + UnitsToString((int)units) +"\n";
	result +="Create: " + date.ToString() + "\n";
	result +="Life time: " + to_string(expirationDate) + " days\n";
	
	return result;
}

void Product::Randomaze(int id){
	StringRandom(name);
	Capitalize(name);

	date.Randomaze();

	expirationDate = rand() % 1000 + 1;

	units = Units(rand() % 4);

	count = (float) (rand() % 1000 + 1);
	if (units == Units::KILOGRAMMS || units == Units::LITERS)
		count += (float)(rand() % 1000) / 1000;

	storeId = ShopId();

	this->id = id;
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

string ProductString::ToString() {
	string result = "\tProduct #" + to_string(id) + "\n";
	result += "Name: " + name + "\n";
	result += "Amount: " + FloatToString(count) + " " + UnitsToString((int)units) + "\n";
	result += "Create: " + date.ToString() + "\n";
	result += "Life time: " + to_string(expirationDate) + " days\n";

	return result;
}

void ProductString::Randomaze(){
	StringRandom(name);
	Capitalize(name);

	date.Randomaze();

	expirationDate = rand() % 1000 + 1;

	units = Units(rand() % 4);

	count = (float) (rand() % 1000 + 1);
	if (units == Units::KILOGRAMMS || units == Units::LITERS)
		count += (float)(rand() % 1000) / 1000;

	storeId = ShopId();

	id = GetLastIdTxt();
}

std::istream& operator>> (std::istream& in, ProductString& product)
{
	in >> product.id;						//<< "id: " 
	in >> product.date;					//<< "date: "
	in >> product.count;					//<< "coutnt: " 
	in >> product.expirationDate;			//<< "expirationDate: " 
	int units = 0;
	in >> units;
	product.units = Units(units);				//<< "units: "
	in >> product.storeId;					//<< "storeId: " 
	
	string result = "";
	char c = in.get();
	while (c = in.get()) {
		if (c == '\n' || in.eof())
			break;
		result += c;
	}
	product.name = result;				//<< "name: " 

	return in;
}

std::ostream& operator<< (std::ostream& out, const ProductString& product){
	out << product.id << ' ';						//<< "id: " 
	out << product.date << ' ';					//<< "date: "
	out << product.count << ' ';					//<< "coutnt: " 
	out << product.expirationDate << ' ';			//<< "expirationDate: " 
	out << (int)product.units << ' ';				//<< "units: "
	out << product.storeId << ' ';					//<< "storeId: " 
	out << product.name << endl;					//<< "name: " 

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

bool Date::SetDate(int day, int mounth, int year, int hours, int min)
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
string AddChar(T value, size_t minCount = 2, char returnValue = '0') {
	string result = "";
	for (size_t i = 0; i < minCount - 1; ++i)
		if ((int)value < pow(10, (i + 1))) 
			result += returnValue;

	result += std::to_string((int)value);
	return result;
}

string Date::ToString(){
	return AddChar(day) + "." + AddChar(mounth) + "." + AddChar(year, 4) + " " 
		+ AddChar(hours) + ":" + AddChar(minutes);
}

int Date::DaysBetween(Date another){
	return another.DaysSinceChristmas() - DaysSinceChristmas();
}

int Date::DaysSinceChristmas(){
	int daysInMounth[12] = { 31,28 + (int)(year % 4 == 0), 31,30,31,30,31,31,30,31,30,31 };
	int result = (int) (365.2468f * year);
	for (int i = 0; i < mounth; i++)
		result += daysInMounth[i];
	result += day;

	return result;
}

void Date::Randomaze(){
	year = rand() % 20 + 2000;
	mounth = rand() % 12 + 1;
	day = rand() % 31 + 1;
	hours = rand() % 24;
	minutes = rand() % 60;

	if (!SetDate(day, mounth, year, hours, minutes))
		Randomaze();
}

std::ostream& operator<< (std::ostream& out, const Date& date) {
	out << (int)date.day << ' ' << (int)date.mounth << ' ' <<
		date.year << ' ' << (int)date.hours << ' ' << (int)date.minutes;

	return out;
}

std::istream& operator>> (std::istream& in, Date& date){
	int data = 0;
	in >> data;
	date.day = data;
	in >> data;
	date.mounth = data;
	in >> data;
	date.year = data; 
	in >> data;
	date.hours = data; 
	in >> data;
	date.minutes = data;

	return in;
}


#pragma endregion


#pragma region Shop

Store::Store() {
	id = 0;
	maxProductCount = 0;
	rating = 0;
}

void Store::Randomaze(){
	StringRandom(name);

	StringRandom(adress);

	rating = (float)(rand() % 100 / 100) + rand() % 10;

	maxProductCount = rand() % (int)1e7 + 1;

	id = GetLastIdStore();
}

#pragma endregion
