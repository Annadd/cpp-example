#ifndef STATICLIST_H
#define STATICLIST_H

#include "SeqList.h"

namespace DTLib
{

template<typename T, int N>
class StaticList : public SeqList<T>
{
protected:
    T mSpace[N];

public:
    StaticList()
    {
        this->mArray = mSpace;
        this->mLength = 0;
    }

    int capacity() const
    {
        return N;
    }
};

}

#endif//STATICLIST_H
