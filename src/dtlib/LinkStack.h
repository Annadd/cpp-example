#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"

namespace DTLib
{

template<typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> mList;

public:
    void push(const T &e) override
    {
        mList.insert(0, e);
    }

    void pop() override
    {
        if(mList.length() > 0){
            mList.remove(0);
        } else {
            THROW_EXCEPTION(InvalidOperationException, "Invalid operation...");
        }
    }

    T top() const override
    {
        if(mList.length() > 0){
            return mList.get(0);
        } else {
            THROW_EXCEPTION(InvalidOperationException, "Invalid operation...");
        }
    }

    void clear() override
    {
        mList.clear();
    }

    int size() const override
    {
        return mList.length();
    }
};

}

#endif//LINKSTACK_H
