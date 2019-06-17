#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace DTLib
{

template<typename T>
class DynamicList : public SeqList<T>
{
protected:
    int mCapacity;

public:
    DynamicList(int capacity)
    {
        this->mArray = new T[capacity];

        if(this->mArray){
            this->mLength = 0;
            this->mCapacity = capacity;
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create to DynamicList object...");
        }
    }

    int capacity() const
    {
        return mCapacity;
    }

    void resize(int capacity)
    {
        if(capacity != mCapacity){
            T* array = new T[capacity];

            if(array){
                int length = (this->mLength < capacity ? this->mLength : capacity);

                for (int i = 0; i < length; i++) {
                    array[i] = this->mArray[i];
                }

                T* temp = this->mArray;

                this->mArray = array;
                this->mLength = length;
                this->mCapacity = capacity;

                delete[] temp;
            } else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to resize DynamicList object...");
            }
        }
    }

    ~DynamicList()
    {
        delete[] this->mArray;
    }
};

}

#endif // DYNAMICLIST_H
