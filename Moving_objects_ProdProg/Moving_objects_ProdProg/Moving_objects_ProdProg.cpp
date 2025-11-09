
#include <iostream>
#include <vector>


std::vector <std::string> one = { "test_string1", "test_string2" };
std::vector <std::string> two;

// Перемещаем с помощью move т.к. сложный объект
void move_vectors() {
	two = std::move(one);
}

// Печать первого вектора после перемещения
void Print1() {
	std::cout << "Vector1" << std::endl;
		for (auto vecCell : one)
		{
			std::cout << vecCell << std::endl;
		}
	std::cout << std::endl;
}

// Печатаем результат
void Print2() {
	std::cout << "Vector2" << std::endl;
		for(auto vecCell: two)
		{
			std::cout << vecCell << std::endl;
		}
}


int main()
{
	move_vectors();
	Print1();
	Print2();

	return 0;
}

