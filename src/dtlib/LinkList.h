#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template<typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct : public Object{
        char reserved[sizeof(T)];
        Node* next;
    } mHeader;
    int mLength;
    int mStep;
    Node* mCurrent;

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&mHeader);

        for (int p = 0; p < i; p++) {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destory(Node* ptr)
    {
        delete ptr;
    }

public:
    LinkList()
    {
        mCurrent = nullptr;
        mHeader.next = nullptr;
        mLength = 0;
        mStep = 1;
    }

    bool insert(const T &e) override
    {
        return insert(mLength, e);
    }

    bool insert(int i, const T &e) override
    {
        bool ret = ((0 <= i) && (i <= mLength));

        if(ret){
            Node* node = create();

            if(node){
                Node* current = position(i);

                node->value = e;
                node->next = current->next;
                current->next = node;

                mLength++;
            } else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to insert new element...");
            }
        }

        return ret;
    }

    bool remove(int i) override
    {
        bool ret = ((0 <= i) && (i < mLength));

        if(ret){
            Node* current = position(i);

            Node* toDel = current->next;

            if(mCurrent == toDel){
                mCurrent = toDel->next;
            }

            current->next = toDel->next;

            mLength--;

            destory(toDel);
        }

        return ret;
    }

    bool set(int i, const T &e) override
    {
        bool ret = ((0 <= i) && (i < mLength));

        if(ret){
            position(i)->next->value = e;
        }

        return ret;
    }

    virtual T get(int i) const
    {
        T ret;
        if(get(i, ret)){
            return ret;
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element...");
        }
        return ret;
    }

    bool get(int i, T &e) const override
    {
        bool ret = ((0 <= i) && (i < mLength));

        if(ret){
            Node* current = position(i);

            e = current->next->value;
        }

        return ret;
    }

    virtual int find(const T& e) const
    {
        int ret = -1;
        int i = 0;

        Node* node = mHeader.next;

        while (node) {
            if(node->value == e){
                ret = i;
                break;
            } else {
                node = node->next;
                i++;
            }
        }

        return ret;
    }

    int length() const override
    {
        return mLength;
    }

    void clear() override
    {
        while (mHeader.next) {
            Node* toDel = mHeader.next;

            mHeader.next = toDel->next;

            mLength--;

            destory(toDel);
        }
    }

    virtual bool move(int i, int step = 1)
    {
        bool ret = ((0 <= i) && (i < mLength) && (step > 0));

        if(ret){
            mCurrent = position(i)->next;
            mStep = step;
        }

        return ret;
    }

    virtual bool end()
    {
        return (mCurrent == nullptr);
    }

    virtual T current()
    {
        if(!end()){
            return mCurrent->value;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
        }
    }

    virtual bool next()
    {
        int i = 0;
        while((i < mStep) && !end()){
            mCurrent = mCurrent->next;
            i++;
        }

        return (i == mStep);
    }

    ~LinkList()
    {
        clear();
    }
};

}

#endif//LINKLIST_H
