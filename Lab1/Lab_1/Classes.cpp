#include "Header.h"


#pragma region Product

Product::Product() :
	id(0),
	name("\0"),
	count(0),
	date(),
	units(),
	expirationDate(0),
	storeId(0) {}

string Product::ToString() {
	string result = "\tProduct #" + to_string(id) + "\n";
	result +="Name: " + string(name) + "\n";
	result +="Amount: " + FloatToString(count) + " " + UnitsToString((int)units) +"\n";
	result +="Create: " + date.ToString() + "\n";
	result +="Life time: " + to_string(expirationDate) + " days\n";
	
	return result;
}

void Product::Randomaze(){
	StringRandom(name);
	Capitalize(name);

	date.Randomaze();

	expirationDate = rand() % 1000 + 1;

	units = Units(rand() % 4);

	count = (float) (rand() % 1000 + 1);
	if (units == Units::KILOGRAMMS || units == Units::LITERS)
		count += (float)(rand() % 1000) / 1000;

	storeId = ShopId();

	id = rand() % (UINT32_MAX - 2) + 1;
}

#pragma endregion


#pragma region ProductString

ProductString::ProductString() :
	id(0),
	name(""),
	count(0),
	date(),
	units(),
	expirationDate(0),
	storeId(0){}

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

	id = rand() % (UINT32_MAX - 2) + 1;
}

std::istream& operator>> (std::istream& in, ProductString& product){
	in >> product.id;						
	if (product.id == 0) {
		while (in.get() != '\n')
			if (in.eof()) break;
		return in;
	}
	in >> product.date;					
	in >> product.count;					
	in >> product.expirationDate;			
	int units = 0;
	in >> units;
	product.units = Units(units);				
	in >> product.storeId;					
	
	string result = "";
	char c = in.get();
	while (c = in.get()) {
		if (c == '\n' || in.eof())
			break;
		result += c;
	}
	product.name = result;				

	return in;
}

std::ostream& operator<< (std::ostream& out, const ProductString& product){
	out << product.id << ' ';						
	out << product.date << ' ';				
	out << product.count << ' ';		
	out << product.expirationDate << ' ';		
	out << (int)product.units << ' ';	
	out << product.storeId << ' ';			
	out << product.name << '\n';

	return out;
}

#pragma endregion


#pragma region Date

Date::Date():
	year(0),
	mounth(0),
	day(0),
	hours(0),
	minutes(0) {}

bool Date::Correct() {
	if (mounth > 12 || mounth < 1) return false;
	if (year < 0) return false;
	if (minutes > 59 || minutes < 0) return false;
	if (hours > 23 || hours < 0) return false;
	int daysInMounth[12] = { 31,28 + (int)(year % 4 == 0), 31,30,31,30,31,31,30,31,30,31 };
	if (day < 1 || day > daysInMounth[mounth - 1]) return false;

	return true;
}

bool Date::SetDate(int day, int mounth, int year, int hours, int min){
	this->day = day;
	this->mounth = mounth;
	this->year = year;
	this->hours = hours;
	this->minutes = min;

	return Correct();
}

template< typename T>
string AddChar(T value, size_t minCount = 2, char returnValue = '0') {
	string result = "";
	for (size_t i = 0; i < minCount - 1; ++i)
		if ((int)value < pow(10, (i + 1))) 
			result += returnValue;

	result += to_string((int)value);
	return result;
}

string Date::ToString(){
	return AddChar(day) + "." + AddChar(mounth) + "." + AddChar(year, 4) + 
		" " + AddChar(hours) + ":" + AddChar(minutes);
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
	byte2 data = 0;
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

bool operator<(Date& first, Date& second){
	if (first.year > second.year) return false;
	if (first.year < second.year) return true;

	if (first.mounth > second.mounth) return false;
	if (first.mounth < second.mounth) return true;

	if (first.day > second.day) return false;
	if (first.day < second.day) return true;

	if (first.hours > second.hours) return false;
	if (first.hours < second.hours) return true;

	if (first.minutes > second.minutes) return false;
	if (first.minutes < second.minutes) return true;
	
	return false;
}

#pragma endregion


#pragma region Shop

Store::Store() :
	id(0),
	maxProductCount(0),
	rating(0),
	name("\0"),
	adress("\0"){}

void Store::Randomaze(){
	StringRandom(name);
	Capitalize(name);

	StringRandom(adress);
	Capitalize(adress);

	rating = (float)(rand() % 1000) / 1000 + rand() % 10;

	maxProductCount = rand() % (size_t)1e7 + (size_t)1e4;

	id = rand() % (UINT32_MAX - 2) + 1;
}

string Store::ToString(){
	string result = "\tStore #" + to_string(id) + "\n";
	result += "Name: " + string(name) + "\n";
	result += "Adress: " + string(adress)+ "\n";
	result += "Rating: " + FloatToString(rating) + "\n";
	result += "Max product count: " + to_string(maxProductCount) + "\n";

	return result;
}

#pragma endregion
