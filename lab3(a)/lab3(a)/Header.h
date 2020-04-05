#ifndef MAIN_HEADER_WITH_ALL_FUNCTIONS
#define MAIN_HEADER_WITH_ALL_FUNCTIONS

#include "UsefulFeatures.h"
#include "Menu.h"
#include <ctime>
#include <iostream>

using std::size_t;

void StartMenu();

int Demonstration();
int Benchmark();

void BubbleSort(tm* arr, size_t size, bool stepPrint = false);
void QuickSort(tm* arr, size_t size, bool stepPrint = false);
void MergeSort(tm* arr, size_t size, bool stepPrint = false);
void CombinedSorting(tm* arr, size_t size, bool stepPrint = false);
void CppSort(tm* arr, size_t size, bool stepPrint=false);

tm tm_Random();
string ToString(tm date);
void StepPrint(tm* arr, size_t size, bool active);

const size_t pauseTime = 1600;

#endif // !MAIN_HEADER_WITH_ALL_FUNCTIONS
