
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
		 countside=0;	
	};
	
	virtual void Print() 
	{
		std::cout << name << std::endl;
		std::cout << (Chek() ? "Правильная" : "Неправильная") << std::endl;
		std::cout << "Количество сторон = " << countside << std::endl;
		std::cout << std::endl;
	}
	virtual bool Chek() 
	{
		return true;
	}
protected:
	Figure(std::string Name,int side) 
		  :name(Name), countside(side) {};
	std::string name = "Фигура";
	int countside{};
};
// Класс треугольник
class Triangel : public Figure
{
public:
	
	Triangel() :Figure("Треугольник", 3)
	{
	}
	bool Chek()  override
	{
		return A + B + C == 180 ?  true : false;
	}
	void Print() override
	{
		std::cout << name << std::endl;
		std::cout <<( Chek() ? "Правильная" : "Неправильная") << std::endl;
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
		:Figure(name_t, 3), a(a), b(b), c(c), A(A), B(B), C(C){
	};
};

//Класс прямоугольный треугольник
class Trian_pryamoyg : public Triangel
{
public:
	Trian_pryamoyg():Triangel(10, 20, 30, 50, 60, 90,"Прямоугольный треугольник") {
	};	
	bool Chek() override
	{
		return ((A + B + C == 180)&& ((C==90)||(A==90)||(B==90))) ? true : false;
	}
};

//Класс Равнобедренный треугольник:
class Trian_ravnobedr : public Triangel
{
public:
	Trian_ravnobedr():Triangel(10, 20, 10, 50, 60, 50,"Равнобедренный треугольник") {
	};
	bool Chek() override
	{
		return ((A + B + C == 180) && ((A==B)||(B==C)||(A==C))) ? true : false;
	}
};
//Класс Равносторонний треугольник:
class Trian_ravnostor : public Triangel
{
public:
	Trian_ravnostor():Triangel(30, 30, 30, 60, 60, 60,"Равносторонний треугольник") {
	};
	bool Chek() override
	{
		return ((a==b)&&(b==c)&&(c==a)&&(A + B + C==180))  ? true : false;
	}
};
//Класс четырехугольник
class Quadrilateral : public Figure
{
public:

	Quadrilateral() :Figure("Четырехугольник",4) {
	};
	bool Chek()  override
	{
		return A + B + C + D == 360 ? true : false;
	}
	void Print() override
	{
		Chek();
		std::cout << name << std::endl;
		std::cout << (Chek() ? "Правильная" : "Неправильная") << std::endl;
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
		:Figure(name_t,4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
	};
};

//Класс Прямоугольник:
class Rectangle1 : public Quadrilateral
{
public:
	Rectangle1():Quadrilateral(30, 30, 30, 20, 60, 60, 60, 90, "Прямоугольник"){
	};
	bool Chek()  override
	{
		return ((a==c)&&(b==d)&&(A==90)&&(B==90)&&(C==90)&&(D==90)) ? true : false;
	}
};
//Класс Квадрат:
class Quadro : public Quadrilateral
{
public:
	Quadro():Quadrilateral(20, 20, 20, 20, 90, 90, 90, 90, "Квадрат"){
	};
	bool Chek()  override
	{
		return (((a+c)==(b+d)) && (A ==90)&&( B ==90)&&( C ==90)&&( D == 90)) ? true : false;
	}
};
//Класс Параллелограмм:
class Parallelogram : public Quadrilateral
{
public:
	Parallelogram():Quadrilateral(20, 30, 20, 30, 30, 40, 30, 40, "Параллелограмм"){
	};
	bool Chek()  override
	{
		return ((A+B+C+D==360)&&(a == c)&&(b==d) && (A == C)) ? true : false;
	}
};
//Класс Ромб:
class Rhomb : public Quadrilateral
{
public:
	Rhomb():Quadrilateral(30, 30, 30, 30, 30, 40, 30, 40, "Ромб"){
	};
	bool Chek()  override
	{
		return (((a + c) == (b + d)) && (A + B + C + D == 360) && (A == C)) ? true : false;
	}
};
//Выодинформации на экран
void PrintFigure(Figure* figure);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Figure figure;
	Triangel triangel;
	Trian_pryamoyg triangel_pramoug;
	Trian_ravnobedr triangel_ravnobed;
	Trian_ravnostor triangel_ravnostor;
	Quadrilateral quadrilateral;
	Rectangle1 rectangle1;
	Quadro quadro;
	Parallelogram parallelogram;
	Rhomb rhomb;

	PrintFigure(&figure);	
	PrintFigure(&triangel);	
	PrintFigure(&triangel_pramoug);	
	PrintFigure(&triangel_ravnobed);	
	PrintFigure(&triangel_ravnostor);	
	PrintFigure(&quadrilateral);	
	PrintFigure(&rectangle1);	
	PrintFigure(&quadro);	
	PrintFigure(&parallelogram);	
	PrintFigure(&rhomb);

	return 0;
}


void PrintFigure(Figure* figure)
{
	figure->Print();
}
