#pragma once
#include <utility>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

template <typename T>
class ExtArray
{
private:
	std::vector<T> extended_array;
	size_t _size;
public:
	ExtArray(std::initializer_list<T> l) : extended_array(l)
	{
		_size = l.size();
	}

	ExtArray(int size) : _size(size)
	{
		extended_array.resize(_size);
	}

	T& operator[](size_t index)
	{
		return extended_array[index];
	}

	size_t size()
	{
		return _size;
	}

	double mean()
	{
		double sum = 0;
		for (size_t i = 0; i < _size; i++)
		{
			sum += extended_array[i];
		}
		return sum / _size;
	}

	double median()
	{
		std::vector<T> temp_array;
		std::copy(extended_array.begin(), extended_array.end(), back_inserter(temp_array));
		std::sort(temp_array.begin(), temp_array.end());
		if (_size % 2 == 1)
		{
			return temp_array[_size / 2];
		}
		else
		{
			return static_cast<double>(temp_array[(_size / 2) - 1] + temp_array[_size / 2]) / 2;
		}
	}

	std::pair<T, int> mode()
	{
		T max = extended_array[0], cmax = 0, rmax = 0;
		for (int i = 0; i < _size; i++) 
		{
			if (cmax > rmax) 
			{
				rmax = cmax;
				max = extended_array[i - 1];
			}
			cmax = 0;
			for (int j = i; j < _size; j++)
			{
				if (extended_array[j] == extended_array[i])
				{
					cmax++;
				}
			}
		}
		return std::pair<T, int>(max, rmax);
	}

	template <typename T1, typename T2>
	void AssertEq(T1 valueA, T2 valueB) {
		if (valueA != valueB) {
			std::ostringstream err;
			err << "Assertion failed: " << valueA << " != " << valueB;
			throw std::runtime_error(err.str());
		}
	}

	void EmptyTest() {
		
		try {
			AssertEq(mean(), 0);
			std::cerr << "Mean function is OK" << std::endl;
		}

		catch (std::runtime_error& e) {
			std::cerr << "Mean function is WRONG" << std::endl;
		}


		try {
			AssertEq(median(), 0);
			std::cerr << "Median function is OK" << std::endl;
		}

		catch (std::runtime_error& e) {
			std::cerr << "Median function is WRONG" << std::endl;
		}

		try {
			std::pair<double, int> P = mode();
			double L = P.first;
			AssertEq(L, 0);
			std::cerr << "Mode function is OK" << std::endl;
		}

		catch (std::runtime_error& e) {
			std::cerr << "Mode function is WRONG" << std::endl;
		}
	}
};
