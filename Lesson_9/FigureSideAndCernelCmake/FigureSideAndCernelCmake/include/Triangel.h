
#pragma once
#include <string>
#include"Figure.h"

class Triangel : public Figure
{
public:

	Triangel() :Figure("Треугольник")
	{
	}
	void Print() const override;
	
protected:
	int a{ 10 };
	int b{ 20 };
	int c{ 30 };
	int A{ 50 };
	int B{ 60 };
	int C{ 70 };
	Triangel(int a, int b, int c, int A, int B, int C, std::string name_t)
		:Figure(name_t), a(a), b(b), c(c), A(A), B(B), C(C) {
	};
};

