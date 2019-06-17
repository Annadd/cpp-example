#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "DualLinkList.h"
#include "LinuxList.h"

namespace DTLib
{

template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object{
        list_head head;
        T value;
    };

    list_head mHeader;
    list_head* mCurrent;

    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&mHeader);

        for (int p = 0; p < i; p++) {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int i) const
    {
        return (this->mLength == 0) ? 0 : (i % this->mLength);
    }

    // List interface
public:
    bool insert(const T &e) override
    {
        return insert(this->mLength, e);
    }

    bool insert(int i, const T &e) override
    {
        bool ret = true;

        Node* node = new Node();

        i = i % (this->mLength + 1);

        if(node != nullptr){
            node->value = e;

            list_add_tail(&node->head, position(i)->next);

            this->mLength++;
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to insert new element");
        }

        return ret;
    }

    bool remove(int i) override
    {
        bool ret = true;

        i = mod(i);

        ret = (0 <= i) && (i < this->mLength);

        if(ret){
            list_head* toDel = position(i)->next;

            if(mCurrent == toDel){
                mCurrent = toDel->next;
            }

            list_del(toDel);

            this->mLength--;

            delete(list_entry(toDel, Node, head));
        }

        return ret;
    }

    bool set(int i, const T &e) override
    {
        bool ret = true;

        i = mod(i);

        ret = (0 <= i) && (i < this->mLength);

        if(ret){
            list_entry(position(i)->next, Node, head)->value = e;
        }

        return ret;
    }

    bool get(int i, T &e) const override
    {
        bool ret = true;

        i = mod(i);

        ret = (0 <= i) && (i < this->mLength);

        if(ret){
            e = list_entry(position(i)->next, Node, head)->value;
        }

        return ret;
    }

    int length() const override
    {
        return this->mLength;
    }

    void clear() override
    {
        while (this->mLength > 0) {
            remove(0);
        }
    }

    int find(const T& e) const override
    {
        int ret = -1;
        int i = 0;
        list_head* slider = nullptr;

        list_for_each(slider, &mHeader){
            if(list_entry(slider, Node, head)->value == e){
                ret = i;
                break;
            }

            i++;
        }

        return ret;
    }

public:
    DualCircleList()
    {
        this->mLength = 0;
        this->mStep = 1;

        this->mCurrent = nullptr;

        INIT_LIST_HEAD(&mHeader);
    }

    T get(int i) const override
    {
        T ret;

        if(get(i, ret)){
            return ret;
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element...");
        }

        return ret;
    }

    bool move(int i, int step = 1) override
    {
        bool ret = (step > 0);

        i = mod(i);

        ret = ret && ((0 <=i ) && (i < this->mLength));

        if(ret){
            mCurrent = position(i)->next;
            this->mStep = step;
        }

        return ret;
    }

    bool end() override
    {
        return (mCurrent == nullptr) || (this->mLength == 0);
    }

    T current() override
    {
        if(!end()){
            return list_entry(mCurrent, Node, head)->value;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
        }
    }

    bool next() override
    {
        int i = 0;

        while ((i < this->mStep) && (!end())) {
            if(mCurrent != &mHeader){
                mCurrent = mCurrent->next;
                i++;
            } else {
                mCurrent = mCurrent->next;
            }
        }

        if(mCurrent == &mHeader){
            mCurrent = mCurrent->next;
        }

        return (i == this->mStep);
    }

    bool pre() override
    {
        int i = 0;

        while ((i < this->mStep) && (!end())) {
            if(mCurrent != &mHeader){
                mCurrent = mCurrent->prev;
                i++;
            } else {
                mCurrent = mCurrent->prev;
            }
        }

        if(mCurrent == &mHeader){
            mCurrent = mCurrent->prev;
        }

        return (i == this->mStep);
    }

    ~DualCircleList()
    {
        clear();
    }
};

}

#endif//
