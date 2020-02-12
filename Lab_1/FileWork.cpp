#include "Header.h"

void initialization() {
	createPathTxt();
	createPathBin();
	setLastIdStore(); //Todo: clear and setLastId
	setLastIdProduct();
}

void memoryFree() {
	deletePathBin();
}


const char* uninsString(int unitId) {

	switch (Units(unitId))
	{
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
			if (date.setDate(day, mounth, year, hour, min))
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

 /*Ask list
 1. Можно ли выбирать в функции параинтр для передачи значение 
 2. char[] as param in func
 3. templete...
 4. ...params
 */

/*Notes
fread return count of readed objects

int f() {
	return 0;
}
template<typename... T>
int f(float x, float y, const T&... tail) {
	return int(x*x + y*y - R*R < 0.0001) + f(tail...);
}
*/