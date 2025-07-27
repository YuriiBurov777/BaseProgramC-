
#include <iostream>
#include<Windows.h>
#include "AddFunc.h"

#define MODE 1

#ifndef MODE                        // Проверка на создание MODE
#error constant MODE required
#endif

namespace in
{
    int num1{};
    int num2{};
}

int main(int argc, char** argv)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
   
#if MODE == 0

    std::cout << "Работаю в режиме тренировки" << std::endl;

#elif MODE == 1

    std::cout << "Работаю в боевом режиме" << std::endl;
    std::cout << "Введите число 1: ";
    std::cin >> in::num1;
    std::cout << "Введите число 2: "; 
    std::cin >> in::num2;
    std::cout << "Результат сложения: " << Add(in::num1, in::num2) << std::endl;

#else

    std::cout << "Неизвестный режим. Завершение работы" << std::endl;

#endif

    return 0;

}
