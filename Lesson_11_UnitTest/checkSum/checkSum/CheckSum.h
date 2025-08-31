#pragma once
#include <utility>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>

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

	int checkSum()
	{
		// Проверка типа массива - только bool или int
	    if (!std::is_same_v<T, bool> && !std::is_same_v<T, int>)
		{
			throw std::invalid_argument("Data type error"); // Подходит для проверки типов данных и аргументов значений. функций
		}

		// Проверка содержимого массива для int
		if (std::is_same_v<T, int>)
		{
			for (size_t i = 0; i < _size; i++) 
			{
				if (extended_array[i] != 0 && extended_array[i] != 1) 
				{
					throw std::logic_error("The array contains numbers other than 0 and 1"); //Lodgic_error подходит для поиска значений ячеек в массиве выходящих за требуемый диапазон
				}
			}
		}

		// Подсчет количества true/единиц.Для bool: true, для int: 1 
		int count = 0;
		for (size_t i = 0; i < _size; i++) 
		{
			if (extended_array[i]) 
			{  
				count++;
			}
		}
		return count;
	}
};
