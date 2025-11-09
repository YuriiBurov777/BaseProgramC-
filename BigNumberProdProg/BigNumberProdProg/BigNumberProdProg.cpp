#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>

class big_integer {

public:
    // Конструктор из строки
    big_integer(const std::string& num) : number(num) {}

    // Конструктор копирования
    big_integer(const big_integer& other) noexcept : number(std::move(other.number)) {}

    // Конструктор перемещения
    big_integer(big_integer&& other) noexcept : number(std::move(other.number)) {}

    // Копирующий оператор присваивания
    big_integer& operator=(const big_integer& other) noexcept {
        if (this != &other) {
            number = std::move(other.number);
        }
        return *this;
    }

    // Перемещающий оператор присваивания
    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            number = std::move(other.number);
        }
        return *this;
    }

    // Оператор сложения
    big_integer operator+(const big_integer& other) const {
       
        std::string result;
        int memory{ 0 };
        int i = number.size() - 1;
        int j = other.number.size() - 1;

        while (i >= 0 || j >= 0 || memory) {
            int sum = memory;
            if (i >= 0) sum += number[i--] - '0';
            if (j >= 0) sum += other.number[j--] - '0';
            result.push_back((sum % 10) + '0');
            memory = sum / 10;
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    // Оператор умножения на число
    big_integer operator*(const big_integer& other) const {
        
        if (number == "0" || other.number == "0") {
            return big_integer("0");
        }

        std::string result;

        for (int j = other.number.size() - 1; j >= 0; j--) {
            int Num2 = other.number[j] - '0';              // Цифра второго числа
            if (Num2 == 0) continue;                       // Пропускаем умножение на 0

            std::string temp_result;
            int memory = 0;

            // Умножаем на текущую цифру
            for (int i = number.size() - 1; i >= 0; i--) {
                int Num1 = number[i] - '0';
                int Num1_Num2 = Num1 * Num2 + memory;
                temp_result.push_back((Num1_Num2 % 10) + '0');
                memory = Num1_Num2 / 10;
            }

            while (memory) {
                temp_result.push_back((memory % 10) + '0');
                memory /= 10;
            }

            std::reverse(temp_result.begin(), temp_result.end());

            // Добавляем нули для сдвига разрядов
            int zero_add = other.number.size() - 1 - j;
            temp_result.append(zero_add, '0');  // Добавляем zeros_to_add нулей

            result = result + temp_result;
        }

        return result;
    }

    // Вывод
    std::string GetValue() const {
        return number;
    }

    private:
    std::string number;

};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");

    // Тестируем копирующий оператор присваивания
    auto number3 = big_integer("999");
    number3 = number1;  // Копирующее присваивание
    std::cout << "После копирования: " << number3.GetValue() << std::endl; // 114575

    // Тестируем перемещающий оператор присваивания
    auto number4 = big_integer("888");
    number4 = std::move(number2);  // Перемещающее присваивание
    std::cout << "После перемещения: " << number4.GetValue() << std::endl; // 78524

    // Сложение
    auto result = number1 + number4;
    std::cout << "Сумма: " << result.GetValue() << std::endl; // 193099

    // Умножение
    auto mult = number1 * number4;
    std::cout << "Умножение: " << mult.GetValue() << std::endl; // 4583002291500572875009166000008020250000

    return 0;
}