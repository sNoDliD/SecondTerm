#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
#include "Header.h"


void StartMenu() {
	Menu menu("Choose your mode:", {
		MenuItem("Demonstration", Demonstration),
		MenuItem("Benchmark", Benchmark)
		});
	menu.DoMenu();
}

int Demonstration(){
    auto Func = { BubbleSort, QuickSort, MergeSort, CombinedSorting, CppSort};
    auto messages = { "Bubble sort","Quick sort", "Merge sort", "Combined sorting", "Librari sort" };
    int size;
    InputStr(size, "Enter size of random array: ", 1, 15);

    tm* arr = new tm[size];
    tm* copy = new tm[size];
    for (size_t i = 0; i < size; i++)
        arr[i] = tm_Random();

    StepPrint(arr, size, true);
    for(size_t i = 0; i < 5; i++){
        std::copy(arr, arr + size, copy);

        cout << "\n" << *(messages.begin() + i) << ":\n";
        StepPrint(copy, size, true);

        auto sort = *(Func.begin() + i);
        sort(arr, size, true);
    }
    delete[] arr;
    delete[] copy;

    system("pause");
	return (int)MenuMode::REPEATE;
}

bool operator <(const tm& lhs, const tm& rhs){
    bool result = std::tie(lhs.tm_year, lhs.tm_mon, lhs.tm_mday, lhs.tm_hour, lhs.tm_min) <
        std::tie(rhs.tm_year, rhs.tm_mon, rhs.tm_mday, rhs.tm_hour, rhs.tm_min);
    return result;
}

bool operator >(const tm& lhs, const tm& rhs){
    return (rhs < lhs);
}

bool operator <=(const tm& lhs, const tm& rhs){
    return !(lhs > rhs);
}

void swap(tm& d1, tm& d2){
    tm temp = d1;
    d1 = d2;
    d2 = temp;
}

tm tm_Random() {
    tm result;
    result.tm_year = Random(1900, 2038);
    result.tm_mon = Random(0, 11);
    result.tm_mday = Random(1, 31);

    result.tm_hour = Random(0, 23);
    result.tm_min = Random(0, 59);
    return result;
}

string ToString(tm date) {
    string result = AddChar(date.tm_mday, 2, '0') + "."
        + AddChar(date.tm_mon, 2, '0') + "."
        + AddChar(date.tm_year, 2, '0') + " "
        + AddChar(date.tm_hour, 2, '0') + ":"
        + AddChar(date.tm_min, 2, '0');
    return result;
}



int HoarePartition(tm* arr, int low, int high){
    tm pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true){
        do{
            i++;
        } while (arr[i] < pivot);

        do{
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;
        swap(arr[i], arr[j]);
    }
}

void QuickSortStep(tm* arr, int left, int right, bool stepPrint){
    if (left < right){
        int pivotIndex = HoarePartition(arr, left, right);
        StepPrint(arr + left, right - left + 1, stepPrint);

        QuickSortStep(arr, left, pivotIndex, stepPrint);
        QuickSortStep(arr, pivotIndex + 1, right, stepPrint);
    }
}

void QuickSort(tm* arr, size_t size, bool stepPrint) {
    QuickSortStep(arr, 0, size - 1, stepPrint);
    StepPrint(arr, size, stepPrint);
}




void CombinedSortingStep(tm* arr, size_t left, size_t right, size_t startSimple, bool stepPrint) {
    if (left + startSimple < right) {

        int pivotIndex = HoarePartition(arr, left, right);
        StepPrint(arr, right - left + 1, stepPrint);

        CombinedSortingStep(arr, left, pivotIndex, startSimple, stepPrint);
        CombinedSortingStep(arr, pivotIndex + 1, right, startSimple, stepPrint);
    }
    else if (left < right) {
        BubbleSort(arr + left, right - left + 1);
        StepPrint(arr, right - left + 1, stepPrint);
    }
}

void CombinedSorting(tm* arr, size_t size, bool stepPrint) {
    CombinedSortingStep(arr, 0, size - 1, 35, stepPrint);
    StepPrint(arr, size, stepPrint);
}




void Merge(tm* source, tm* destination, size_t begin, size_t middle, size_t end, bool stepPrint) {
    size_t first = begin, second = middle;

    for (size_t i = begin; i < end; i++) {
        if ((first < middle) && (second >= end || source[first] <= source[second])) {
            destination[i] = source[first];
            first++;
        }
        else {
            destination[i] = source[second];
            second++;
        }
    }
    StepPrint(destination + begin, end - begin, stepPrint);
}

void MergeSortTwoarrays(tm* source, tm* destination, size_t begin, size_t end, bool stepPrint) {
    if (end - begin < 2)
        return;
    size_t middle = (end + begin) / 2;

    MergeSortTwoarrays(destination, source, begin, middle, stepPrint);
    MergeSortTwoarrays(destination, source, middle, end, stepPrint);
    Merge(source, destination, begin, middle, end, stepPrint);
}

void MergeSort(tm* arr, size_t size, bool stepPrint) {
    tm* destination = new tm[size];
    std::copy(arr, arr + size, destination);
    MergeSortTwoarrays(destination, arr, 0, size, stepPrint);
    delete[] destination;
}




void BubbleSort(tm* arr, size_t size, bool stepPrint) {
    for (size_t j = size - 1; j > 0; j--) {
        bool isSorted = true;

        for (size_t i = 0; i < j; i++)
            if (arr[j] < arr[i]) {
                isSorted = false;
                swap(arr[i], arr[j]);
                StepPrint(arr, size, stepPrint);
            }

        if (isSorted)
            break;
    }
}

void StepPrint(tm* arr, size_t size, bool active) {
    if (active) {
        for (size_t index = 0; index < size; index++)
            cout << ToString(arr[index]) + " | ";
        cout << endl;
    }
}




void CppSort(tm* arr, size_t size, bool stepPrint) {
    std::sort(arr, arr + size);
    StepPrint(arr, size, stepPrint);
}