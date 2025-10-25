#include <iostream>
#include <vector>
#include <algorithm>


class Counter {
private:
    int sum{0};
    int count{0};

public:
    Counter() = default;


    // Функтор - перегруженный оператор ()
    void operator()(int number) {
          if ((number % 3 == 0) and (number >= 3)) {
            sum += number;
            count++;
            // Вывод подходящего числа
            std::cout << number << std::endl;
          }
    }

    // Метод для получения суммы
    int get_sum() const {
        return sum;
    }

    // Метод для получения количества
    int get_count() const {
        return count;
    }
};

int main() {
    std::vector<int> vec = { 4, 1, 3, 6, 25, 54 };

    Counter _Funct_;
    std::cout << "Count_Start: " << _Funct_.get_count() << std::endl;
    std::cout << "Sum_Start: " << _Funct_.get_sum() << std::endl;

    for(int num:vec){
        _Funct_(num);
    }

    std::cout << "get_sum() = " << _Funct_.get_sum() << std::endl;
    std::cout << "get_count() = " << _Funct_.get_count() << std::endl;

    return 0;
}