#include "Header.h"
#include <ctime>
#include <fstream>

static string AddChar(size_t value, size_t minCount = 10, char returnValue = ' ');

static string AddChar(string value, size_t minCount = 10, char returnValue = ' ');


static void BenchFixedSize(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);
static void BenchOnVector(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);
static void BenchCircular(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);


static bool ByScreenPlay(void(*Func)(const size_t&, size_t&, size_t&),
	const string message, const char* path, bool reCreate = false) {

	std::fstream file;
	if (reCreate)
		file.open(path, std::fstream::out);
	else file.open(path, std::fstream::app);
	if (!file.is_open()) throw - 1;

	file << message << "\n\n";
	file << AddChar("N") << AddChar("mSec", 7) << AddChar("Bytes") << endl;
	SetColor(6, "\t", message, " start benchmark\n");

	size_t n = 85, n_start = 0;
	size_t sizeInBytes = 0;
	size_t timeInMilisec = 0;

	while (true) {
		Func(n, sizeInBytes, timeInMilisec);
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
		if (sizeInBytes > 1e8 || timeInMilisec > 1e4) break;
	}
	file << "\n";
	file.close();
	return true;
}

int Benchmark() {
	ByScreenPlay(BenchFixedSize, "Fixed size list", "Benchmark.txt", true);
	ByScreenPlay(BenchOnVector, "List based on vector", "Benchmark.txt");
	ByScreenPlay(BenchCircular, "Linked list", "Benchmark.txt");
	
	cout << "\nBenchmark ends" << endl;
	system("pause");
	
	return (int)MenuMode::REPEATE;
}

string AddChar(size_t value, size_t minCount, char returnValue) {
	string result = "";
	for (size_t i = 0; i < minCount - 1; ++i)
		if ((int)value < pow(10, (i + 1)))
			result += returnValue;

	result += to_string((int)value);
	return result;
}

string AddChar(string value, size_t minCount, char returnValue) {
	for (size_t i = minCount - value.size(); i > 0; i--)
		value = returnValue + value;

	return value;
}



/* Benchmark screenplay

create empty
insert n in begin
set random elem value from get another
delete n/5 random elem

*/

void BenchFixedSize(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec) {
	clock_t start, end;
	start = clock();

	FixedSize<IP> arr(n);
	for (size_t i = 0; i < n; i++) {
		arr.Insert(RandomIP(), RandomInt());
		arr.Set(arr.Get(RandomInt()), RandomInt());
	}
	for (size_t i = n / 5; i > 0; i--)
		arr.Remove(RandomInt());

	end = clock();
	timeInMilisec = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
	sizeInBytes = sizeof(arr) + sizeof(IP) * n;
}

void BenchOnVector(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec) {
	clock_t start, end;
	start = clock();

	OnVector<IP> arr;
	for (size_t i = 0; i < n; i++) {
		arr.Insert(RandomIP(), RandomInt());
		arr.Set(arr.Get(RandomInt()), RandomInt());
	}
	for (size_t i = n / 5; i > 0; i--)
		arr.Remove(RandomInt());

	end = clock();
	timeInMilisec = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
	sizeInBytes = sizeof(arr) + sizeof(IP) * n / 5 * 4;
}

void BenchCircular(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec) {
	clock_t start, end;
	start = clock();

	CircularList<IP> arr;
	for (size_t i = 0; i < n; i++) {
		arr.Insert(RandomIP(), RandomInt());
		arr.Set(arr.Get(RandomInt()), RandomInt());
	}
	for (size_t i = n / 5; i > 0; i--)
		arr.Remove(RandomInt());

	end = clock();
	timeInMilisec = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
	sizeInBytes = sizeof(arr) + (sizeof(IP) + sizeof(Node<IP>*)) * n / 5 * 4;

}