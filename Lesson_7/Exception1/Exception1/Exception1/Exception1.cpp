
#include <iostream>
#include <Windows.h>

int function(std::string str, int forbidden_length);


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int a{};
    std::string inWord{};
    std::cout << "Введите запретную длину: ";
    std::cin >> a;

    do
    {
    std::cout << "Введите слово: ";
    std::cin >> inWord;
    // Обертка для функции с вероятностью ошибки
    try
    { 
        std::cout << "Длина слова " << inWord << " равна "<< function(inWord, a) << std::endl ;
    }
    // Обработка ошибки
    catch (const std::exception&e)
    {
        std::cerr << "Исключение: " << e.what() << std::endl;
        break;
    }

    } while (true);
    
    return 0;
}

int function(std::string str, int forbidden_length)
{   
    int size = str.length();

    if (size == forbidden_length)
    {
        // Выброс ошибки
        throw std::runtime_error("Вы ввели слово запретной длины!До свидания!");
        return size;
    }
        
    return size;
}


