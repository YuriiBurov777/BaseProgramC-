
#include <iostream>
#include "CheckSum.h"

int main()
{
	ExtArray<int> v1{ 1,1,0,1};
	//ExtArray<double> v1{ 4.2, 2, 7, 3, -5, 0, -3, 1 };
	try
	{
		//v1.checkSum();
		std::cout << v1.checkSum();
		//Logger::WriteMessage(L"===Решение найдено и верно===");
		//Assert::AreEqual(2, v1.checkSum());
	}
	catch (const std::invalid_argument& e)
	{
	       std::cout << e.what();
		//Logger::WriteMessage(L"===Тест ошибка типа данных===");
		//Assert::IsTrue(message.find("Ошибка") != std::string::npos, L"Не найдено Trow bad_typeid");
	}
	catch (const std::logic_error& e)
	{
		std::cout << e.what();
		//Logger::WriteMessage(L"===Тест масив int содержит отличные значения от 0 и 1===");
		//Assert::IsTrue(message.find("Массив") != std::string::npos, L"Не найдено Trow logic_error");
	}
}

