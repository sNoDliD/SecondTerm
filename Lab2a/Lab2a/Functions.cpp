//#include "Header.h"
//#include <fstream>
//
//using std::ifstream;
//using std::ofstream;
//
//void Initialization() {
//	cout << "Wait for initialization..." << endl;
//	CreatePathStore(g_storeBase);
//	srand((unsigned int) time(0));
//}
//
//void MemoryFree() {
//	DeletePathBin();
//}
//
//void Capitalize(string& str) {
//	size_t len = str.length();
//	if (len < 1) return;
//	str[0] = toupper(str[0]);
//	for (size_t i = 1; i < len; i++)
//		str[i] = tolower(str[i]);
//}
//
//void Capitalize(char* str) {
//	size_t len = strlen(str);
//	if (len < 1) return;
//	str[0] = toupper(str[0]);
//	for (size_t i = 1; i < len; i++)
//		str[i] = tolower(str[i]);
//}
//
//bool SubString(const char* main, const char* compare) {
//	size_t mainLen = strlen(main), compareLen = strlen(compare);
//	if (compareLen == 0) return true;
//	if (mainLen < compareLen) return false;
//
//	for (size_t i = 0; i <= mainLen - compareLen; i++) {
//		bool result = true;
//		for (size_t j = 0; j < compareLen; j++)
//			if (tolower(main[i + j]) != tolower(compare[j])) {
//				result = false;
//				break;
//			}
//		if (result == false) continue;
//		return true;
//	}
//	return false;
//}
//
//bool SubString(const string& main, const string& compare) {
//	if (compare == "") return true;
//	size_t mainLen = main.length(), compareLen = compare.length();
//	if (mainLen < compareLen) return false;
//
//	for (size_t i = 0; i <= mainLen - compareLen; i++) {
//		bool result = true;
//		for (size_t j = 0; j < compareLen; j++)
//			if (tolower(main[i + j]) != tolower(compare[j])) {
//				result = false;
//				break;
//			}
//		if (result == false) continue;
//		return true;
//	}
//	return false;
//}
//
//void StringRandom(string& str, size_t minSize, size_t maxSize) {
//	str = "";
//	if (minSize > maxSize)
//		minSize = 0;
//	size_t len = rand() % (maxSize - minSize + 1) + minSize;
//	for (size_t i = 0; i < len; i++)
//		str += rand() % ('z' - 'a') + 'a';
//}
//
//void StringRandom(char* str, size_t minSize, size_t maxSize) {
//	if (minSize > maxSize - 1)
//		minSize = 0;
//	size_t len = rand() % (maxSize - minSize) + minSize;
//	for (size_t i = 0; i < len; i++)
//		str[i] = rand() % ('z' - 'a') + 'a';
//	str[len] = '\0';
//
//}
//
//const char* UnitsToString(int unitId) {
//	switch (Units(unitId)){
//	case Units::PIECE:
//		return "pieces";
//	case Units::KILOGRAMMS:
//		return "kilogramms";
//	case Units::LITERS:
//		return "litters";
//	case Units::BAG:
//		return "bags";
//	default:
//		throw - 2;
//	}
//}
//
//bool ClearIfBreak(bool condition) {
//	if (cin.fail() || condition) {
//		cin.clear();
//		cin.ignore(INT64_MAX, '\n');
//		return true;
//	}
//	return false;
//}
//
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
//
//void InputStr(size_t& str){
//	long long temp;
//	cin >> temp;
//	while (ClearIfBreak(temp < 1 || temp > UINT32_MAX)) {
//		SetColor(6, "\tIncorrect input. Enter value [1,", UINT32_MAX, "]\n");
//		cin >> temp;
//	}
//	ClearIfBreak(true);
//	str = (size_t)temp;
//}
//
//void InputStr(byte2& str){
//	int temp;
//	cin >> temp;
//	while (ClearIfBreak(temp < 1 || temp > UINT16_MAX)) {
//		SetColor(6, "\tIncorrect input. Enter value [1,", UINT16_MAX, "]\n");
//		cin >> temp;
//	}
//	ClearIfBreak(true);
//	str = (byte2)temp;
//}
//
//void InputStr(string& str){
//	getline(cin, str);
//	if (str.size() == 0) {
//		SetColor(6, "\tIt's not a word\n");
//		InputStr(str);
//	}
//}
//
//string FloatToString(float str, size_t accuracy) {
//	if (accuracy > 6) accuracy = 6;
//	if (str < 0) return "-" + FloatToString(-str, accuracy);
//	float up = roundf(str * (float)pow(10, accuracy));
//	if (up == 0) return "0";
//
//	string result = std::to_string(up);
//	while (result.back() == '0') result.pop_back();
//	if (result.back() == '.') result.pop_back();
//
//	int over = result.size() - accuracy - 1;
//	while (over++ < 0) result.insert(0, "0");
//	result.insert(result.size() - accuracy, ".");
//
//	while (result.back() == '0') result.pop_back();
//	if (result.back() == '.') result.pop_back();
//	return result;
//}
//
//bool SetValue(const char* preMessage, Units& value){
//	vector <MenuItem>* all = new vector<MenuItem>;
//	all->push_back(MenuItem("Bag", nullptr, (int)Units::BAG));
//	all->push_back(MenuItem("Kilogramms", nullptr, (int)Units::KILOGRAMMS));
//	all->push_back(MenuItem("Liters", nullptr, (int)Units::LITERS));
//	all->push_back(MenuItem("Piece", nullptr, (int)Units::PIECE));
//
//	Menu* menu = new Menu(preMessage, all);
//	int unitId = menu->DoMenu();
//	delete menu;
//
//	if (unitId == (int)MenuMode::EXIT) return false;
//	value = Units(unitId);
//	return true;
//}
//
//void SetValue(float& value, Units& units){
//	cout << "Enter product's count in " << UnitsToString((int)units) << ": ";
//	InputStr(value);
//	if (units == Units::BAG || units == Units::PIECE)
//		value = trunc(value);
//}
