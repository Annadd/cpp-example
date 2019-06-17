#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* mRef;

    void assign(const SharedPointer<T>& obj)
    {
        this->mRef = obj.mRef;
        this->mPointer = obj.mPointer;

        if(mRef){
            (*mRef)++;
        }
    }

public:
    SharedPointer(T* p = nullptr) : mRef(nullptr)
    {
        if(p){
            mRef = new int(0);

            if(mRef){
                *mRef = 1;
                this->mPointer = p;
            } else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create SharedPointer object ...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T> (obj)
    {
        assign(obj);
    }

    SharedPointer<T>& operator=(const SharedPointer<T>& obj)
    {
        if(this != &obj){
            clear();
            assign(obj);
        }
        return *this;
    }

    void clear()
    {
        T* toDel = this->mPointer;
        int* ref = mRef;

        this->mRef = nullptr;
        this->mPointer = nullptr;

        if(ref){
            (*ref)--;

            if(!(*ref)){
                delete ref;
                delete toDel;
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }
};

template<typename T>
bool operator==(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template<typename T>
bool operator!=(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(l == r);
}

}

#endif//SHAREDPOINTER_H
