#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DTLib
{

template <typename T>
class Pointer : public Object
{
protected:
    T* mPointer;

public:
    Pointer(T* p = nullptr)
    {
        mPointer = p;
    }

    T* operator->()
    {
        return mPointer;
    }

    T& operator*()
    {
        return *mPointer;
    }

    const T* operator->() const
    {
        return mPointer;
    }

    const T& operator*() const
    {
        return *mPointer;
    }

    bool isNull() const
    {
        return (mPointer == nullptr);
    }

    T* get() const
    {
        return mPointer;
    }
};

}

#endif//POINTER_H
