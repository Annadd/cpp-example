#ifndef TEST_H
#define TEST_H

#include "Object.h"

class Test : public DTLib::Object
{
public:
    Test(int v = 0);

    bool operator==(const Test& obj);

    ~Test();

    int getValue() const;

    void setValue(int v);

private:
    int value;
};

#endif // TEST_H
