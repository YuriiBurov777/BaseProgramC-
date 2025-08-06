
#include "Triangel.h"

void Triangel::Print() const
{
	std::cout << name << std::endl;
	std::cout << "Стороны: " << "a = " << a << "  b = " << b << "  c = " << c << std::endl;
	std::cout << "Углы: " << "A = " << A << "  B = " << B << "  C = " << C << std::endl;
	std::cout << std::endl;
}
