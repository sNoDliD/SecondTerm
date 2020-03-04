#include "Header.h"


#pragma region Declaration

static int ChoiceMode();
static int Interactive(int mode);

static bool ShopMenuCreate();
static int ShopChoice();
static int ShopCreate();
static int ShopFind(); 
static int DeleteAllShop();

static int Add();

static int ShowAll();

static int Search();
static size_t SearchName();
static size_t SearchAmount();
static size_t SearchDate();

static int Delete();

static int Modify();

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
	Initialization();

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
	SetWorkMode(Mode(mode));
	if (!ShopMenuCreate()) return (int)MenuMode::REPEATE;

	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Add", Add));
	all->push_back(MenuItem("Show all", ShowAll));
	all->push_back(MenuItem("Search", Search));
	all->push_back(MenuItem("Modify", Modify));
	all->push_back(MenuItem("Delete", Delete));

	Menu* menu = new Menu("Interactive mode", all);
	menu->DoMenu();
	delete menu;

	return (int)MenuMode::REPEATE;
}

#pragma endregion


#pragma region Shop

bool AllProductCorrect(Date& date) {
	int index = SetIndex(WorkMode(), {Mode::VECTOR, Mode::BIN});
	auto Func = SwitchFunc(index, {TakeProductVector, TakeProductBin});
	size_t i = 0;
	while(true)
		if (Func) {
			Product* product = Func(i++);
			if (product == nullptr) break;
			if (product->date < date) {
				delete product;
				return false;
			}
			delete product;
		}
		else {
			ProductString* product = TakeProductTxt(i++);
			if (product == nullptr) break;
			if (product->date < date) {
				delete product;
				return false;
			}
			delete product;
		}
	return true;
}

bool ShopMenuCreate() {
	vector <MenuItem>* all = new vector<MenuItem>;
	all->push_back(MenuItem("Find shop", ShopFind));
	all->push_back(MenuItem("Choose shop", ShopChoice));
	all->push_back(MenuItem("Create new", ShopCreate));
	all->push_back(MenuItem("Delete all", DeleteAllShop));

	Menu* menu = new Menu("Choose or create shop:", all);
	int shopId = menu->DoMenu();
	delete menu;
	if (shopId == (int)MenuMode::EXIT)
		return false;

	SetShop(shopId);

	cout << "Wait for initialization..." << endl;
	auto Func = SwitchFunc((int)WorkMode() - 1, { CreatePathTxt, CreatePathBin });
	if (Func != nullptr)
		Func(to_string(ShopId()).c_str());
	else ReorganizeVector();

	return true;
}

int ShopFind() {
	Store* store = TakeStore(0);
	if(store != nullptr) {
		delete store;
		char name[g_nameSize];
		SetValue("Enter part of store's name: ", name);
		Date date;
		cout << "Enter min date of creation: ";
		InputStr(date, true);
		vector <MenuItem>* all = new vector<MenuItem>;
		size_t i = 0;

		while (true) {
			Store* store = TakeStore(i++);
			if (store == nullptr) break;
			if (SubString(store->name, name) && AllProductCorrect(date))
				all->push_back(MenuItem(store->name, nullptr, store->id));
			delete store;
		}
		if (all->size() != 0) {
			Menu* menu = new Menu("Choose your shop:", all);
			int result = menu->DoMenu();
			delete menu;
			if (result == (int)MenuMode::EXIT)
				return (int)MenuMode::REPEATE;
			return result;
		}
	}
	system("cls");
	cout << "Don't find any shops. Create new...\n\n";
	system("pause");
	return ShopCreate();
}

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
		if (result == (int)MenuMode::EXIT)
			return (int)MenuMode::REPEATE;
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
			FreeShopBin(newStore->id);
			FreeShopTxt(newStore->id);
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
		FreeShopBin(newStore->id);
		FreeShopTxt(newStore->id);
	}
	cout << "\nSuccess" << endl;
	delete newStore;
	system("pause");
	return (int)MenuMode::REPEATE;
}

