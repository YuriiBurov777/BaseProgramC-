
#include <iostream>
#include<Windows.h>
#include"Figure.h"
#include"Triangel.h"
#include"Trian_pryamoyg.h"
#include"Trian_ravnobedr.h"
#include"Trian_ravnostor.h"
#include"Quadrilateral.h"
#include"Quadro.h"
#include"Rectangle1.h"
#include"Parallelogram.h"
#include"Rhomb.h"
#include"Print.h"





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



