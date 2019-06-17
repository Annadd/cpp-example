#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DTLib
{

template<typename T>
class Array : public Object
{
protected:
    T* mArray;
public:
    virtual bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < length()));

        if(ret){
            mArray[i] = e;
        }

        return ret;
    }

    virtual bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i < length()));

        if(ret){
           e = mArray[i];
        }

        return ret;
    }


    T& operator[](int i)
    {
        if((0 <= i) && (i < length())){
            return mArray[i];
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }

    T operator[](int i) const
    {
        return (const_cast<Array<T>&>(*this))[i];
    }

public:
    virtual int length() const = 0;
};

}

#endif // ARRAY_H
