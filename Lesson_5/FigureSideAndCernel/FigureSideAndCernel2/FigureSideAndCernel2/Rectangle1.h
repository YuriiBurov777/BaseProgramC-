
#pragma once
#include <string>
#include"Quadrilateral.h"

//Класс Прямоугольник:
class Rectangle1 : public Quadrilateral
{
public:
	Rectangle1() : Quadrilateral(30, 30, 30, 20, 60, 60, 60, 90, "Прямоугольник") {
	};
};

