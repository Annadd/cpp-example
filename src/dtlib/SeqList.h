#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include "List.h"
#include "Exception.h"

namespace DTLib{

template <typename T>
class SeqList : public List<T>
{
protected:
    T* mArray;
    int mLength;

public:
    bool insert(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i <= mLength));
        ret = (ret && (mLength < capacity()));
        
        if(ret){
            for(int p = mLength - 1; p >= i; p--){
                mArray[p + 1] = mArray[p];
            }

            mArray[i] = e;
            mLength++;
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < mLength));
        
        if(ret){
            for(int p = i; p < mLength - 1; p++){
                mArray[p] = mArray[p + 1];
            }

            mLength--;
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < mLength));
        
        if(ret){
            mArray[i] = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i < mLength));
        
        if(ret){
            e = mArray[i];
        }

        return ret;
    }

    int length() const
    {
        return mLength;
    }

    void clear()
    {
        mLength = 0;
    }

    T& operator[](int i)
    {
        if((0 <= i) && (i < mLength)){
            return mArray[i];
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
        }
    }

    T operator[](int i) const
    {
        return (const_cast<SeqList<T>&>(*this))[i];
    }

    virtual int capacity() const = 0;
};    

}

#endif //__SEQLIST_H__
