#ifndef ADD_THIS_IN_ALL_MY_PRODUCTS
#define ADD_THIS_IN_ALL_MY_PRODUCTS

#include <string>
#include <iostream>
#include <initializer_list>
#include <Windows.h>

std::string FloatToString(float str, size_t accuracy = 3);

#pragma region Template


template <typename Tfunc, typename... T>
int CallWithoutBack(Tfunc& Func, const char* endMessage = "", T&... data) {
	try {
		Func(data...);
	}
	catch (const char* msg) {
		system("cls");
		std::cout << "Error: " << msg << std::endl;
		return -1;
	}
	system("cls");
	std::cout << endMessage;
	return 0;
}

template <typename T>
std::string to_string(T value) {
	return std::to_string(value);
}

template <typename T>
T SwitchFunc(int mode, std::initializer_list<T> Func) {
	int size = Func.size();
	if (mode <= 0 || mode > size)
		return nullptr;
	return *(Func.begin() + mode - 1);
}

template <typename T>
int SetIndex(T element, std::initializer_list<T> list) {
	size_t size = list.size();
	for (size_t i = 0; i < size; i++) {
		if (element == *(list.begin() + i))
			return i + 1;
	}
	return 0;
}


#pragma endregion

void SleepPrint(std::string str, const char* preMassege, size_t printPause = 160, size_t pause = 600);

int RandomInt();
int Random(int start, int end);

void InputStr(int& str, const char* preMessage, int leftBorder = INT32_MIN, int righrBorder = INT32_MAX);
void InputStr(float& str, const char* preMessage, float leftBorder, float rightBorder);

std::string AddChar(int value, size_t minCount = 10, char returnValue = ' ');
std::string AddChar(std::string value, size_t minCount = 10, char returnValue = ' ');

#endif // !ADD_THIS_IN_ALL_MY_PRODUCTS
