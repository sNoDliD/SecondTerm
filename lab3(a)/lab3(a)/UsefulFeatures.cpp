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


int Random(int start, int end) {
	int circle = (end - start + 1);

	if (circle < 1)
		exit(0);
	
	int result = RandomInt() % circle;
	if (result < 0)
		result += circle;

	return result + start;
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


std::string AddChar(int value, size_t minCount, char returnValue) {
	return AddChar(to_string(value), minCount, returnValue);
}

std::string AddChar(std::string value, size_t minCount, char returnValue) {
	for (int i = minCount - value.size(); i > 0; i--)
		value = returnValue + value;

	return value;
}

