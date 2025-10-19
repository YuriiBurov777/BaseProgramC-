#include <Windows.h>
#include "Sarr.h"


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try {

        // Попытка создать массив с индексом 0
        //smart_array arr(0);

        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);

        //Проверка обработки неверного индекса
        //std::cout << arr.get_element(10) << std::endl; // Выбросит исключение
        
        // Попытка добавить шестой элемент - массив автоматически расширится
        // arr.add_element(100);

        std::cout << "Элемент в индексе 1: " << arr.get_element(1) << std::endl;
        std::cout << "Текущий размер: " << arr.get_size() << std::endl;
        std::cout << "Текущая вместимость: " << arr.get_capacity() << std::endl;
        std::cout << "\t"<< std::endl;
        arr.print();
       
    }
    // Базовый класс для исключений
    catch (const std::exception& ex) {
        std::cout << "Исключение: " << ex.what() << std::endl;
    }

    return 0;
}