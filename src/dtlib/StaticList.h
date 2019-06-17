#ifndef __STATICLIST_H__
#define __STATICLIST_H__

#include "SeqList.hpp"

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
        mArray = mSpace;
        mLength = 0;
    }

    int capacity() const
    {
        return N;
    }
};

}

#endif//__STATICLIST_H__