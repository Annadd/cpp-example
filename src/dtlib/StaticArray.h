#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"

namespace DTLib
{

template<typename T, int N>
class StaticArray : public Array<T>
{
protected:
    T mSpace[N];
public:
    StaticArray()
    {
        this->mArray = mSpace;
    }

    StaticArray(const StaticArray<T, N>& obj)
    {
        this->mArray = mSpace;

        for (int i = 0; i < N; i++) {
            mSpace[i] = obj.mSpace[i];
        }
    }

    StaticArray<T, N>& operator=(const StaticArray<T, N>& obj)
    {
        if(this != &obj){
            for (int i = 0; i < N; i++) {
                mSpace[i] = obj.mSpace[i];
            }
        }

        return *this;
    }

    int length() const
    {
        return N;
    }
};

}

#endif//STATICARRAY_H
