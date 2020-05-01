#include "Header.h"


#pragma region Declaration

static int ChoiceMode();
static int Interactive(int mode);

static bool ShopMenuCreate();
static int ShopFind(); 
static int ShopChoice();
static int ShopCreate();
static int DeleteAllShop();

static int Add();

static int ShowAll();

static int Search();
static size_t SearchName();
static size_t SearchAmount();
static size_t SearchDate();

static int Delete();

static int Modify();

static const size_t g_coutSleep = 80;
static const size_t g_pauseSleep = 1200;

#pragma endregion


#pragma region ForDemonstration

static void PrintWithSleep(const char* preMessage, string str) {
	cout << preMessage;
	for (char c : str) {
		Sleep(g_coutSleep);
		cout << c;
	}
	Sleep(g_pauseSleep);
	cout << "\n(Perfect)\n\n";
}

static bool SetValue(const char* preMessage, Units& value) {
	Menu menu(preMessage, {
		MenuItem("Bag", nullptr, (int)Units::BAG),
		MenuItem("Kilogramms", nullptr, (int)Units::KILOGRAMMS),
		MenuItem("Liters", nullptr, (int)Units::LITERS),
		MenuItem("Piece", nullptr, (int)Units::PIECE)
		});
	size_t choice = rand() % 4 + 1;
	int unitId = menu.DoMenu({ choice });

	if (unitId == (int)MenuMode::EXIT) return false;
	value = Units(unitId);
	return true;
}

static void SetValue(float& value, Units& units) {
	cout << "Enter product's count in " << UnitsToString((int)units) << ": ";
	value = rand() % 1000 + (float)(rand() % 100) / 100;
	PrintWithSleep("", FloatToString(value));
	if (units == Units::BAG || units == Units::PIECE)
		value = trunc(value);
}

#pragma endregion


#pragma region Start

int Demonstration() {
	Initialization();

	Menu menu("Choose your read/write mode", {
		MenuItem("Vector", Interactive, (int)Mode::VECTOR),
		MenuItem("Text", Interactive, (int)Mode::TXT),
		MenuItem("Binary", Interactive, (int)Mode::BIN)
		});
	menu.DoMenu({ 2,1,3 });

	return (int)MenuMode::REPEATE;
}

int Interactive(int mode) {
	SetWorkMode(Mode(mode));
	if (!ShopMenuCreate()) return (int)MenuMode::REPEATE;

	Menu menu("Interactive mode", {
		MenuItem("Add", Add),
		MenuItem("Show all", ShowAll),
		MenuItem("Search", Search),
		MenuItem("Modify", Modify),
		MenuItem("Delete", Delete)
		});
	menu.DoMenu({ 2, 1, 2, 5, 5, 4, 4, 4, 2, 1, 3 });

	return (int)MenuMode::REPEATE;
}

#pragma endregion


#pragma region Shop

int DeleteAllShop() {
	system("cls");
	if (FreeShops(g_storeBase)) {
		cout << "All shops delete...\n";
	}
	else
		cout << "Fail of delete shops...\n";
	Sleep(g_pauseSleep);
	return (int)MenuMode::REPEATE;
}

