#ifndef EDGE_H
#define EDGE_H

#include "Object.h"

namespace DTLib
{

template<typename E>
struct Edge : public Object
{
    int b;
    int e;
    E data;

    Edge(int i = -1, int j = -1)
    {
        b = i;
        e = j;
    }

    Edge(int i, int j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator==(const Edge<E>& obj)
    {
        return (b == obj.b) && (e == obj.e);
    }

    bool operator!=(const Edge<E>& obj)
    {
        return !(*this == obj);
    }

    bool operator< (const Edge<E>& obj)
    {
        return data < obj.data;
    }

    bool operator> (const Edge<E>& obj)
    {
        return data > obj.data;
    }
};

}

#endif
