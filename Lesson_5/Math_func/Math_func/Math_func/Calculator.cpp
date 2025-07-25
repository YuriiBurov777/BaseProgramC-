#include "Calculator.h"

void Calculator::setnum1(double num1) { this->num1 = num1; }

void Calculator::setnum2(double num2) { this->num2 = num2; }

void Calculator::setvalue(int value) { this->value = value; }

bool Calculator::chekOperator() const
{
	if ((num2 == 0) && (value == 4)) { return false; }
	else { return true; }
}

double Calculator::Math_op()const
{
	switch (value)
	{
	case 1:  //Add
		return num1 + num2;
		break;
	case 2:  //Subtract
		return num1 - num2;
		break;
	case 3:  //Multiply
		return num1 * num2;
		break;
	case 4:  //Div
		return num1 / num2;
		break;
	case 5:  //sqrt
		return num1 * num1;
		break;
	}
	return 0;
}

