#include "Header.h"


#pragma region Declaration

using std::to_string;

int ChoiceMode();
int Interactive(int mode);
int Demonstration();
int Benchmark();

int ShopChoice();
int ShopCreate();
int ShopFind();

int Add();

int ShowAll();

int Search();
size_t SearchName();
size_t SearchAmount();
size_t SearchDate();

int Delete();

int Modify();

static Store g_store;
static Mode g_mode = Mode::WAIT;
size_t ShopId() {
	return g_store.id;
}
size_t ShopMaxCount() {
	return g_store.maxProductCount;
}

#pragma endregion


#pragma region Template

template <typename Tproduct, typename T>
bool IsSubName(Tproduct* product, T& str) {
	bool deletedProduct = product->id == 0 || product->storeId != ShopId();
	if (!deletedProduct && SubString(product->name, str))
		return true;
	return false;
}

template <typename Tproduct, typename T>
bool IsMore(Tproduct* product, T& count) {
	bool deletedProduct = product->id == 0 || product->storeId != ShopId();
	if (!deletedProduct && product->count >= count)
		return true;
	return false;
}

template <typename Tproduct>
bool IsDied(Tproduct* product, Date& date) {
	bool deletedProduct = product->id == 0 || product->storeId != ShopId();
	if (!deletedProduct && product->date.DaysBetween(date) >= product->expirationDate )
		return true;
	return false;
}

template <typename Tproduct, typename... T>
size_t ShowByCondition(bool (*Condition)(Tproduct*,T&...) = nullptr,T&... data) {
	size_t totalFind = 0, i = 0;
	int index = SetIndex(g_mode, { Mode::VECTOR, Mode::BIN });
	auto TakeProduct = SwitchFunc(index, { TakeProductVector, TakeProductBin });
	Tproduct* product;

	while (true) {
		if (TakeProduct)
			product = (Tproduct*)TakeProduct(i++);
		else
			product = (Tproduct*)TakeProductTxt(i++);

		if (product == nullptr) break;
		bool deletedProduct = product->id == 0 || product->storeId != ShopId();
		if (!deletedProduct && (Condition == nullptr || Condition(product, data...))) {
			cout << product->ToString() << endl;
			totalFind++;
		}
		if(g_mode != Mode::VECTOR) delete product;
	}
	return totalFind;
}

template <typename Tproduct>
bool InputProduct(Tproduct* newProduct) {
	SetValue("Enter product's name: ", newProduct->name);
	Capitalize(newProduct->name);
	SetValue("Enter product's date in format day.mount.year hours:minutes (15.02.2002 21:10)\n", newProduct->date);
	SetValue("Enter product's expiration days: ", newProduct->expirationDate);
	if (!SetValue("Choose units of product", newProduct->units)) return false;
	SetValue(newProduct->count, newProduct->units);
	newProduct->storeId = ShopId();

	system("cls");

	return true;
}

#pragma endregion


#pragma region Start

int StartMenu() {

	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Interactive", ChoiceMode));
	all->push_back(MenuItem("Demonstration", Demonstration));
	all->push_back(MenuItem("Benchmark", Benchmark));

	Menu* menu = new Menu("Choose your mode:", all);
	menu->DoMenu();
	delete menu;

	return (int)MenuMode::EXIT;
}

int ChoiceMode() {
	vector<MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Vector", Interactive, (int)Mode::VECTOR));
	all->push_back(MenuItem("Text", Interactive, (int)Mode::TXT));
	all->push_back(MenuItem("Binary", Interactive, (int)Mode::BIN));

	Menu* menu = new Menu("Choose your read/write mode", all);
	menu->DoMenu();
	delete menu;

	return (int)MenuMode::REPEATE;
}

