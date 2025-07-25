
#include <string>
#include <iostream>

namespace input_number
{
	int number_monat{0};
}
enum class Monat
{
	Januar=1,
	Februar,
	Marz,
	April,
	Mai,
	Juni,
	Juli,
	August,
	September,
	Oktober,
	November,
	Dezember
};

Monat sel_monat (int variable);

void Print (Monat name_monat);

int main()
{
	setlocale(LC_ALL, "Russian");
	do
	{
		std::cout << "Введите номер месяца или введите 0 для выхода\n" << std::endl;
		std::cin >> input_number::number_monat;
		std::cout << std::endl;
		
		if (input_number::number_monat !=0)
		{
			Print(sel_monat(input_number::number_monat));
			std::cout << std::endl;
		}

	} while (input_number::number_monat !=0);

	std::cout << "До свидания!" << std::endl;

	return 0;
}

Monat sel_monat (int variable)
{
	return static_cast<Monat>(variable);
	
}

void Print(Monat name_monat)
{
	switch (name_monat)
	{
	case Monat::Januar:
		std::cout<< "Januar" << std::endl;
		break;
	case Monat::Februar:
		std::cout << "Februa" << std::endl;
		break;
	case Monat::Marz:
		std::cout << "Marz" << std::endl;
		break;
	case Monat::April:
		std::cout << "April" << std::endl;
		break;
	case Monat::Mai:
		std::cout << "Mai" << std::endl;
		break;
	case Monat::Juni:
		std::cout << "Juni" << std::endl;
		break;
	case Monat::Juli:
		std::cout << "Juli" << std::endl;
		break;
	case Monat::August:
		std::cout << "August" << std::endl;
		break;
	case Monat::September:
		std::cout << "September" << std::endl;
		break;
	case Monat::Oktober:
		std::cout << "Oktober" << std::endl;
		break;
	case Monat::November:
		std::cout << "November" << std::endl;;
		break;
	case Monat::Dezember:
		std::cout << "Dezember" << std::endl;
		break;
	default:
		std::cout << "Попробуйте еще раз. У Вас получиться." << std::endl;
		break;
	}
}
