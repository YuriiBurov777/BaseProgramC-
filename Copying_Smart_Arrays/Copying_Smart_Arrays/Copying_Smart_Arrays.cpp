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

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        std::cout << "Элемент в индексе 1: " << arr.get_element(1) << std::endl;
        std::cout << "Текущий размер: " << arr.get_size() << std::endl;
        std::cout << "Текущая вместимость: " << arr.get_capacity() << std::endl;
        arr.print();
        std::cout << "\t" << std::endl;
        

        std::cout << "Элемент в индексе 1: " << new_array.get_element(1) << std::endl;
        std::cout << "Текущий размер: " << new_array.get_size() << std::endl;
        std::cout << "Текущая вместимость: " << new_array.get_capacity() << std::endl;
        new_array.print();
        std::cout << "\t" << std::endl;
        
        arr = new_array;

        //Проверка обработки неверного индекса
        //std::cout << arr.get_element(10) << std::endl; // Выбросит исключение

        // Попытка добавить шестой элемент - массив автоматически расширится
        // arr.add_element(100);

        arr.print();
        new_array.print();

    }
    // Базовый класс для исключений
    catch (const std::exception& ex) {
        std::cout << "Исключение: " << ex.what() << std::endl;
    }

    return 0;
}