int Interactive(int mode) {
	g_mode = Mode(mode);

	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Find shop", ShopFind));
	all->push_back(MenuItem("Choose shop", ShopChoice));
	all->push_back(MenuItem("Create new", ShopCreate));

	Menu* menu = new Menu("Choose or create shop:", all);
	int shopId = menu->DoMenu();
	delete menu;

	if (shopId == (int)MenuMode::EXIT)
		return (int)MenuMode::REPEATE;

	Store* shopChoice = TakeStore(shopId - 1);
	g_store = *shopChoice;
	delete shopChoice;

	cout << "Wait for initialization..." << endl;
	auto Func = SwitchFunc((int)g_mode - 1, { CreatePathTxt, CreatePathBin });
	if (Func != nullptr)
		Func(to_string(ShopId()).c_str());

	all = new vector<MenuItem>;
	all->push_back(MenuItem("Add", Add));
	all->push_back(MenuItem("Show all", ShowAll));
	all->push_back(MenuItem("Search", Search));
	all->push_back(MenuItem("Modify", Modify));
	all->push_back(MenuItem("Delete", Delete));

	menu = new Menu("Interactive mode", all);
	menu->DoMenu();
	delete menu;

	return (int)MenuMode::REPEATE;
}

int Demonstration() {
	Menu* menu = new Menu("Demonstration...");
	menu->DoMenu();
	delete menu;
	return (int)MenuMode::REPEATE;
}

int Benchmark() {
	Menu* menu = new Menu("Benchmark...");
	menu->DoMenu();
	delete menu;
	return (int)MenuMode::REPEATE;
}

#pragma endregion


#pragma region Shop

int ShopChoice() {
	vector <MenuItem>* all = new vector<MenuItem>;
	size_t i = 0;
	while (true) {
		Store* a = TakeStore(i++);
		if (a == nullptr) break;
		all->push_back(MenuItem(a->name, nullptr, a->id));
		delete a;
	}

	if (all->size() == 0) {
		cout << "Don't find any shops. Create new...\n\n";
		system("pause");
		delete all;
		return ShopCreate();
	}
	else {
		Menu* menu = new Menu("Choose your shop:", all);
		int result = menu->DoMenu();
		delete menu;

		return result;
	}
}

int ShopCreate() {
	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Random", nullptr, 1));
	all->push_back(MenuItem("Yourself", nullptr, 2));

	Menu* menu = new Menu("Fill type:", all);
	int type = menu->DoMenu();
	delete menu;

	if (type == (int)MenuMode::EXIT)
		return (int)MenuMode::REPEATE;

	Store* newStore = new Store();
	if (type == 1) {
		size_t n;
		SetValue("Enter count of add stores: ", n);
		for (size_t i = 0; i < n; i++) {
			newStore->Randomaze();
			AppendStore(newStore);
			cout << '\n' << newStore->ToString() << '\n';
		}
	}
	else {
		SetValue("Enter shop's name: ", newStore->name);
		Capitalize(newStore->name);
		SetValue("Enter shop's adress: ", newStore->adress);
		SetValue("Enter shop's rating: ", newStore->rating, ZeroToTen, 
			"\tRating should be in interval [0,10]. Try again\n");
		SetValue("Enter shop's maximum of product count: ", newStore->maxProductCount);
		AppendStore(newStore);
		cout << '\n' << newStore->ToString() << '\n';
	}
	cout << "\nSuccess" << endl;
	delete newStore;
	system("pause");
	return (int)MenuMode::REPEATE;
}

int ShopFind() {
	Store* a = TakeStore(0);
	if (a == nullptr) {
		cout << "Don't find any shops. Create new...\n\n";
		system("pause");
		return ShopCreate();
	}
	else {
		//Магазини із заданим фрагментом тексту в назві, в яких всі товари
		//	мають термін виробництва не раніше заданого.
		char name[nameSize];
		SetValue("Enter part of store's name: ", name);
		Date date;
		SetValue("Enter min date of creation: ", date);
		vector <MenuItem>* all = new vector<MenuItem>;
		int i = 0;
		while (true) {
			Store* a = TakeStore(i++);
			if (a == nullptr) break;
			if (SubString(a->name, name)) {
				//switch g_mode
				//read all product while !product.date < date
				all->push_back(MenuItem(a->name, nullptr, a->id));
			}
			delete a;
		}
		if (i == 0) {
			cout << "i == 0";
			system("pause");
		}
		Menu* menu = new Menu("Choose your shop:", all);
		int result = menu->DoMenu();
		delete menu;

		return result;
	}



	return (int)MenuMode::REPEATE;
}

