
#include "Counter2.h"

void Counter::setIncrDecr(char Operator)
{
    {
        if (Operator == '+')
        {
            this->countValue = countValue + 1;
        }
        if (Operator == '-')
        {
            this->countValue = countValue - 1;
        }
    }
}
