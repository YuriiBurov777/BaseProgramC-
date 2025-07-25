
#include<string>
#include <iostream>
#include<Windows.h>

class Figure
{
public:
	Figure() {};
	std::string getName ()
	{
		return name;
	}
	virtual void Print() const
	{
		std::cout << name << std::endl;
	}
protected:
	Figure(std::string Name) :name(Name) {};
	std::string name = "Фигура";
private:
	

};

class Triangel: public Figure
{
public:
	
	Triangel():Figure ("Треугольник")
	{}
	void Print () const override 
	{
		std::cout << name << std::endl;
		std::cout << "Стороны: " << "a = " << a << "  b = " << b << "  c = " << c << std::endl;
		std::cout <<  "Углы: " << "A = " << A << "  B = " << B << "  C = " << C << std::endl;
		std::cout << std::endl;
	}
protected:
	int a{10};
	int b{20};
	int c{30};
	int A{50};
	int B{ 60 };
	int C{ 70 };
	Triangel(int a, int b, int c, int A, int B, int C, std::string name_t)
		    :Figure(name_t), a(a), b(b), c(c), A(A), B(B), C(C) {};
private:

};
//Класс прямоугольный треугольник
class Trian_pryamoyg : public Triangel
{
public:
	Trian_pryamoyg() : Triangel(10, 20, 30, 50, 60, 90, "Прямоугольный треугольник") {
	};
protected:
private:
};

//Класс Равнобедренный треугольник:
class Trian_ravnobedr : public Triangel
{
public:
	Trian_ravnobedr(): Triangel(10, 20, 10, 50, 60, 50, "Равнобедренный треугольник") {
	};
protected:
private:
};
//Класс Равносторонний треугольник:
class Trian_ravnostor : public Triangel
{
public:
	Trian_ravnostor(): Triangel(30, 30, 30, 60, 60, 60, "Равносторонний треугольник") {
	};
protected:
private:
};
//Класс четырехугольник
class Quadrilateral : public Figure
{
public:

	Quadrilateral() :Figure("Четырехугольник"){};

	void Print() const override
	{
		std::cout << name << std::endl;
		std::cout << "Стороны: " << "a = " << a << "  b = " << b << "  c = " << c << "  d = " << d<< std::endl;
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
	int D{80};
	Quadrilateral(int a, int b, int c, int d, int A, int B, int C, int D, std::string name_t)
		:Figure(name_t), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
	};
private:

};

//Класс Прямоугольник:
class Rectangle1 : public Quadrilateral
{
public:
	Rectangle1(): Quadrilateral(30, 30, 30, 20, 60, 60, 60, 90, "Прямоугольник"){
	};
protected:
private:
};
//Класс Квадрат:
class Quadro : public Quadrilateral
{
public:
	Quadro(): Quadrilateral(20, 20, 20, 20, 90, 90, 90, 90, "Квадрат"){
	};
protected:
private:
};
//Класс Параллелограмм:
class Parallelogram : public Quadrilateral
{
public:
	Parallelogram():Quadrilateral(20, 30, 20, 30, 30, 40, 30, 40, "Параллелограмм") {
	};
protected:
private:
};
//Класс Ромб:
class Rhomb : public Quadrilateral
{
public:
	Rhomb():Quadrilateral(30, 30, 30, 30, 30, 40, 30, 40, "Ромб"){
	};
protected:
private:
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
