#include "Header.h"


IP RandomIP() {
	unsigned result = (rand() << 1) + rand() % 2;
	result += ((rand() << 1) + rand() % 2) << 16;
	return IP(result);
}

std::string to_string(IP ip) {
	std::string result = "";

	for (int i = 3; i >= 0; i--) {
		byte now = 0;

		for (size_t n = 0; n < 8; n++) {
			if (((ip.adress >> (i * 8)) >> n) & 1)
				now |= (1 << n);
			else
				now &= ~(1 << n);
		}

		result += std::to_string(now) + ".";
	}

	result.pop_back();
	return result;
}

void InputStr(int& str,const char* preMessage, int leftBorder, int rightBorder) {
	std::cout << preMessage;
	std::cin >> str;
	while (std::cin.fail() || str < leftBorder || str > rightBorder) {
		std::cin.clear();
		std::cin.ignore(1i64, '\n');
		SetColor(6, "\tIncorrect input. Enter value [", leftBorder, ",", rightBorder, "]\n");
		std::cin >> str;
	}
	std::cin.clear();
	std::cin.ignore(1i64, '\n');
}


IP InputIP(){
	Menu menu("How add IP:", { 
		MenuItem("Random", nullptr, 1),
		MenuItem("Yourself", nullptr, 2) },
		"");

	int result = menu.DoMenu();
	while (result == (int)MenuMode::EXIT)
		result = menu.DoMenu();

	if (result == 1) return RandomIP();
	else {
		int a, b, c, d;
		cout << "Input IPv4 (255.255.255.255):\n";
		while (true) {
			if (scanf_s("%d.%d.%d.%d", &a, &b, &c, &d) == 4) {
				if (!(a < 0 || b < 0 || c < 0 || d < 0 ||
					a > 255 || b > 255 || c > 255 || d > 255))
					return IP(a, b, c, d);
			}
			SetColor(6, "\tIncorrect input. Try again\n");
		}

	}
	throw "Unreachable code";
}

//void InputStr(char* str) {
//	cin.getline(str, g_nameSize);
//	if (ClearIfBreak()) {
//		SetColor(6, "\tSo big word, enter less than ", (int)g_nameSize, " symbols\n");
//		InputStr(str);
//	}
//	if (strlen(str) == 0) {
//		SetColor(6, "\tIt's not a word\n");
//		InputStr(str);
//	}
//}
//
//void InputStr(Date& date, const bool withoutTime) {
//	int day, mounth, year, hour = 0, min = 0;
//	while (withoutTime == false) {
//		int count = scanf_s("%d.%d.%d %d:%d", &day, &mounth, &year, &hour, &min);
//		if (ClearIfBreak(count != 5) == false)
//			if (date.SetDate(day, mounth, year, hour, min)) break;
//		SetColor(6, "\tIncorrect input. Or try enter in format: day.mounth.year hour:minutes\n");
//	}
//	while (withoutTime == true) {
//		int count = scanf_s("%d.%d.%d", &day, &mounth, &year);
//		if(ClearIfBreak(count != 3) == false)
//			if (date.SetDate(day, mounth, year, hour, min)) break;
//		SetColor(6, "\tIncorrect input. Or try enter in format: day.mounth.year \n");
//	}
//	ClearIfBreak(true);
//}