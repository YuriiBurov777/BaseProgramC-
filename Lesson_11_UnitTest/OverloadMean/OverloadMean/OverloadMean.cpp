

#include <iostream>
#include "OverMean.h"

int main()
{
	ExtArray<int> v1{ 4, 2, 7, 2, 5, 5, 0, 5, 5 };
	std::cout << v1.mean(3,5);
	return 0;
}

