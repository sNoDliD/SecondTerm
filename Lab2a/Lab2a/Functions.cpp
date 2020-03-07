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
		std::cin.ignore(UINT16_MAX, '\n');
		SetColor(6, "\tIncorrect input. Enter value [", leftBorder, ",", rightBorder, "]\n");
		std::cin >> str;
	}
	std::cin.clear();
	std::cin.ignore(UINT16_MAX, '\n');
}

IP InputIP(size_t choice){
	Menu menu("How add IP:", { 
		MenuItem("Random", nullptr, 1),
		MenuItem("Yourself", nullptr, 2) },
		"");

	int result = menu.DoMenu({ choice });
	while (result == (int)MenuMode::EXIT)
		result = menu.DoMenu();

	if (result == 1) {
		IP result = RandomIP();
		cout << to_string(result) << endl;
		return result;
	}
	else {
		int a, b, c, d;
		cout << "Input IPv4 (255.255.255.255):\n";
		if (choice == 2) {
			IP result = RandomIP();
			SleepPrint(to_string(result), coutSleep, coutPause);
			return result;
		}
		while (true) {
			if (scanf_s("%d.%d.%d.%d", &a, &b, &c, &d) == 4) {
				if (!(a < 0 || b < 0 || c < 0 || d < 0 ||
					a > 255 || b > 255 || c > 255 || d > 255)) {
					std::cin.ignore(UINT16_MAX, '\n');
					return IP(a, b, c, d);
				}
					
			}
			std::cin.ignore(UINT16_MAX, '\n');
			SetColor(6, "\tIncorrect input. Try again\n");
		}
	}
	throw "Unreachable code";
}
