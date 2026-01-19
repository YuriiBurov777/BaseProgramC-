#include <future>
#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>

template<typename Iterator, typename V>
void parallel_for_each(Iterator first, Iterator last, V LambdaFunc) {
    size_t size = std::distance(first, last);
    // Если мало элементов - обрабатываем последовательно
    if (size <= 4) {
        std::for_each(first, last, LambdaFunc);
        return;
    }
    // Делим пополам
    Iterator mid = first;
    std::advance(mid, size / 2);

    // Левая часть в отдельном потоке
    auto left = std::async(parallel_for_each<Iterator, V>,first, mid, LambdaFunc);

    // Правую часть обрабатываем здесь
    parallel_for_each <Iterator, V> (mid, last, LambdaFunc);

    // Ждем левую часть
    left.get();
}

int main() {

    std::vector<int> Numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Умножаем все элементы на 3
    parallel_for_each(Numbers.begin(), Numbers.end(),
        [](int& x) { x *= 3; });

    // Выводим результат
    for (int n : Numbers) {
        std::cout << n << " ";
    }
   

    return 0;
}