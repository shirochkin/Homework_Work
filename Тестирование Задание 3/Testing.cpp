
#include <iostream>
#include "extended_array.h"
#include <typeinfo>

int main() {
	ExtArray<bool> arr = { 0, 1, 1, 0, 1, 0, 0, 0, 0, 1 };
	ExtArray<bool> arr2 = { true, false, false, false, true, false, true, true, false, true, false, false, false };
	ExtArray<int> arr3 = { 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1 };
	ExtArray<bool> arr4 = { 1, false, 1, 1, true, false, true, true, false, 1 };
	ExtArray<int> arr5 = { 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 5, 0, 1 };
	ExtArray<double> arr6 = { 1.25, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0 };

	arr.checkSumTest();
	arr2.checkSumTest();
	arr3.checkSumTest();
	arr4.checkSumTest();
	arr5.checkSumTest();
	arr6.checkSumTest();
	system("pause");
	return 0;
}