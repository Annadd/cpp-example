#include "Test.h"

#include <iostream>

using namespace std;

Test::Test(int v):value(v)
{
    cout << "Test()" << endl;
}

bool Test::operator==(const Test &obj)
{
    return value == obj.value;
}

Test::~Test()
{
    cout << "~Test()" << endl;
}

int Test::getValue() const
{
    return value;
}

void Test::setValue(int v)
{
    value = v;
}
