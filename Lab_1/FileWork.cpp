#include "Header.h"

void initialization() {
	createPathTxt();
	createPathBin();
	setLastIdStore(); //Todo: clear and setLastId
}

void memoryFree() {
	deletePathBin();
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

template <typename T>
void InputStr<T>(T& str) {
	cin >> str;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT64_MAX, '\n');
		SetColor(6);
		cout << "\tIncorrect input. Try again" << endl;
		SetColor();
		cin >> str;
	}
	cin.clear();
	cin.ignore(INT64_MAX, '\n');
}

 /*Ask list
 1. Можно ли выбирать в функции параинтр для передачи значение 
 2. char[] as param in func
 3. templete...
 */

/*Notes
fread return count of readed objects
*/