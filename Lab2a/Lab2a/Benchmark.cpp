#include "Header.h"
#include <ctime>
#include <fstream>

static string AddChar(size_t value, size_t minCount = 10, char returnValue = ' ');
static string AddChar(string value, size_t minCount = 10, char returnValue = ' ');


static void BenchFixedSize(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);
static void BenchOnVector(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);
static void BenchCircular(const size_t& n, size_t& sizeInBytes, size_t& timeInMilisec);

void BenchOperations();

static void Insert(std::ostream& file);
static void SetGet(std::ostream& file);
static void Remove(std::ostream& file);


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

	BenchOperations();
	
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


void BenchOperations() {

	std::fstream file;
	file.open("Benchmark_operations.txt", std::fstream::out);
	if (!file.is_open()) throw - 1;

	file << "Operations:\n\n";
	SetColor(6, "\tOperations start benchmark\n");

	SetColor(6, "\tINSERT\n");
	Insert(file);
	SetColor(6, "\tSET/GET\n");
	SetGet(file);
	SetColor(6, "\tREMOVE\n");
	Remove(file);

	file.close();
}

void Insert(std::ostream& file) {
	clock_t start, end;
	int index = 0;
	file << "Average count of INSERT per seconds:\n";

	while (index < 3) {
		if (index == 0) file << "\tFixed size list - ";
		if (index == 1) file << "\tList based on vector - ";
		else if (index == 2) file << "\tCircular list - ";
		size_t n = 600, time;
		size_t nSum = 0, timeSum = 0;

		while (true) {
			FixedSize<IP> fixedSize(n);
			OnVector<IP> onVector;
			CircularList<IP> circularList;
			start = clock();

			if (index == 0)
				for (size_t i = 0; i < n; i++)
					fixedSize.Insert(RandomIP(), RandomInt());
			else if (index == 1)
				for (size_t i = 0; i < n; i++)
					onVector.Insert(RandomIP(), RandomInt());
			else if (index == 2)
				for (size_t i = 0; i < n; i++)
					circularList.Insert(RandomIP(), RandomInt());

			end = clock();
			time = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
			cout << AddChar(n) << AddChar(time, 7) << endl;
			timeSum += time;
			nSum += n;

			if (time > 1e4) break;
			n *= 2;
		}
		file << FloatToString((float)nSum / timeSum) << endl;
		index++;
	}
	file << endl;
}

void SetGet(std::ostream& file) {
	clock_t start, end;
	int index = 0;
	file << "Average count of SET-GET per seconds:\n";

	while (index < 3) {
		if (index == 0) file << "\tFixed size list - ";
		if (index == 1) file << "\tList based on vector - ";
		else if (index == 2) file << "\tCircular list - ";
		size_t n = 600, time;
		size_t nSum = 0, timeSum = 0;

		while (true) {
			FixedSize<IP> fixedSize(n);
			OnVector<IP> onVector;
			CircularList<IP> circularList;

			if (index == 0)
				for (size_t i = 0; i < n; i++)
					fixedSize.Insert(RandomIP(), RandomInt());
			else if (index == 1)
				for (size_t i = 0; i < n; i++)
					onVector.Insert(RandomIP(), RandomInt());
			else if (index == 2)
				for (size_t i = 0; i < n; i++)
					circularList.Insert(RandomIP(), RandomInt());

			start = clock();

			if (index == 0)
				for (size_t i = 0; i < n; i++)
					fixedSize.Set(fixedSize.Get(RandomInt()), RandomInt());
			else if (index == 1)
				for (size_t i = 0; i < n; i++)
					onVector.Set(onVector.Get(RandomInt()), RandomInt());
			else if (index == 2)
				for (size_t i = 0; i < n; i++)
					circularList.Set(circularList.Get(RandomInt()), RandomInt());

			end = clock();
			time = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
			cout << AddChar(n) << AddChar(time, 7) << endl;
			timeSum += time;
			nSum += n;

			if (n > 1e5 || time > 1e4) break;
			n *= 2;
		}
		file << FloatToString((float)nSum / timeSum) << endl;
		index++;
	}
	file << endl;
}

void Remove(std::ostream& file) {
	clock_t start, end;
	int index = 0;
	file << "Average count of REMOVE per seconds:\n";

	while (index < 3) {
		if (index == 0) file << "\tFixed size list - ";
		if (index == 1) file << "\tList based on vector - ";
		else if (index == 2) file << "\tCircular list - ";
		size_t n = 600, time;
		size_t nSum = 0, timeSum = 0;

		while (true) {
			FixedSize<IP> fixedSize(n);
			OnVector<IP> onVector;
			CircularList<IP> circularList;

			if (index == 0)
				for (size_t i = 0; i < n; i++)
					fixedSize.Insert(RandomIP(), RandomInt());
			else if (index == 1)
				for (size_t i = 0; i < n; i++)
					onVector.Insert(RandomIP(), RandomInt());
			else if (index == 2)
				for (size_t i = 0; i < n; i++)
					circularList.Insert(RandomIP(), RandomInt());

			start = clock();

			if (index == 0)
				for (size_t i = 0; i < n; i++)
					fixedSize.Remove(RandomInt());
			else if (index == 1)
				for (size_t i = 0; i < n; i++)
					onVector.Remove(RandomInt());
			else if (index == 2)
				for (size_t i = 0; i < n; i++)
					circularList.Remove(RandomInt());

			end = clock();
			time = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
			cout << AddChar(n) << AddChar(time, 7) << endl;
			timeSum += time;
			nSum += n;

			if (n > 1e5 || time > 1e4) break;
			n *= 2;
		}
		file << FloatToString((float)nSum / timeSum) << endl;
		index++;
	}
	file << endl;
}
