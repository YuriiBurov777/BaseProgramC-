
#pragma once

class Counter
{
public:
    char Operator{};

    Counter()
    {
        this->countValue = 1;
    }
    Counter(int StartValue)
    {
        this->countValue = StartValue;
    }
    void setIncrDecr(char Operator);
   

    int const getValue()
    {
        return countValue;
    }

private:
    int countValue{ 0 };

};

