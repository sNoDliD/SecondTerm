#ifndef ADD_THIS_IN_ALL_MY_PRODUCTS
#define ADD_THIS_IN_ALL_MY_PRODUCTS

#include <string>
#include <iostream>
#include <initializer_list>

std::string FloatToString(float str, size_t accuracy = 3);

#pragma region Template


template <typename Tfunc, typename... T>
int CallWithoutBack(Tfunc& Func, const char* message = "", T&... data) {
	try {
		Func(data...);
	}
	catch (const char* msg) {
		system("cls");
		std::cout << "Error: " << msg << std::endl;
		return -1;
	}
	system("cls");
	std::cout << message;
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



#endif // !ADD_THIS_IN_ALL_MY_PRODUCTS
