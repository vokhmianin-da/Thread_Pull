#ifndef TASK_H
#define TASK_H


class Task
{
    unsigned int val;
    unsigned int res;
    unsigned int factorial(unsigned int x);
public:
    Task();
    Task(unsigned int v);

    unsigned int getVal();
    unsigned int getResult();
    void run();

    unsigned int operator()();
};

#endif // TASK_H
