
#include<string>
#include <iostream>
#include<Windows.h>
//Класс фигура
class Figure
{
public:
	Figure()
	{
		name = "Фигура";
		countside = 0;
	};

	virtual void Print()
	{
		std::cout << name << std::endl;
		std::cout << "Создан" << std::endl;
		std::cout << "Количество сторон = " << countside << std::endl;
		std::cout << std::endl;
	}
	
protected:
	Figure(std::string Name, int side)
		:name(Name), countside(side) {
	};
	std::string name = "Фигура";
	int countside{};
};
// Класс треугольник
class Triangel : public Figure
{
public:

	Triangel() :Figure("Треугольник", 3)
	{

		if (A + B + C != 180)

		{
			throw std::domain_error("Сумма углов A,B,C не равна 180 градусов");
		}
	}

	void Print() override
	{
		std::cout << name << std::endl;
		std::cout << "Создан" << std::endl;
		std::cout << "Количество сторон = " << countside << std::endl;
		std::cout << "Стороны: " << "a = " << a << "  b = " << b << "  c = " << c << std::endl;
		std::cout << "Углы: " << "A = " << A << "  B = " << B << "  C = " << C << std::endl;
		std::cout << std::endl;
	}
protected:
	int a{ 10 };
	int b{ 20 };
	int c{ 30 };
	int A{ 50 };
	int B{ 60 };
	int C{ 70 };
	Triangel(int a, int b, int c, int A, int B, int C, std::string name_t)
		:Figure(name_t, 3), a(a), b(b), c(c), A(A), B(B), C(C) { };
};

//Класс прямоугольный треугольник
class Trian_pryamoyg : public Triangel
{
public:
	Trian_pryamoyg() :Triangel(10, 20, 30, 50, 60, 90, "Прямоугольный треугольник") 
	{
		if (A + B + C != 180)
		{
			throw std::domain_error("Сумма углов A,B,C не равна 180 градусов");
		}
		if (C != 90)
		{
			throw std::domain_error("Угол С не равен 90 градусов");
		}

	};

};

//Класс Равнобедренный треугольник:
class Trian_ravnobedr : public Triangel
{
public:
	Trian_ravnobedr() :Triangel(10, 20, 10, 50, 60, 50, "Равнобедренный треугольник")
	{
		if (A + B + C != 180)
		{
			throw std::domain_error("Сумма углов A,B,C не равна 180 градусов");
		}
		if (a != c)
		{
			throw std::domain_error("Стороны а и с не равны");
		}
		if (A != C)
		{
			throw std::domain_error("Углы А и С не равны");
		}

	};

};
//Класс Равносторонний треугольник:
class Trian_ravnostor : public Triangel
{
public:
	Trian_ravnostor() :Triangel(30, 30, 30, 60, 60, 60, "Равносторонний треугольник") 
	{
		
		if ((a != b) || (b != c) || (c != a))
		{
			throw std::domain_error("Стороны а,b и с не равны");
		}
		if ((A != B) || (B != C) || (C != A))
		{
			throw std::domain_error("Углы А,B и С не равны");
		}
	};

};
//Класс четырехугольник
class Quadrilateral : public Figure
{
public:

	Quadrilateral() :Figure("Четырехугольник", 4) 
	{
		if (A + B + C + D != 360)
		{
			throw std::domain_error("Сумма углов A,B,C и D не равны 360 градусов");
		}
	};

	void Print() override
	{
		std::cout << name << std::endl;
		std::cout << "Создан" << std::endl;
		std::cout << "Количество сторон = " << countside << std::endl;
		std::cout << "Стороны: " << "a = " << a << "  b = " << b << "  c = " << c << "  d = " << d << std::endl;
		std::cout << "Углы: " << "A = " << A << "  B = " << B << "  C = " << C << "  D= " << D << std::endl;
		std::cout << std::endl;
	}
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
		:Figure(name_t, 4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
	};
};

