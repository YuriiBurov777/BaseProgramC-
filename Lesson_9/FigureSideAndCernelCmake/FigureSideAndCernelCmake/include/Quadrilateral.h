
#pragma once
#include <string>
#include"Figure.h"

//Класс четырехугольник
class Quadrilateral : public Figure
{
public:

	Quadrilateral() :Figure("Четырехугольник") {};

	void Print() const override;
	
protected:
	int a{ 10 };
	int b{ 20 };
	int c{ 30 };
	int d{ 40 };
	int A{ 50 };
	int B{ 60 };
	int C{ 70 };
	int D{ 80 };
	Quadrilateral(int a, int b, int c, int d, int A, int B, int C, int D, std::string name_t)
		:Figure(name_t), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
	};
};
