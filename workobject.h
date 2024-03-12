#ifndef WORKOBJECT_H
#define WORKOBJECT_H

class WorkObject
{
    unsigned int val;
    unsigned int res;
    unsigned int factorial(unsigned int x);
public:
    WorkObject();
    WorkObject(unsigned int v);

    unsigned int getResult();
    void run();

    unsigned int operator()();
};

#endif // WORKOBJECT_H
