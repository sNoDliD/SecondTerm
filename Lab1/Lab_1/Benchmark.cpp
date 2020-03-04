#include "Header.h"
#include <ctime>
#include <fstream>

static string AddChar(size_t value, size_t minCount = 10, char returnValue = ' ');

static void TxtBench(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);
static void BinBench(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);
static void VectorBench(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);

template <typename Tproduct, typename... T>
static size_t FindByCondition(bool (*Condition)(Tproduct*, T&...) = nullptr, T&... data) {
	size_t totalFind = 0, i = 0;
	int index = SetIndex(WorkMode(), { Mode::VECTOR, Mode::BIN });
	auto TakeProduct = SwitchFunc(index, { TakeProductVector, TakeProductBin });
	Tproduct* product;

	while (true) {
		if (TakeProduct)
			product = (Tproduct*)TakeProduct(i++);
		else
			product = (Tproduct*)TakeProductTxt(i++);

		if (product == nullptr) break;
		bool deletedProduct = product->id == 0 || product->storeId != ShopId();
		if (!deletedProduct && (Condition == nullptr || Condition(product, data...)))
			totalFind++;
		if (WorkMode() != Mode::VECTOR) delete product;
	}
	return totalFind;
}

/* Benchmark screenplay

add n pdocuct
find by name 
delete n/10 from end and n/10 from start
find by amound, by date
show all
(reorganize for vector and bin. Txt reorganize all time)

*/


int Benchmark() {
	std::fstream file;
	file.open("Benchmark_result.txt", std::fstream::out);
	if (!file.is_open()) throw - 1;

	Store* temp = new Store();
	temp->maxProductCount = 1e9;
	remove("temp.bin");
	CreatePathStore("temp.bin");
	AppendStore(temp);
	delete temp;
	SetShop(1);

	int index = 0;
	string message[] = { "Vector" , "Txt", "Bin"};

	while (index < 3) {
		SetWorkMode(Mode(index));
		file << message[index] << "\n\n";
		file << "         N   mSec    Bytes\n";
		SetColor(6, "\t", message[index], " start benchmark\n");
		cout << "        N    mSec    Bytes\n\n";

		size_t n = 10, n_start = 0;
		size_t sizeInBytes = 0;	
		size_t timeInMilisec = 0;	
		
		while (true) {
			SwitchFunc(index + 1, { VectorBench, TxtBench, BinBench })(n, sizeInBytes, timeInMilisec);
			cout << AddChar(n) << AddChar(timeInMilisec, 7) << AddChar(sizeInBytes) << endl;
			file << AddChar(n) << AddChar(timeInMilisec, 7) << AddChar(sizeInBytes) << endl;
			if (n_start == 0) {
				if (timeInMilisec > 1e3) {
					n_start = n;
					n += n_start;
				}
				else n *= 2;
			}
			else n += n_start;
			if (sizeInBytes > 1e9 || timeInMilisec > 1e4) break;
		}
		index++;
	}
	file.close();
	FreeShops("temp.bin", false);

	cout << "\nBenchmark ends" << endl;
	system("pause");
	return (int)MenuMode::REPEATE;
}

void TxtBench(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec) {
	clock_t start, end;
	remove("DataBases/benchmark.txt");
	CreatePathTxt("benchmark");

	float count = 900;
	Date date;
	date.Randomaze();

	start = clock();

	AddTxtRandom(n);
	FindByCondition<ProductString>(IsSubName, "ab");
	for (size_t i = 1; i <= n / 10; i++) 
		DeleteTxt(n - i);
	for (size_t i = 1; i <= n / 10; i++) 
		DeleteTxt(i);
	FindByCondition<ProductString>(IsMore, count);
	FindByCondition<ProductString>(IsDied, date);
	FindByCondition<ProductString>();

	end = clock();

	FILE* file;
	fopen_s(&file, "DataBases/benchmark.txt", "rb");
	if (file == 0) throw - 1;
	fseek(file, 0, SEEK_END);
	sizeInBytes = ftell(file);
	fclose(file);

	timeInMilisec = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
	remove("DataBases/benchmark.txt");
}

void BinBench(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec) {
	clock_t start, end;
	remove("DataBases/benchmark.bin");
	CreatePathBin("benchmark");

	float count = 900;
	Date date;
	date.Randomaze();

	start = clock();

	AddBinRandom(n);
	FindByCondition<Product>(IsSubName, "ab");
	FindByCondition<Product>(IsMore, count);
	FindByCondition<Product>(IsDied, date);
	for (size_t i = 1; i <= n / 10; i++) {
		DeleteBin(n - i);
		DeleteBin(i);
	}
	FindByCondition<Product>();
	SetLastIdBin();

	end = clock();

	FILE* file;
	fopen_s(&file, "DataBases/benchmark.bin", "rb");
	if (file == 0) throw - 1;
	fseek(file, 0, SEEK_END);
	sizeInBytes = ftell(file);
	fclose(file);

	timeInMilisec = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
	remove("DataBases/benchmark.bin");
}

void VectorBench(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec) {
	clock_t start, end;
	FreeVector();
	float count = 900;
	Date date;
	date.Randomaze();

	start = clock();

	AddVectorRandom(n);
	FindByCondition<Product>(IsSubName, "ab");
	FindByCondition<Product>(IsMore, count);
	FindByCondition<Product>(IsDied, date);
	for (size_t i = 1; i <= n / 10; i++) {
		DeleteVector(i);
		DeleteVector(n - i);
	}
	FindByCondition<Product>();
	sizeInBytes = ReorganizeVector() * sizeof(Product);

	end = clock();

	FreeVector();
	timeInMilisec = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
}

string AddChar(size_t value, size_t minCount, char returnValue) {
	string result = "";
	for (size_t i = 0; i < minCount - 1; ++i)
		if ((int)value < pow(10, (i + 1)))
			result += returnValue;

	result += to_string((int)value);
	return result;
}
