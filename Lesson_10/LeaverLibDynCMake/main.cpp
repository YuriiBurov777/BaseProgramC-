
#include <iostream>
#include <Windows.h>
#include "Lib/Lib.h"


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string Name;

    std::cout << std::endl;
    std::cout << "������� ���: ";
    std::cin >> Name;

    LeaverNMS::Leave leave(Name);

    std::cout << std::endl;
    std::cout << "�������� ���: " << leave.getName() << std::endl;

}