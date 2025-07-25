#pragma once

class Calculator
{
    public:
    Calculator() 
    {
       num1=0;
       num2=0;
       value=0;
    };
       void setnum1(double num1);
       void setnum2(double num2);
       void setvalue(int value);
       bool chekOperator() const;
       double Math_op() const;
    private:
        double num1{};
        double num2{};
        int value{};
};

