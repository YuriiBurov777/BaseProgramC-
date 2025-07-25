
#include "Create.h"

Counter Create(std::string a, int b)
{
    {
        if (a == "да")
        {
            return Counter(b);
        }
        else
        {
            return Counter();
        }
    }
}
