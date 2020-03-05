#ifndef All_HEADER_IN_ONE_FILE
#define All_HEADER_IN_ONE_FILE

#include <iostream>
#include "UsefulFeatures.h"
#include "Menu.h"
#include "Classes.h"

using std::cout;
using std::endl;

enum class Mode {
	FIXEDSIZE,
	VECTOR,
	LINKEDLIST
};

void StartMenu();


#endif // !All_HEADER_IN_ONE_FILE
