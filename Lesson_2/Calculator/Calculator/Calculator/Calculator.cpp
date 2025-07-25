

#include <iostream>

namespace inp
{
    double num1{ 0 };
    double  num2{ 0 };
}

class Calculator
{
public:

    
    bool setnum1(double num1)
    {
        if (num1 > 0)
        {
            this->num1 = num1;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool setnum2(double num2)
    {
        if (num2 > 0)
        {
            this->num2 = num2;
            return true;
        }
        else
        {
            return false;
        }
    }

    double Add()
    {
        return num1 + num2;
    }
    double Multiply()
    {
        return num1 * num2;
    }
    double Subtract_1_2()
    {
        return num1 - num2;
    }
    double Subtract_2_1()
    {
        return num2 - num1;
    }
    double Divide_1_2()
    {
        return num1 / num2;
    }
    double Divide_2_1()
    {
        return num2 / num1;
    }

    double getnum1()
    {
        return num1;
    }
    double getnum2()
    {
        return num2;
    }

private:
    double num1{ 0 };
    double num2{ 0 };

};

void Print(Calculator calc);

int main()
{
    setlocale(LC_ALL, "Russian");
    Calculator calc;

    do
   {
    std::cout << "Веедите число Num1 больше 0: " << std::endl;
    std::cin >> inp::num1;
    std::cout << "Веедите число Num2 больше 0: " << std::endl;
    std::cin >> inp::num2;
  
    if ((calc.setnum1(inp::num1) == true) and (calc.setnum2(inp::num2)==true))
    {
        Print (calc);
    }
    if ((calc.setnum1(inp::num1) == false) and (calc.setnum2(inp::num2) == false))
    {
        std::cout << " Неверное значение num1 и num2."<< std::endl;
    }
    if ((calc.setnum1(inp::num1) == true) and (calc.setnum2(inp::num2) == false))
    {
        std::cout << " Неверное значение num2." << std::endl;
    }
    if ((calc.setnum1(inp::num1) == false) and (calc.setnum2(inp::num2) == true))
    {
        std::cout << " Неверное значение num1." << std::endl;
    }
    std::cout  << std::endl;
   } while (true);
}

void Print(Calculator calc)
{
    std::cout << "num1 + num2: " << calc.Add() << std::endl;
    std::cout <<"num1 - num2: " << calc.Multiply() << std::endl;
    std::cout <<"num2 - num1: " << calc.Subtract_1_2() << std::endl;
    std::cout << "num1 * num2: " << calc.Subtract_2_1() << std::endl;
    std::cout << "num1 / num2: " << calc.Divide_1_2() << std::endl;
    std::cout << "num2 / num1: " << calc.Divide_2_1() << std::endl;
}
 