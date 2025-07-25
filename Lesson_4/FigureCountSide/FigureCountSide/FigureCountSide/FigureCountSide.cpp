
#include<vector>
#include <iostream>
#include<string>
#include<Windows.h>

class figure
{
public:
	figure() {};
	const int  getsidecount()
	{
		return sidescount;
	}
	const std::string getname()
	{
		return nameF;
	}
protected:
	figure(std::string name, int side) :
		nameF{ name },
		sidescount{ side } {};	
private:
	int sidescount{};
	std::string nameF{ "Фигура" };
};
  
class Triangle: public figure
{
public:
	Triangle () :  figure("Треугольник", 3) {};
protected:
private:
};

class Quadrangle : public figure
{
public:
	Quadrangle() : figure("Четирехугольник", 4) {};
protected:
private:
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Название фигуры и количество сторон." << std::endl;
	figure Figure;
	Triangle Triang;
	Quadrangle Quad;
	std::cout << Figure.getname() << ":" << Figure.getsidecount() << std::endl;
	std::cout << Triang.getname() << ":" << Triang.getsidecount() << std::endl;
	std::cout << Quad.getname() << ":" << Quad.getsidecount() << std::endl;
}

