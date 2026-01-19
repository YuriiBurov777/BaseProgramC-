#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <windows.h>

// Асинхронный поиск индекса минимального элемента
int find_min_index_async(const std::vector<int>& arr, int start) {
    int min_index = start;
    for (int i = start + 1; i < arr.size(); i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

// Сортировка выбором с асинхронным поиском минимума
void select_sort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        // Запускаем асинхронный поиска
        auto future = std::async(std::launch::async, find_min_index_async, std::ref(arr), i);

        // Ждем результат
        int min_index = future.get();

        // Меняем местами
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //Создаем массив
    std::vector<int> arr = { 644, 125, 12, 322, 101, 33, 90, 1 };

    std::cout << "До сортировки: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;

    //Запускаем сортировку
    select_sort(arr);

    std::cout << "После сортировки: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}