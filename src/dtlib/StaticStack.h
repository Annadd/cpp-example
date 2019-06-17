#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib
{

template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T mSpace[N];
    int mTop;
    int mSize;

public:
    StaticStack()
    {
        mTop = -1;
        mSize = 0;
    }

    int capacity() const
    {
        return N;
    }



    // Stack interface
public:
    void push(const T &e)
    {
        if(mSize < N){
            mSpace[mTop + 1] = e;
            mTop++;
            mSize++;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack...");
        }
    }

    void pop() override
    {
        if(mSize > 0){
            mTop--;
            mSize--;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
        }
    }

    T top() const override
    {
        if(mSize > 0){
            return mSpace[mTop];
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
        }
    }

    void clear() override
    {
        mTop = -1;
        mSize = 0;
    }

    int size() const override
    {
        return mSize;
    }
};

}

#endif//
