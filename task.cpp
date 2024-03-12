#include "task.h"

unsigned int Task::factorial(unsigned int x)
{
    if(x <= 1) return 1;
    return x * factorial(x - 1);
}

Task::Task(): val(1), res(0)
{

}

Task::Task(unsigned int v): val(v), res(0)
{

}

unsigned int Task::getResult()
{
    return res;
}

void Task::run()
{
    res = factorial(val);
}

unsigned int Task::operator()()
{
    res = factorial(val);
    return res;
}
