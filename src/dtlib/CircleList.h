#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace DTLib
{

template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    int mod(int i) const
    {
        return (this->mLength == 0) ? 0 : (i % this->mLength);
    }

    Node* last()
    {
        return this->position(this->mLength - 1)->next;
    }

    void lastToFirst()
    {
        last()->next = this->mHeader.next;
    }

public:
    bool insert(const T& e) override
    {
        return insert(this->mLength, e);
    }

    bool insert(int i, const T& e) override
    {
        bool ret = true;

        i = i % (this->mLength + 1);

        ret = LinkList<T>::insert(i, e);

        if(ret && (i == 0)){
            lastToFirst();
        }

        return ret;
    }

    bool remove(int i) override
    {
        bool ret = true;

        i = mod(i);

        if(i == 0){
            Node* toDel = this->mHeader.next;

            if(toDel != nullptr){
                this->mHeader.next = toDel->next;
                this->mLength--;

                if(this->mLength > 0){
                    lastToFirst();

                    if(this->mCurrent == toDel){
                        this->mCurrent = toDel->next;
                    }
                } else {
                    this->mHeader.next = nullptr;
                    this->mCurrent = nullptr;
                }

                this->destory(toDel);
            } else {
                ret = false;
            }
        } else {
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }

    bool set(int i, const T& e) override
    {
        return LinkList<T>::set(mod(i), e);
    }

    T get(int i) const override
    {
        return LinkList<T>::get(mod(i));
    }

    bool get(int i, T& e) const override
    {
        return LinkList<T>::get(mod(i), e);
    }

    int find(const T& e) const override
    {
        int ret = -1;

        Node* slider = this->mHeader.next;

        for (int i = 0; i < this->mLength; i++) {
            if(slider->value == e){
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void clear() override
    {
        while(this->mLength > 1){
            remove(1);
        }

        if(this->mLength == 1){
            Node* toDel = this->mHeader.next;

            this->mHeader.next = nullptr;
            this->mLength = 0;
            this->mCurrent = nullptr;

            this->destory(toDel);
        }
    }

    bool move(int i, int step) override
    {
        return LinkList<T>::move(mod(i), step);
    }

    bool end() override
    {
        return (this->mLength == 0) || (this->mCurrent == nullptr);
    }

    ~CircleList()
    {
        clear();
    }
};

}

#endif//CIRCLELIST_H
