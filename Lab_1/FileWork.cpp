#include "Header.h"

void Initialization() {
	CreatePathTxt();
	CreatePathBin();
	SetLastIdStore(); //Todo: clear and setLastId
	SetLastIdBin();
	SetLastIdTxt();
}

void MemoryFree() {
	DeletePathBin();
}


const char* UnitsToString(int unitId) {
	switch (Units(unitId)){
	case Units::PIECE:
		return "pieces";
	case Units::KILOGRAMMS:
		return "kilogramms";
	case Units::LITERS:
		return "litters";
	case Units::BAG:
		return "bags";
	default:
		throw - 2;
	}
}

void InputStr(char* str) {
	cin.getline(str, nameSize);
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT64_MAX, '\n');
		SetColor(6);
		cout << "\tSo big word, enter less than " << (int)nameSize << " symbols" << endl;
		SetColor();
		cin.getline(str, nameSize);
	}
}

void InputStr(Date& date) {
	int day, mounth, year, hour, min;
	while (true) {
		int count = scanf_s("%d.%d.%d %d:%d", &day, &mounth, &year, &hour, &min);
		if (cin.fail() || count != 5) {
			cin.clear();
			cin.ignore(INT64_MAX, '\n');
		}
		else {
			if (date.SetDate(day, mounth, year, hour, min))
				return;
		}
		SetColor(6, "\tIncorrect input. Try again");
	}
}
template <typename T>
void InputStr<T>(T& str) {
	cin >> str;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT64_MAX, '\n');
		SetColor(6, "\tIncorrect input. Try again");
		cin >> str;
	}
	cin.clear();
	cin.ignore(INT64_MAX, '\n');
}

string FloatToString(float str, const size_t accuracy) {
	string result = "";
	int whole = int(str);
	str -= whole;

	while (whole > 0) {
		char now = whole % 10 + '0';
		result = now + result;
		whole /= 10;
	}

	whole = int((1 + str) * pow(10, accuracy + 1));

	string extra = "";
	bool over = false;
	bool first = true;

	for (size_t i = 0; i < accuracy + 1; i++) {
		char now = whole % 10 + '0';
		bool add = true;

		if (first && now == '0' && !over)
			add = false;
		else if (now > '4' && i == 0) {
			over = true;
			add = false;
		}
		else if (over) {
			now++;
			over = false;
			if (now == '9' + 1) {
				add = false;
				over = true;
			}
		}
		if (add) {
			first = false;
			extra = now + extra;
		}
		whole /= 10;
	}

	if (result == "")
		result = "0";
	while (extra.length() > accuracy)
		extra.pop_back();
	if (extra != "")
		result += "." + extra;
	return result;
}

/*Ask list
 1. Можно ли выбирать в функции параинтр для передачи значение 
 2. char[] as param in func
 3. templete...
 4. ...params
 */

/*Notes
(-3%) no support for real numbers in different formats (either 0.5 or 0,5)

(-9%) Implementing custom function or type that repeats features of standard library
datetime -> use std::tm
parse datetime -> use std::get_time or implement using sscanf
datetime to string, output -> use strftime


for (auto strList : { "hello", "world" })

int f() {
	return 0;
}
template<typename... T>
int f(float x, float y, const T&... tail) {
	return int(x*x + y*y - R*R < 0.0001) + f(tail...);
}
*/