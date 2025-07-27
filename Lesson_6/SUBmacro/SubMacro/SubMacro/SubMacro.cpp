
#include <iostream>
#include<Windows.h>
#define sub( a, b) ((a)-(b))

namespace in
{
	int a{ 6 };
	int b{ 5 };
	int c{ 2 };
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Результат:" << "\n" << std::endl;

	std::cout << sub(in::a, in::b) << "\n" << std::endl;
	std::cout << sub(in::a, in::b) * in::c << "\n" << std::endl;
	std::cout << sub(in::a, in::b + in::c) * in::c << "\n" << std::endl;

	return 0;

}
