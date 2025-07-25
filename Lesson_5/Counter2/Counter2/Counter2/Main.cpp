
#include <iostream>
#include<Windows.h>
#include"InpValue.h"
#include"Counter2.h"
#include"Create.h"



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет:" << std::endl;
    std::cin >> inp::a;

    if (inp::a == "да")
    {
        std::cout << "Введите начальное значение счётчика:" << std::endl;
        std::cin >> inp::stVal;

    }

    Counter myCount = Create(inp::a, inp::stVal);
    Counter* ptr = &myCount;

    do
    {
        std::cout << "Введите команду('+', '-', '=' или 'x') : " << std::endl;
        std::cin >> inp::operat;
        if ((inp::operat == '+') or (inp::operat == '-'))
        {
            ptr->setIncrDecr(inp::operat);
        }
        if (inp::operat == '=')
        {
            std::cout << ptr->getValue() << std::endl;
        }

    } while (inp::operat != 'х');

    std::cout << "До свидания" << std::endl;
}



