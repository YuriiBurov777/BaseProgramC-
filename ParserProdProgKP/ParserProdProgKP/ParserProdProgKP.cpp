
#include "Parser.h"
#include <Windows.h>


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Тест 1: Корректный файл
    std::cout << "=== Тест 1: Корректный файл ===" << std::endl;
    try {

        Parser parser("Text.txt");

        // Чтение существующих значений
        std::cout << "Section1: " << parser.get_value<std::string>("Section1.var2") << std::endl;
        std::cout << "Section2: " << parser.get_value<int>("Section1.var1") << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Тест 2: Файл не существует
    std::cout << "\n=== Тест 2: Файл не существует ===" << std::endl;
    try {
        Parser parser("Text1.txt");
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Тест 3: Значение не найдено
    std::cout << "\n=== Тест 3: Значение не найдено ===" << std::endl;
    try {
        Parser parser("Text.txt");
        auto value = parser.get_value<int>("Section3.val1");
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Тест 4: Секция не найдена
    std::cout << "\n=== Тест 4: Секция не найдена ===" << std::endl;
    try {
        Parser parser("Text.txt");
        auto value = parser.get_value<std::string>("Section7.val1");
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Тест 5: Пустой файл
    std::cout << "\n=== Тест 6: Пустой файл ===" << std::endl;
    try {

        Parser parser("TextEmpty.txt");
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Тест 6: Преобразование типа bool
    std::cout << "\n=== Тест 6: Пустой файл ===" << std::endl;
    try {

        Parser parser("Text.txt");
        auto value = parser.get_value<int>("Section4.Mode");
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}