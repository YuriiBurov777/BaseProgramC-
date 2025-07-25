
#include <iostream>
#include<Windows.h>
#include"Calculator.h"

namespace inp
{
    double in1{};
    double in2{};
    int op1{};
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Calculator calculator;
    Calculator* ptr = &calculator;
    do
    {
        std::cout << "Введите первое число: ";
        std::cin >> inp::in1;
        std::cout << std::endl;
        std::cout << "Введите второе число: ";
        std::cin >> inp::in2;
        std::cout << std::endl;
        std::cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
        std::cin >> inp::op1;
      
         //Запись значений в класс калькулятор
        ptr->setnum1(inp::in1);
        ptr->setnum2(inp::in2);
        ptr->setvalue(inp::op1);
         //Проверка деления на 0
        if (ptr->chekOperator() == false)
        {
            std::cout << "Деление на ноль - ошибка " << std::endl;
            continue;
        }
         //Вывод результата
        std::cout << std::endl;
        std::cout << "Результат операции (" << inp::op1 << "): " << ptr->Math_op() << std::endl;
        std::cout << std::endl;

    } while (true);
    return 0;
}

