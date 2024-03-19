#include "task.h"

//unsigned int Task::factorial(unsigned int x)
//{
//    if(x <= 1) return 1;
//    return x * factorial(x - 1);
//}

Task::Task(): val(1), res(0), Function(nullptr)
{

}

Task::Task(unsigned int v): val(v), res(0), Function(nullptr)
{

}

unsigned int Task::getVal()
{
    return val;
}

unsigned int Task::getResult()
{
    return res;
}

bool Task::SetFunction(TaskOverFun *fun)
{
    if(fun != nullptr)
    {
        Function = fun;
        return true;
    }
    return false;
}

void Task::run()
{
    if(Function != nullptr) res = Function(val);
}

unsigned int Task::operator()()
{
    if(Function != nullptr)
    {
        res = Function(val);
    }
    else
    {
        res = 0;
    }
    return res;
}
