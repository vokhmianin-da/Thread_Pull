#ifndef TASK_H
#define TASK_H

typedef unsigned int TaskOverFun (const unsigned int &x);

class Task
{
    unsigned int val;
    unsigned int res;
    TaskOverFun *Function;
//    unsigned int factorial(unsigned int x);
public:
    Task();
    Task(unsigned int v);

    unsigned int getVal();
    unsigned int getResult();
    bool SetFunction(TaskOverFun* fun);
    void run();

    unsigned int operator()();
};

#endif // TASK_H