#pragma endregion


#pragma region Add

bool AddSelf() {
	bool isAdded = false;

	switch (g_mode) {
	case Mode::VECTOR:
	case Mode::BIN: {
		Product* newProduct = new Product();
		if (InputProduct(newProduct)) {
			int index = SetIndex(g_mode, { Mode::VECTOR, Mode::BIN });
			SwitchFunc(index, { AppendProductVector, AppendProductBin })(newProduct);
			cout << newProduct->ToString() << endl;
			isAdded = true;
		}
		delete newProduct;
	}
				  break;
	case Mode::TXT: {
		ProductString* newProduct = new ProductString();
		if (!InputProduct(newProduct)) {
			AppendProductTxt(newProduct);
			cout << newProduct->ToString() << endl;
			isAdded = true;
		}
		delete newProduct;
	}
				  break;
	default:
		throw - 3;
	}
	return isAdded;
}

int Add() {
	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Random", nullptr, 1));
	all->push_back(MenuItem("Yourself", nullptr, 2));

	Menu* menu = new Menu("Fill type:", all);
	int type = menu->DoMenu();
	delete menu;

	if (type == (int)MenuMode::EXIT)
		return (int)MenuMode::REPEATE;

	if (type == 1) {
		size_t n;
		SetValue("Enter count of add products: ", n);
		SwitchFunc((int)g_mode, { AddVectorRandom, AddTxtRandom, AddBinRandom })(n);
	}
	else if (!AddSelf())
		return (int)MenuMode::REPEATE;
	cout << "\nSuccess" << endl;
	system("pause");
	return (int)MenuMode::REPEATE;
}

#pragma endregion


int ShowAll() {
	size_t totalFind = 0;
	if (g_mode == Mode::TXT)
		totalFind = ShowByCondition<ProductString>();
	else
		totalFind = ShowByCondition<Product>();
	if (totalFind == 0)
		cout << "Store is empty\n\n";
	else
		cout << "Total find " << totalFind << " products\n\n";
	system("pause");
	return (int)MenuMode::REPEATE;
}


#pragma region Search

size_t SearchName() {
	cout << "Enter substring for name: ";
	string name;
	InputStr(name);
	system("cls");

	size_t totalFind = 0;
	if (g_mode == Mode::TXT)
		totalFind = ShowByCondition<ProductString>(IsSubName, name);
	else
		totalFind = ShowByCondition<Product>(IsSubName, name);
	return totalFind;
}

size_t SearchAmount() {
	float count;
	SetValue("Enter min count of product: ", count, Positive, "\tIncorrect input. Count > 0!");
	system("cls");

	size_t totalFind = 0;
	if (g_mode == Mode::TXT)
		totalFind = ShowByCondition<ProductString>(IsMore, count);
	else
		totalFind = ShowByCondition<Product>(IsMore, count);
	return totalFind;
}

size_t SearchDate() {
	cout << "Enter data to find products that will die\nDay.Mounth.Year(1.4.2020): ";
	Date date;
	InputStr(date, true);
	system("cls");

	size_t totalFind = 0;
	if (g_mode == Mode::TXT)
		totalFind = ShowByCondition<ProductString>(IsDied, date);
	else
		totalFind = ShowByCondition<Product>(IsDied, date);
	return totalFind;
}

