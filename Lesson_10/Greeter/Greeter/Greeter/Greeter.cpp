

#include <iostream>
#include<Windows.h>
#include "StaticLib.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string Name;

    std::cout << std::endl;
    std::cout << "Введите имя: ";
    std::cin >> Name;

    GreeteNMS::Greete greete(Name);

    std::cout << std::endl;
    std::cout << "Здравствуйте: " << greete.getNam() << std::endl;

}

