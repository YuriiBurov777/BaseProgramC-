

#include <iostream>
#include <Windows.h>
#include "LeaverLibDyn.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    std::string Name;

    std::cout << std::endl;
    std::cout << "Введите имя: ";
    std::cin >> Name;

    LeaverNMS::Leave leave(Name);

    std::cout << std::endl;
    std::cout << "Aufwiedersehen.Schonen Tag: " << leave.getName() << std::endl;





}

