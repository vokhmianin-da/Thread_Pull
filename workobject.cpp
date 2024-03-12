#include "workobject.h"

unsigned int WorkObject::factorial(unsigned int x)
{
    if(x <= 1) return 1;
    return x * factorial(x - 1);
}

WorkObject::WorkObject(): val(1), res(0)
{

}

WorkObject::WorkObject(unsigned int v): val(v), res(0)
{

}

unsigned int WorkObject::getResult()
{
    return res;
}

void WorkObject::run()
{
    res = factorial(val);
}

unsigned int WorkObject::operator()()
{
    res = factorial(val);
    return res;
}
