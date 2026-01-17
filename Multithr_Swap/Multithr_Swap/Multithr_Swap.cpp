#include <iostream>
#include <mutex>
#include <utility>
#include <windows.h>

class Data {

    public:
    // Конструктор
    Data(int val = 0) : value(val) {}

    // Конструктор копирования
    Data(const Data& other) {
        std::lock_guard<std::mutex> lock(other.mtx);
        value = other.value;
    }

    // Оператор присваивания
    Data& operator=(const Data& other) {
        if (this != &other) {
            // Для захвата обоих мьютексов одновременно
            std::lock(mtx, other.mtx);
            std::lock_guard<std::mutex> lock1(mtx, std::adopt_lock);
            std::lock_guard<std::mutex> lock2(other.mtx, std::adopt_lock);
            value = other.value;
        }
        return *this;
    }

    int getValue() const {
        std::lock_guard<std::mutex> lock(mtx);
        return value;
    }

    void setValue(int val) {
        std::lock_guard<std::mutex> lock(mtx);
        value = val;
    }

    // Метод обмена данными с другим объектом Data
    // Вариант 1: Использование std::lock с lock_guard
    void swap_using_lock(Data& other) {
        if (this == &other) return; // избегаем самоприсваивания

        // Захватываем оба мьютекса одновременно, избегая deadlock
        std::lock(mtx, other.mtx);

        // Используем adopt_lock, чтобы lock_guard не пытался захватить уже захваченные мьютексы
        std::lock_guard<std::mutex> lock1(mtx, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(other.mtx, std::adopt_lock);

        // Выполняем обмен данными
        std::swap(value, other.value);
    }

    // Вариант 2: Использование std::scoped_lock (C++17)
    void swap_using_scoped_lock(Data& other) {
        if (this == &other) return; // избегаем самоприсваивания

        // std::scoped_lock автоматически захватывает все переданные мьютексы
        std::scoped_lock lock(mtx, other.mtx);
      
        // Выполняем обмен данными
        std::swap(value, other.value);
    }

    // Вариант 3: Использование std::unique_lock
    void swap_using_unique_lock(Data& other) {
        if (this == &other) return; // избегаем самоприсваивания

        // Создаем unique_lock для каждого мьютекса, но не захватываем их сразу
        std::unique_lock<std::mutex> lock1(mtx, std::defer_lock);
        std::unique_lock<std::mutex> lock2(other.mtx, std::defer_lock);

        // Захватываем оба мьютекса одновременно
        std::lock(lock1, lock2);

        // Выполняем обмен данными
        std::swap(value, other.value);
    }

    private:
    mutable std::mutex mtx;
    int value;
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Data data1(10);
    Data data2(20);

    std::cout << "До обмена_using_lock:" << std::endl;
    std::cout << "data1 = " << data1.getValue() << ", data2 = " << data2.getValue() << std::endl;

    // Тестируем swap с использованием lock
    data1.swap_using_lock(data2);
    std::cout << "\nПосле обмена_using_lock:" << std::endl;
    std::cout << "data1 = " << data1.getValue() << ", data2 = " << data2.getValue() <<"\n" << std::endl;

    // Возвращаем исходные значения
    data1.swap_using_lock(data2);

    std::cout << "До обмена_scoped_lock:" << std::endl;
    std::cout << "data1 = " << data1.getValue() << ", data2 = " << data2.getValue() << std::endl;

    // Тестируем swap с использованием scoped_lock
    data1.swap_using_scoped_lock(data2);
    std::cout << "\nПосле обмена_using_scoped_lock:" << std::endl;
    std::cout << "data1 = " << data1.getValue() << ", data2 = " << data2.getValue() <<"\n" <<  std::endl;

    // Возвращаем исходные значения
    data1.swap_using_scoped_lock(data2);

    std::cout << "До обмена_using_unique_lock:" << std::endl;
    std::cout << "data1 = " << data1.getValue() << ", data2 = " << data2.getValue() << std::endl;

    // Тестируем swap с использованием unique_lock
    data1.swap_using_unique_lock(data2);
    std::cout << "\nПосле обмена_using_unique_lock:" << std::endl;
    std::cout << "data1 = " << data1.getValue() << ", data2 = " << data2.getValue() << std::endl;

    // Тестируем копирование и присваивание
    Data data3(data1);  // конструктор копирования
    Data data4;
    data4 = data2;      // оператор присваивания

    std::cout << "\nПосле обмена копирования и присваивания:" << std::endl;
    std::cout << "data3 (копия data1) = " << data3.getValue() << std::endl;
    std::cout << "data4 (копия из data2) = " << data4.getValue() << std::endl;
    return 0;
}