
#include<string>
#include <iostream>
#include "OutputStruct.h"

struct Adresse
{
    std::string City;
    std::string Street;
    int NumberHaus;
    int NumberWohnung;
    int Index;
};

void Print(const Adresse* a);


int main()
{
   setlocale(LC_ALL, "Russian");
   Adresse adress[2]{};
   auto * ptr{ adress };
   ptr[0] = { "Москва","Арбат",12 ,8,123456 };
   ptr[1] = { "Ижевск","Пушкина",59 ,143,953769 };
   
   Print(ptr);
}

void Print(const Adresse* a)
{
    for (int i = 0; i < 2; i++)
    {
        std::cout << "Город:\t" << a[i].City << std::endl;
        std::cout << "Улица:\t" << a[i].Street << std::endl;
        std::cout << "Номер дома:\t" << a[i].NumberHaus << std::endl;
        std::cout << "Номер квартиры:\t" << a[i].NumberWohnung << std::endl;
        std::cout << "Индекс:\t" << a[i].Index << "\n" << std::endl;
    }
}
