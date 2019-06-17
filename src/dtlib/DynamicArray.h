#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"

namespace DTLib
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int mLength;

    T* copy(T* array, int len, int newLen)
    {
        T* ret = new T[newLen];

        if(ret){
            int size = (len < newLen) ? len : newLen;

            for(int i = 0; i < size; i++){
                ret[i] = array[i];
            }
        }

        return ret;
    }

    void update(T* array, int length)
    {
        if(array){
            T* temp = this->mArray;

            this->mArray = array;
            this->mLength = length;

            delete [] temp;
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to update DynamicArray object...");
        }
    }

    void init(T* array, int length)
    {
        if(array){
            this->mArray = array;
            this->mLength = length;
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to init DynamicArray object...");
        }
    }

public:
    DynamicArray(int length = 0)
    {
        init(new T[length], length);
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        init(copy(obj.mArray, obj.mLength, obj.mLength), obj.mLength);
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& obj)
    {
        if(this != &obj){
            update(copy(obj.mArray, obj.mLength, obj.mLength), obj.mLength);
        }

        return *this;
    }

    int length() const
    {
        return mLength;
    }

    void resize(int length)
    {
        if(length != mLength){
            update(copy(this->mArray, mLength, length), length);
        }
    }

    ~DynamicArray()
    {
        delete [] this->mArray;
    }
};

}

#endif//DYNAMICARRAY_H
