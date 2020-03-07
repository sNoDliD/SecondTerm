#ifndef All_HEADER_IN_ONE_FILE
#define All_HEADER_IN_ONE_FILE

#include <iostream>
#include <ctime>
#include "UsefulFeatures.h"
#include "Menu.h"
#include "Classes.h"

using std::cout;
using std::endl;
typedef unsigned char byte;

enum class Mode {
	FIXEDSIZE,
	VECTOR,
	LINKEDLIST
};

struct IP {
	unsigned adress;

	IP(unsigned adress = 0) : adress(adress) {}
	
	IP(int a, int b, int c, int d) : adress((a << 24) + (b << 16) + (c << 8) + d) {}
};

IP RandomIP();

std::string to_string(IP ip);

void InputStr(int& str, const char* preMessage, int leftBorder = INT32_MIN, int rightBorder = INT32_MAX);

IP InputIP();

void StartMenu();


#endif // !All_HEADER_IN_ONE_FILE
