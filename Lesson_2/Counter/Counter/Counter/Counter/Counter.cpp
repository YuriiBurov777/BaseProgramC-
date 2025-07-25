
#include<string>
#include <iostream>
#include<Windows.h>

namespace inp
{
    int stVal{0};
    char operat{};
    std::string a{};
}

class Counter
{
public:
    char Operator{};
    
   Counter()
   {
        this->countValue = 1;
   }
   Counter(int StartValue)
   {
        this->countValue = StartValue;
   }
   void setIncrDecr(char Operator)
   {
        if (Operator == '+')
        {
            this->countValue = countValue + 1;
        }
        if (Operator == '-')
        {
            this->countValue = countValue - 1;
        }
   }
     
   int const getValue( )
   {
       return countValue;
   }

private:
    int countValue{ 0 };

};

Counter Create(std::string a, int b);

int main()
{   
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет:" << std::endl;
    std::cin >> inp::a;

    if (inp::a == "да")
    {
       std::cout << "Введите начальное значение счётчика:" << std::endl;
       std::cin >> inp::stVal;
      
    }

     Counter myCount = Create(inp::a,inp::stVal);
     Counter* ptr = &myCount;
    
    do
    {
        std::cout << "Введите команду('+', '-', '=' или 'x') : " << std::endl;
        std::cin >> inp::operat;
        if ((inp::operat == '+') or (inp::operat == '-'))
        {
            ptr->setIncrDecr(inp::operat);
        }
        if (inp::operat == '=')
        {
            std::cout << ptr->getValue() << std::endl;
        }
       
    } while (inp::operat != 'х');

    std::cout << "До свидания" << std::endl;
}

Counter Create(std::string a, int b)
{
    if (a == "да")
    {
       return Counter (b);
    }
    else
    {
       return Counter();
    }
}