bool ShopMenuCreate() {
	Menu menu("Choose or create shop:", {
		MenuItem("Find shop", ShopFind),
		MenuItem("Choose shop", ShopChoice),
		MenuItem("Create new", ShopCreate),
		MenuItem("Delete all", DeleteAllShop)
		});
	int shopId = menu.DoMenu({4, 2, 3, 1, 2});

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

int ShopChoice() {
	vector <MenuItem> all;
	size_t i = 0;
	while (true) {
		Store* a = TakeStore(i++);
		if (a == nullptr) break;
		all.push_back(MenuItem(a->name, nullptr, a->id));
		delete a;
	}

	if (all.size() == 0) {
		cout << "Don't find any shops. Create new...\n\n";
		Sleep(g_pauseSleep);

		return ShopCreate();
	}
	size_t choice = rand() % all.size() + 1;
	Menu menu("Choose your shop:", all);
	int result = menu.DoMenu({ choice });

	return result;
}

int ShopCreate() {
	vector<size_t> order = { 1,2 };
	while (true) {
		if (order.size() == 0) break;

		Menu menu("Fill type:", {
			MenuItem("Random", nullptr, 1),
			MenuItem("Yourself", nullptr, 2)
			});
		int type = menu.DoMenu({ order[0] });
		order.erase(order.begin(), order.begin() + 1);

		if (type == (int)MenuMode::EXIT)
			return (int)MenuMode::REPEATE;

		Store* newStore = new Store();
		if (type == 1) {
			size_t n = rand() % 3 + 1;
			PrintWithSleep("Enter count of add stores: ",FloatToString((float)n));
			for (size_t i = 0; i < n; i++) {
				newStore->Randomaze();
				AppendStore(newStore);
				cout << '\n' << newStore->ToString() << '\n';
				FreeShopBin(newStore->id);
				FreeShopTxt(newStore->id);
			}
		}
		else {
			newStore->Randomaze();
			PrintWithSleep("Enter shop's name: ", newStore->name);
			PrintWithSleep("Enter shop's adress: ", newStore->adress);
			PrintWithSleep("Enter shop's rating: ", FloatToString(newStore->rating));
			PrintWithSleep("Enter shop's maximum of product count: ", FloatToString((float)newStore->maxProductCount));
			AppendStore(newStore);
			cout << '\n' << newStore->ToString() << '\n';
			FreeShopBin(newStore->id);
			FreeShopTxt(newStore->id);
		}
		cout << "\nSuccess" << endl;
		delete newStore;
		Sleep(g_pauseSleep);
	}
	return (int)MenuMode::REPEATE;
}

int ShopFind() {
	Store* store = TakeStore(0);
	if (store != nullptr) {
		delete store;
		char name[g_nameSize];
		StringRandom(name, 2, 6);
		PrintWithSleep("Enter part of store's name: ", name);
		Date date;
		date.Randomaze();
		PrintWithSleep("Enter min date of creation: ", date.ToString());
		vector <MenuItem> all;
		size_t i = 0;

		while (true) {
			Store* store = TakeStore(i++);
			if (store == nullptr) break;
			if (SubString(store->name, name) && AllProductCorrect(date))
				all.push_back(MenuItem(store->name, nullptr, store->id));
			delete store;
		}
		if (all.size() != 0) {
			size_t choice = rand() % all.size() + 1;
			Menu menu("Choose your shop:", all);
			int result = menu.DoMenu({choice});

			return result;
		}
	}
	system("cls");
	cout << "Don't find any shops. Create new...\n\n";
	Sleep(g_pauseSleep);
	return ShopCreate();
}

#pragma endregion


#pragma region Add

template <typename Tproduct>
static bool InputProduct(Tproduct* newProduct) {
	newProduct->Randomaze();
	PrintWithSleep("Enter product's name: ", newProduct->name);
	PrintWithSleep("Enter product's date in format day.mount.year hours:minutes (15.02.2002 21:10)\n", newProduct->date.ToString());
	PrintWithSleep("Enter product's expiration days: ", FloatToString(newProduct->expirationDate));
	if (!SetValue("Choose units of product", newProduct->units)) return false;
	SetValue(newProduct->count, newProduct->units);
	newProduct->storeId = ShopId();

	system("cls");

	return true;
}

static bool AddSelf() {
	bool isAdded = false;

	switch (WorkMode()) {
	case Mode::VECTOR:
	case Mode::BIN: {
		Product* newProduct = new Product();
		if (InputProduct(newProduct)) {
			int index = SetIndex(WorkMode(), { Mode::VECTOR, Mode::BIN });
			if (SwitchFunc(index, { AppendProductVector, AppendProductBin })(newProduct) == false)
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
	vector<size_t> order = { 1,2 };
	while (true) {
		if (order.size() == 0) break;

		Menu menu("Fill type:", {
			MenuItem("Random", nullptr, 1),
			MenuItem("Yourself", nullptr, 2)
			});
		int type = menu.DoMenu({ order[0] });
		order.erase(order.begin(), order.begin() + 1);


		if (type == (int)MenuMode::EXIT)
			return (int)MenuMode::REPEATE;

		if (type == 1) {
			size_t n = rand() % 40 + 10;
			PrintWithSleep("Enter count of add products: ", FloatToString(n));
			if (SwitchFunc((int)WorkMode(), { AddVectorRandom, AddTxtRandom, AddBinRandom })(n) == false)
				SetColor(6, "Shop is full!\n");
		}
		else if (!AddSelf())
			return (int)MenuMode::REPEATE;
		cout << "\nSuccess" << endl;
		Sleep(g_pauseSleep);
	}
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
	Sleep(g_pauseSleep);
	return (int)MenuMode::REPEATE;
}


#pragma region Search

size_t SearchName() {
	string name;
	StringRandom(name, 3, 6);
	PrintWithSleep("Enter substring for name: ", name);

	size_t totalFind = 0;
	if (WorkMode() == Mode::TXT)
		totalFind = ShowByCondition<ProductString>(IsSubName, name);
	else
		totalFind = ShowByCondition<Product>(IsSubName, name);
	return totalFind;
}

size_t SearchAmount() {
	float count = rand() % 500 + 500;
	PrintWithSleep("Enter min count of product: ",FloatToString(count));

	size_t totalFind = 0;
	if (WorkMode() == Mode::TXT)
		totalFind = ShowByCondition<ProductString>(IsMore, count);
	else
		totalFind = ShowByCondition<Product>(IsMore, count);
	return totalFind;
}

size_t SearchDate() {
	Date date;
	date.Randomaze();
	PrintWithSleep("Enter data to find products that will die\nDay.Mounth.Year(1.4.2020): ", date.ToString());

	size_t totalFind = 0;
	if (WorkMode() == Mode::TXT)
		totalFind = ShowByCondition<ProductString>(IsDied, date);
	else
		totalFind = ShowByCondition<Product>(IsDied, date);
	return totalFind;
}

int Search() {
	vector<size_t> order = { 3,2,1 };
	while (true) {
		if (order.size() == 0) break;

		Menu menu("Search type:", {
			MenuItem("By name", nullptr, 1),
			MenuItem("By amount", nullptr, 2),
			MenuItem("By date", nullptr, 3)
			});
		int type = menu.DoMenu({ order[0] });
		order.erase(order.begin(), order.begin() + 1);

		if (type == (int)MenuMode::EXIT) return (int)MenuMode::REPEATE;

		size_t totalFind = SwitchFunc(type, { SearchName, SearchAmount, SearchDate })();
		if (totalFind == 0)
			cout << "Nothing found\n\n";
		else
			cout << "Total find " << totalFind << " products\n\n";
		Sleep(g_pauseSleep);
	}
	return (int)MenuMode::REPEATE;
}

#pragma endregion 


#pragma region Modify

template <typename Tproduct>
static bool ModifyField(Tproduct* product, int field) {
	switch (field) {
	case 1:
		StringRandom(product->name);
		PrintWithSleep("Enter new product's name: ", product->name);
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
		product->date.Randomaze();
		PrintWithSleep("Enter new product's date: ", product->date.ToString());
		break;
	case 5:
		product->expirationDate = rand() % 500 + 500;
		PrintWithSleep("Enter new product's life time: ", FloatToString((float)product->expirationDate));
	}

	return true;
}

template <typename Tproduct>
static bool ModifySet(size_t id) {
	bool modifySuccess = false;

	Tproduct* product;

	if (WorkMode() == Mode::TXT)
		product = (Tproduct*)TakeProductTxt(id - 1);
	else if (WorkMode() == Mode::BIN)
		product = (Tproduct*)TakeProductBin(id - 1);
	else product = (Tproduct*)TakeProductVector(id - 1);
	if (product == nullptr || product->id == 0) {
		if (product && WorkMode() != Mode::VECTOR) delete product;
		return false;
	}

	Menu menu("Select a field to change: ", {
		MenuItem("Name: " + string(product->name), nullptr, 1),
		MenuItem("Amount: " + FloatToString(product->count), nullptr, 2),
		MenuItem("Type: " + string(UnitsToString((int)product->units)), nullptr, 3),
		MenuItem("Date: " + product->date.ToString(), nullptr, 4),
		MenuItem("Life time: " + to_string(product->expirationDate), nullptr, 5)
		});
	size_t choice = rand() % 5 + 1;
	int result = menu.DoMenu({ choice });

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
	size_t id = rand() % 20 + 10;
	PrintWithSleep("Enter id of product: ", FloatToString((float)id));
	bool modifySuccess = false;

	if (WorkMode() == Mode::TXT)
		modifySuccess = ModifySet<ProductString>(id);
	else
		modifySuccess = ModifySet<Product>(id);

	if (modifySuccess)
		cout << "\n\nSuccess" << endl;
	else
		cout << "\n\nFailed to modify product." << endl;
	Sleep(g_pauseSleep);
	return (int)MenuMode::REPEATE;
}

#pragma endregion


int Delete() {
	size_t id = rand() % 20 + 3;
	PrintWithSleep("Enter id of product: ", FloatToString((float)id));
	bool deleteSuccess = SwitchFunc((int)WorkMode(), { DeleteVector, DeleteTxt, DeleteBin })(id);
	if (deleteSuccess)
		cout << "\n\nSuccess" << endl;
	else
		cout << "\n\nFailed to delete product." << endl;
	Sleep(g_pauseSleep);
	return (int)MenuMode::REPEATE;
}
