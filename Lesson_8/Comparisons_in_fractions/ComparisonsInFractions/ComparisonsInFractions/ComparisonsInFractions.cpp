#include <iostream>
#include <Windows.h>

class Fraction
{
private:
	int numerator_;
	int denominator_;

public:
	Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator)
	{
		if (denominator_ == 0)
		{
			throw std::runtime_error("Denominator равен 0. Решения нет.");
		}

	}

    // Перегрузка операторов сравнения как методов класса

    bool operator==(const Fraction& other) const 
    {
        return numerator_ == other.numerator_ && denominator_ == other.denominator_;
    }

    bool operator!=(const Fraction& other) const 
    {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const 
    {
        return numerator_ * other.denominator_ < other.numerator_ * denominator_;
    }

    bool operator>(const Fraction& other) const
    {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const 
    {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		Fraction f1(4, 7);
		Fraction f2(6, 11);

		std::cout  << "\n";
		std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
		std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
		std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
		std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
		std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
		std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';
	}
	catch (const std::exception& f1_)
	{
		std::cout << "\n";
		std::cout << f1_.what() << std::endl;
	}

	return 0;
}  
