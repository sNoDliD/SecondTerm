#include "UsefulFeatures.h"


std::string FloatToString(float str, size_t accuracy) {
	if (accuracy > 6) accuracy = 6;
	if (str < 0) return "-" + FloatToString(-str, accuracy);
	float up = roundf(str * (float)pow(10, accuracy));
	if (up == 0) return "0";

	std::string result = std::to_string(up);
	while (result.back() == '0') result.pop_back();
	if (result.back() == '.') result.pop_back();

	int over = result.size() - accuracy - 1;
	while (over++ < 0) result.insert(0, "0");
	result.insert(result.size() - accuracy, ".");

	while (result.back() == '0') result.pop_back();
	if (result.back() == '.') result.pop_back();
	return result;
}


void SleepPrint(std::string str, const char* preMassege, size_t printPause, size_t pause) {
	std::cout << preMassege;
	Sleep(pause);
	for (auto a : str) {
		std::cout << a;
		Sleep(printPause);
	}
	Sleep(pause);
	std::cout << std::endl;
}

int RandomInt(){
	int result = (rand() << 1) + rand() % 2;
	result += ((rand() << 1) + rand() % 2) << 16;
	return result;
}

void InputStr(int& str, const char* preMessage, int leftBorder, int rightBorder) {
	std::cout << preMessage;
	std::cin >> str;
	while (std::cin.fail() || str < leftBorder || str > rightBorder) {
		std::cin.clear();
		std::cin.ignore(INT32_MAX, '\n');
		std::cout << "\tIncorrect input. Try enter from intervar [" << 
			leftBorder << "," << rightBorder << "]\n";
		std::cin >> str;
	}
	std::cin.ignore(INT32_MAX, '\n');
}

void InputStr(float& str, const char* preMessage, float leftBorder, float rightBorder) {
	std::cout << preMessage;
	std::cin >> str;
	while (std::cin.fail() || str < leftBorder || str > rightBorder) {
		std::cin.clear();
		std::cin.ignore(INT32_MAX, '\n');
		std::cout << "\tIncorrect input. Try enter from intervar [" << 
			leftBorder << "," << rightBorder << "]\n";
		std::cin >> str;
	}
	std::cin.ignore(INT32_MAX, '\n');
}


std::string AddChar(size_t value, size_t minCount, char returnValue) {
	std::string result = "";
	for (size_t i = 0; i < minCount - 1; ++i)
		if ((int)value < pow(10, (i + 1)))
			result += returnValue;

	result += to_string((int)value);
	return result;
}

std::string AddChar(std::string value, size_t minCount, char returnValue) {
	for (size_t i = minCount - value.size(); i > 0; i--)
		value = returnValue + value;

	return value;
}