int DeleteAllShop() {
	system("cls");
	if (FreeShops(g_storeBase)) {
		cout << "All shops delete...\n";
	}
	else
		cout << "Fail of delete shops...\n";
	system("pause");
	return (int)MenuMode::REPEATE;
}

#pragma endregion


#pragma region Add

template <typename Tproduct>
static bool InputProduct(Tproduct* newProduct) {
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

bool AddSelf() {
	bool isAdded = false;

	switch (WorkMode()) {
	case Mode::VECTOR:
	case Mode::BIN: {
		Product* newProduct = new Product();
		if (InputProduct(newProduct)) {
			int index = SetIndex(WorkMode(), { Mode::VECTOR, Mode::BIN });
			if(SwitchFunc(index, { AppendProductVector, AppendProductBin })(newProduct) == false)
				SetColor(6, "Shop is full!\n");
			else 
				cout << newProduct->ToString() << endl;
			isAdded = true;
		}
		delete newProduct;
	}
				  break;
	case Mode::TXT: {
		ProductString* newProduct = new ProductString();
		if (InputProduct(newProduct)) {
			if (AppendProductTxt(newProduct) == false)
				SetColor(6, "Shop is full!\n");
			else
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
		if (SwitchFunc((int)WorkMode(), { AddVectorRandom, AddTxtRandom, AddBinRandom })(n) == false)
			SetColor(6, "Shop is full!\n");
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
	if (WorkMode() == Mode::TXT)
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

	size_t totalFind = 0;
	if (WorkMode() == Mode::TXT)
		totalFind = ShowByCondition<ProductString>(IsSubName, name);
	else
		totalFind = ShowByCondition<Product>(IsSubName, name);
	return totalFind;
}

size_t SearchAmount() {
	float count;
	SetValue("Enter min count of product: ", count, Positive, "\tIncorrect input. Count > 0!");

	size_t totalFind = 0;
	if (WorkMode() == Mode::TXT)
		totalFind = ShowByCondition<ProductString>(IsMore, count);
	else
		totalFind = ShowByCondition<Product>(IsMore, count);
	return totalFind;
}

size_t SearchDate() {
	cout << "Enter data to find products that will die\nDay.Mounth.Year(1.4.2020): ";
	Date date;
	InputStr(date, true);

	size_t totalFind = 0;
	if (WorkMode() == Mode::TXT)
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

	if (type == (int)MenuMode::EXIT) 
		return (int)MenuMode::REPEATE;
	
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
static bool ModifyField(Tproduct* product, int field) {
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
static bool ModifySet(size_t id) {
	bool modifySuccess = false;
	vector <MenuItem>* all = new vector<MenuItem>;
	Tproduct* product;

	if (WorkMode() == Mode::TXT)
		product = (Tproduct*)TakeProductTxt(id - 1);
	else if (WorkMode() == Mode::BIN)
		product = (Tproduct*)TakeProductBin(id - 1);
	else product = (Tproduct*)TakeProductVector(id - 1);
	if (product == nullptr || product->id == 0) {
		if (product && WorkMode() != Mode::VECTOR) delete product;
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
		if (WorkMode() == Mode::TXT)
			ModifyTxt(id, (ProductString*)product);
		else if (WorkMode() == Mode::BIN)
			ModifyBin(id, (Product*)product);
		cout << "\n" << product->ToString();
	}
	if (WorkMode() != Mode::VECTOR) delete product;

	return modifySuccess;
}

int Modify() {
	size_t id;
	SetValue("Enter id of product: ", id);
	bool modifySuccess = false;

	if (WorkMode() == Mode::TXT)
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
	bool deleteSuccess = SwitchFunc((int)WorkMode(), { DeleteVector, DeleteTxt, DeleteBin })(id);
	if (deleteSuccess)
		cout << "\n\nSuccess" << endl;
	else
		cout << "\n\nFailed to delete product." << endl;
	system("pause");
	return (int)MenuMode::REPEATE;
}
