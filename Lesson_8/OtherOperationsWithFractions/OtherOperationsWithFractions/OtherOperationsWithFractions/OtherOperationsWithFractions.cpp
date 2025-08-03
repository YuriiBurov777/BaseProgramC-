

#include <iostream>
#include <Windows.h>
#include <string>


class Fraction {
private:
    int numerator;
    int denominator;

    // Сокращение дроби
    int NOD(int numerator, int denominator)
    {
        numerator = abs(numerator);
        denominator = abs(denominator);

        while (numerator > 0 && denominator > 0)

            if (numerator > denominator)
                numerator %= denominator;

            else
                denominator %= numerator;

        return numerator + denominator;
    }

public:

    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::runtime_error("Знаменатель равен 0. Решения нет.");
        }
        NOD(numerator, denominator);
    }

    //Доступ к приват 
    int getNumerat() const
    {
        return numerator;
    }

    int getDenom() const
    {
        return denominator;
    }

    // Арифметические операции
    Fraction operator+(const Fraction& other) const
    {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const
    {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const
    {
        return Fraction(numerator * other.numerator,
            denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const
    {
        if (other.numerator == 0)
        {
            throw std::runtime_error("Деление на ноль. Ошибка");
        }
        return Fraction(numerator * other.denominator,
            denominator * other.numerator);
    }

    //  Инкремент префиксный
    Fraction& operator++()
    {
        numerator += denominator;
        return *this;
    }

    // Инкремент постфиксный
    Fraction operator++(int)
    {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    //  Декремент префиксный
    Fraction& operator--()
    {
        numerator -= denominator;
        return *this;
    }

    // Декремент постфиксный
    Fraction operator--(int)
    {
        Fraction temp = *this;
        --(*this);
        return temp;
    }
};

// Перегрузка оператора <<. Вывод нa консоль
std::ostream& operator << (std::ostream& result, const Fraction fraction)
{
    if (fraction.getDenom() == 1)
    {
        result << fraction.getNumerat();
    }
    else
    {
        result << fraction.getNumerat() << " / " << fraction.getDenom();
    }
    return result;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int num1{};
    int den1{};
    int num2{};
    int den2{};

    do
    {

   
      std::cout << "Введите числитель дроби 1: ";
      std::cin >> num1;
      std::cout << "Введите знаменатель дроби 1: ";
      std::cin >> den1;
      std::cout << "Введите числитель дроби 2: ";
      std::cin >> num2;
      std::cout << "Введите знаменатель дроби 2: ";
      std::cin >> den2;

    try
    {
        Fraction f1(num1, den1);
        Fraction f2(num2, den2);

        std::cout << f1 << " + " << f2 << " = " << f1 + f2 << std::endl;
        std::cout << f1 << " - " << f2 << " = " << f1 - f2 << std::endl;
        std::cout << f1 << " * " << f2 << " = " << f1 * f2 << std::endl;

        try
        {
            std::cout << f1 << " / " << f2 << " = " << f1 / f2 << std::endl;
        }
        catch (const std::exception& divine)
        {
            std::cout << std::endl;
            std::cout << divine.what() << std::endl;
            std::cout << std::endl;
        }

        std::cout << ++f1 << " * " << f2 << " = " << f1 * f2 << std::endl;
        std::cout << "Значение дроби 1 =" << f1 << std::endl;
        std::cout << f1-- << " * " << f2 << " = " << f1 * f2 << std::endl;
        std::cout << "Значение дроби 1 =" << f1 << std::endl;
        break;
    }
    catch (const std::exception& f)
    {
        std::cout << std::endl;
        std::cout << f.what() << std::endl;
        std::cout << std::endl;
    }
   
    } while (true);



    return 0;
};