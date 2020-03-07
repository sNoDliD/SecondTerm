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


void SleepPrint(std::string str, size_t printPause, size_t pause) {
	Sleep(pause);
	for (auto a : str) {
		std::cout << a;
		Sleep(printPause);
	}
	Sleep(pause);
	std::cout << std::endl;
}