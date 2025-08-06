#pragma once
#include <iostream>

class Figure
{
	public:
		Figure() {};

		std::string getName();
		
		virtual void Print() const;
		
	protected:
		Figure(std::string Name) :name(Name) {};
		std::string name = "Фигура";

};

