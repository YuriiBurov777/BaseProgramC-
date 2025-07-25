#include <typeinfo>
#include<string>
#include <iostream>


struct Person_Rechnung
{
	int	Rechnung;
	double Balance{5000};
	std::string Name;
};

void Print(Person_Rechnung* person);


int main()
{
	Person_Rechnung person;
	Person_Rechnung* ptr{ &person };
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите номер счёта:";
	std::cin >> ptr->Rechnung;
	

	std::cout << "Введите имя:";
	std::cin >> ptr->Name;
	std::cout << std::endl;

	std::cout << "Баланс: "<<ptr->Balance << std::endl;
	std::cout << std::endl;

	std::cout << "Введите сумму:";
	std::cin >> ptr->Balance;
	std::cout << std::endl;
	
	Print(ptr);
}

void Print(Person_Rechnung* person)
{
	std::cout << "Ваш счет: " << person->Name << ',' << person->Rechnung << ',' << person->Balance << std::endl;
}
