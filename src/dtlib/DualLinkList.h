#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template<typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
        Node* pre;
    }mHeader;

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

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    DualLinkList()
    {
        mHeader.next = nullptr;
        mHeader.pre = nullptr;
        mLength = 0;
        mStep = 1;
        mCurrent = nullptr;
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

            if(node != nullptr){
                Node* current = position(i);
                Node* next = current->next;

                node->value = e;
                node->next = next;

                current->next = node;

                if(current != reinterpret_cast<Node*>(&mHeader)){
                    node->pre = current;
                } else {
                    node->pre = nullptr;
                }

                if(next != nullptr){
                    next->pre = node;
                }

                mLength++;
            } else{
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to insert new element ...");
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
            Node* next = toDel->next;

            if(mCurrent == toDel){
                mCurrent = next;
            }

            current->next = next;

            if(next != nullptr){
                next->pre = toDel->pre;
            }

            mLength--;

            destroy(toDel);
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
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ...");
        }

        return ret;
    }

    bool get(int i, T &e) const override
    {
        bool ret = ((0 <= i) && (i < mLength));

        if(ret){
            e = position(i)->next->value;
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
        while(mLength > 0){
            remove(0);
        }
    }

    virtual bool move(int i, int step = 1)
    {
        bool ret = (0 <= i) && (i < mLength) && (step > 0);

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
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    virtual bool next()
    {
        int i = 0;

        while ((i < mStep) && !end()) {
            mCurrent = mCurrent->next;
            i++;
        }

        return (i == mStep);
    }

    virtual bool pre()
    {
        int i = 0;

        while ((i < mStep) && !end()) {
            mCurrent = mCurrent->pre;
            i++;
        }

        return (i == mStep);
    }

    ~DualLinkList()
    {
        clear();
    }
};

}

#endif//DUALLINKLIST_H
