#include "Header.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

void Initialization() {
	cout << "Wait for initialization..." << endl;
	CreatePathStore();
	srand((unsigned int) time(0));
	SetLastIdStore();
}

void MemoryFree() {
	DeletePathBin();
}

void Capitalize(string& str) {
	size_t len = str.length();
	if (len < 1) return;
	str[0] = toupper(str[0]);
	for (size_t i = 1; i < len; i++)
		str[i] = tolower(str[i]);
}

void Capitalize(char* str) {
	size_t len = strlen(str);
	if (len < 1) return;
	str[0] = toupper(str[0]);
	for (size_t i = 1; i < len; i++)
		str[i] = tolower(str[i]);
}

bool SubString(const char* main, const char* compare) {
	size_t mainLen = strlen(main), compareLen = strlen(compare);
	if (mainLen < compareLen)
		return false;

	for (size_t i = 0; i <= mainLen - compareLen; i++) {
		bool result = true;
		for (size_t j = 0; j < compareLen; j++)
			if (tolower(main[i + j]) != tolower(compare[j])) {
				result = false;
				break;
			}
		if (result == false)
			continue;
		return true;
	}
	return false;
}

bool SubString(const string& main, const string& compare) {
	size_t mainLen = main.length(), compareLen = compare.length();
	if (mainLen < compareLen)
		return false;

	for (size_t i = 0; i <= mainLen - compareLen; i++) {
		bool result = true;
		for (size_t j = 0; j < compareLen; j++)
			if (tolower(main[i + j]) != tolower(compare[j])) {
				result = false;
				break;
			}
		if (result == false)
			continue;
		return true;
	}
	return false;
}

void StringRandom(string& str, size_t minSize, size_t maxSize) {
	str = "";
	if (minSize > maxSize)
		minSize = 0;
	size_t len = rand() % (maxSize - minSize + 1) + minSize;
	for (size_t i = 0; i < len; i++)
		str += rand() % ('z' - 'a') + 'a';
}

void StringRandom(char* str, size_t minSize, size_t maxSize) {
	if (minSize > maxSize)
		minSize = 0;
	size_t len = rand() % (maxSize - minSize + 1) + minSize;
	for (size_t i = 0; i < len; i++)
		str[i] = rand() % ('z' - 'a') + 'a';
	str[len] = '\0';

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
		else if (date.SetDate(day, mounth, year, hour, min))
				return;
		SetColor(6, "\tIncorrect input. Try again");
	}
}

void InputStr(size_t& str){
	long int temp;
	cin >> temp;
	while (cin.fail() || temp < 1) {
		cin.clear();
		cin.ignore(INT64_MAX, '\n');
		SetColor(6, "\tIncorrect input. Enter value > 0");
		cin >> temp;
	}
	cin.clear();
	cin.ignore(INT64_MAX, '\n');
	str = (size_t)temp;
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
 3. templete...
 4. ...params

6. what faster == or <


	Todo: *all vector delete
	todo: think zero product in txt
	*/

	/* Worksheet

	--1. Modify
	-----2. Delete
	--3. Shop Find
	4. Demonstration
	5. Benchmark

 */

/*Notes
int f() {
	return 0;
}
template<typename... T>
int f(float x, float y, const T&... tail) {
	return int(x*x + y*y - R*R < 0.0001) + f(tail...);
}
*/
