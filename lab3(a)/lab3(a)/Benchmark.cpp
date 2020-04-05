#include "Header.h"
#include <ctime>
#include <fstream>

static void AllSorts(const char* path);

static void OnlyCombined();

static void SortTime(void(*SortFunc)(tm*, size_t, bool), tm* arr, const size_t& size, size_t& timeInMilisec) {

	tm* copy = new tm[size];
	std::copy(arr, arr + size, copy);

	clock_t start, end;
	start = clock();

	SortFunc(copy, size, false);

	end = clock();
	timeInMilisec = ((double)end - start) * 1000 / CLOCKS_PER_SEC;
}

static void SortArr(tm* arr, size_t size, std::ostream& file, bool* active) {
	auto Func = { BubbleSort, QuickSort, MergeSort, CombinedSorting, CppSort };


	size_t timeInMilisec = 0;


		for (size_t i = 0; i < 5; i++) {
			if (!active[i]) {
				continue;
			}
			auto Sort = *(Func.begin() + i);
			SortTime(Sort, arr, size, timeInMilisec);
			file << i + 1 << ". " << AddChar(timeInMilisec, 5) << " msec" << endl;

			if (timeInMilisec > 6e3)
				active[i] = false;
		}
	file << "\n";

}

void AllSorts(const char* path) {

	std::fstream file;
	file.open(path, std::fstream::out);
	if (!file.is_open()) throw - 1;

	size_t size = 30 + Random(-2, 5);
	file << "Random array:\n";

	bool active[] = { true, true, true, true, true };
	while (size < 1e6) {
		file << " N = " << AddChar(size) << ":\n";
		cout << size << endl;

		tm* arr = new tm[size];
		for (size_t i = 0; i < size; i++)
			arr[i] = tm_Random();

		SortArr(arr, size, file, active);

		size = Random(8, 10) * size + Random(-2, 100);
		file << "\n\n";
		delete[] arr;
	}
	file.close();
}

int Benchmark() {
	cout << "Benchmark start.\nPlease wait..." << endl;

	AllSorts("Bencmark.txt");

	//OnlyCombined();
	
	cout << "\nBenchmark ends" << endl;
	system("pause");
	
	return (int)MenuMode::REPEATE;
}