int Search() {
	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("By name", nullptr, 1));
	all->push_back(MenuItem("By amount", nullptr, 2));
	all->push_back(MenuItem("By date", nullptr, 3));

	Menu* menu = new Menu("Search type:", all);
	int type = menu->DoMenu();
	delete menu;

	if (type == (int)MenuMode::EXIT) return (int)MenuMode::REPEATE;
	
	size_t totalFind = SwitchFunc(type, { SearchName, SearchAmount, SearchDate})();
	if (totalFind == 0) 
		cout << "Nothing found\n\n";
	else 
		cout << "Total find " << totalFind << " products\n\n";
	system("pause");
	return (int)MenuMode::REPEATE;
}

#pragma endregion 


#pragma region Modify

template <typename Tproduct>
bool ModifyField(Tproduct* product, int field) {
	switch (field) {
	case 1:
		SetValue("Enter new product's name: ", product->name);
		break;
	case 2:
		SetValue(product->count, product->units);
		break;
	case 3: {
		bool isSet = SetValue("Enter new product's type: ", product->units);
		if (product->units == Units::BAG || product->units == Units::PIECE)
			product->count = trunc(product->count);
		return isSet;
	}
	case 4:
		SetValue("Enter new product's date: ", product->date);
		break;
	case 5:
		SetValue("Enter new product's life time: ", product->expirationDate);
	}

	return true;
}

template <typename Tproduct>
bool ModifySet(size_t id) {
	bool modifySuccess = false;
	vector <MenuItem>* all = new vector<MenuItem>;
	Tproduct* product;

	if (g_mode == Mode::TXT)
		product = (Tproduct*)TakeProductTxt(id - 1);
	else if (g_mode == Mode::BIN)
		product = (Tproduct*)TakeProductBin(id - 1);
	else product = (Tproduct*)TakeProductVector(id - 1);
	if (product == nullptr || product->id == 0) {
		if (product && g_mode != Mode::VECTOR) delete product;
		delete all;
		return false;
	}

	all->push_back(MenuItem("Name: " + string(product->name), nullptr, 1));
	all->push_back(MenuItem("Amount: " + FloatToString(product->count), nullptr, 2));
	all->push_back(MenuItem("Type: " + string(UnitsToString((int)product->units)), nullptr, 3));
	all->push_back(MenuItem("Date: " + product->date.ToString(), nullptr, 4));
	all->push_back(MenuItem("Life time: " + to_string(product->expirationDate), nullptr, 5));

	Menu* menu = new Menu("Select a field to change: ", all);
	int result = menu->DoMenu();
	delete menu;

	if (result == (int)MenuMode::EXIT) return false;
	modifySuccess = ModifyField(product, result);
	if (modifySuccess) {
		if (g_mode == Mode::TXT)
			ModifyTxt(id, (ProductString*)product);
		else if (g_mode == Mode::BIN)
			ModifyBin(id, (Product*)product);
		cout << "\n" << product->ToString();
	}
	if (g_mode != Mode::VECTOR) delete product;

	return modifySuccess;
}

int Modify() {
	size_t id;
	SetValue("Enter id of product: ", id);
	bool modifySuccess = false;

	if (g_mode == Mode::TXT)
		modifySuccess = ModifySet<ProductString>(id);
	else 
		modifySuccess = ModifySet<Product>(id);

	if (modifySuccess)
		cout << "\n\nSuccess" << endl;
	else
		cout << "\n\nFailed to modify product." << endl;
	system("pause");
	return (int)MenuMode::REPEATE;
}

#pragma endregion


int Delete() {
	size_t id;
	cout << "Enter id of product: ";
	InputStr(id);
	bool deleteSuccess = SwitchFunc((int)g_mode, { DeleteVector, DeleteTxt, DeleteBin })(id);
	if (deleteSuccess)
		cout << "\n\nSuccess" << endl;
	else
		cout << "\n\nFailed to delete product." << endl;
	system("pause");
	return (int)MenuMode::REPEATE;
}
