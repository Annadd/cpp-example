#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace DTLib
{

template<typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T mSpace[N];
    int mFornt;
    int mRear;
    int mLength;

public:
    StaticQueue()
    {
        mFornt = 0;
        mRear = 0;
        mLength = 0;
    }

    int capacity() const
    {
        return N;
    }

    // Queue interface
    void add(const T &e) override
    {
        if(mLength < N){
            mSpace[mRear] = e;
            mRear = (mRear + 1) % N;
            mLength++;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No space in current queue...");
        }
    }


    void remove() override
    {
        if(mLength > 0){
            mFornt = (mFornt + 1) % N;
            mLength--;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
        }
    }

    T front() const override
    {
        if(mLength > 0){
            return mSpace[mFornt];
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
        }
    }

    void clear() override
    {
        mFornt = 0;
        mRear = 0;
        mLength = 0;
    }

    int length() const override
    {
        return mLength;
    }

    ~StaticQueue()
    {
        clear();
    }
};

}

#endif//STATICQUEUE_H