//Класс Прямоугольник:
class Rectangle1 : public Quadrilateral
{
public:
	Rectangle1() :Quadrilateral(30, 30, 30, 20, 60, 60, 60, 90, "Прямоугольник") 
	{
		if ((a != c) || (b != d))
		{
			throw std::domain_error("Стороны а и с не равны. Стороны b и d не равны");
		}
		if ((A != C) || (B != D))
		{
			throw std::domain_error("Углы A и C не равны. Углы B и D не равны.");
		}

	};

};
//Класс Квадрат:
class Quadro : public Quadrilateral
{
public:
	Quadro() :Quadrilateral(20, 20, 20, 20, 90, 90, 90, 90, "Квадрат")
	{
		if ((a + c) != (b + d))
		{
			throw std::domain_error("Стороны а,b,с и d не равны");
		}

		if ((A != 90) || (B != 90) || (C != 90) || (D != 90))
		{
			throw std::domain_error("Углы A,C,B и D не равны.");
		}
	};

};
//Класс Параллелограмм:
class Parallelogram : public Quadrilateral
{
public:
	Parallelogram() :Quadrilateral(20, 30, 20, 30, 30, 40, 30, 40, "Параллелограмм") 
	{
		if ((a != c) || (b != d))
		{
			throw std::domain_error("Стороны а и с не равны. Стороны b и d не равны.");
		}
		if ((A != C) || (B != D))
		{
			throw std::domain_error("Углы A и C не равны. Углы B и D не равны.");
		}
	};

};
//Класс Ромб:
class Rhomb : public Quadrilateral
{
public:
	Rhomb() :Quadrilateral(30, 30, 30, 30, 30, 40, 30, 40, "Ромб") 
	{
		if ((a + c) != (b + d))
		{
			throw std::domain_error("Стороны а,b,с и d не равны");
		}
		if ((A != C) || (B != D))
		{
			throw std::domain_error("Углы A и C не равны. Углы B и D не равны.");
		}
	};
	

};
//Выодинформации на экран
void PrintFigure(Figure* figure);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Figure figure;
	PrintFigure(&figure);

	try
	{
	   Triangel triangel;
	   PrintFigure(&triangel);
	}
	catch (const std::exception& trian)
	{
		std::cout << "Ошибка создания фигуры Треугольник. Причина: " << trian.what() << std::endl;
		std::cout << std::endl;
	}
	
	try
	{
       Trian_pryamoyg triangel_pramoug;
	   PrintFigure(&triangel_pramoug);
	}
	catch (const std::exception& trian_pr)
	{
		std::cout << "Ошибка создания фигуры Прямоугольный треугольник. Причина: " << trian_pr.what() << std::endl;
		std::cout << std::endl;
	}

	try
	{
	   Trian_ravnobedr triangel_ravnobed;
	   PrintFigure(&triangel_ravnobed);
	}
	catch (const std::exception& trian_rav)
	{
		std::cout << "Ошибка создания фигуры Равнобедренный треугольник. Причина: " << trian_rav.what() << std::endl;
		std::cout << std::endl;
	}
	
	try
	{
	   Trian_ravnostor triangel_ravnostor;
	   PrintFigure(&triangel_ravnostor);
	}
	catch (const std::exception& trian_ravst)
	{
		std::cout << "Ошибка создания фигуры Равносторонний треугольник. Причина: " << trian_ravst.what() << std::endl;
		std::cout << std::endl;
	}

	try
	{
	   Quadrilateral quadrilateral;
	   PrintFigure(&quadrilateral);
	}
	catch (const std::exception& quad)
	{
		std::cout << "Ошибка создания фигуры Четырехугольик. Причина: " << quad.what() << std::endl;
		std::cout << std::endl;
	}
	
	try
	{
		Rectangle1 rectangle1;
		PrintFigure(&rectangle1);
	}
	catch (const std::exception& rect)
	{
		std::cout << "Ошибка создания фигуры Прямоугольник. Причина: " << rect.what() << std::endl;
		std::cout << std::endl;
	}
	
	try
	{
		Quadro quadro;
		PrintFigure(&quadro);
	}
	catch (const std::exception& quadr)
	{
		std::cout << "Ошибка создания фигуры Квадрат. Причина: " << quadr.what() << std::endl;
		std::cout << std::endl;
	}

	try
	{
		Parallelogram parallelogram;
		PrintFigure(&parallelogram);
	}
	catch (const std::exception& parall)
	{
		std::cout << "Ошибка создания фигуры Параллелограм. Причина: " << parall.what() << std::endl;
		std::cout << std::endl;
	}
	
	try
	{
      Rhomb rhomb;
	  PrintFigure(&rhomb);
	}
	catch (const std::exception& rhom)
	{
		std::cout << "Ошибка создания фигуры Ромб. Причина: " << rhom.what() << std::endl;
		std::cout << std::endl;
	}
	return 0;
}


void PrintFigure(Figure* figure)
{
	figure->Print();
}