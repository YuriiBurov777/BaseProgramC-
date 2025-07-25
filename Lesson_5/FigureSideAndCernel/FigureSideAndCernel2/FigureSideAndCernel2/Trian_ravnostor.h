
#pragma once
#include <string>
#include"Triangel.h"

//Класс Равносторонний треугольник:
class Trian_ravnostor : public Triangel
{
public:
	Trian_ravnostor() : Triangel(30, 30, 30, 60, 60, 60, "Равносторонний треугольник") {
	};
};

