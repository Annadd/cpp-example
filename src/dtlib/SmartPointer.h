#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace DTLib
{

template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = nullptr) : Pointer<T> (p)
    {}
	
    SmartPointer(const SmartPointer<T>& obj) : Pointer<T>(obj)
    {
        this->mPointer = obj.mPointer;
        const_cast<SmartPointer<T>&>(obj).mPointer = nullptr;
    }
	
    SmartPointer<T>& operator=(const SmartPointer<T>& obj)
    {
		if(this != &obj){
            T* p = this->mPointer;

            this->mPointer = obj.mPointer;

			const_cast<SmartPointer<T>&>(obj).mPointer = nullptr;

            delete p;
		}
		
		return *this;
	}
	
    ~SmartPointer()
    {
        delete this->mPointer;
	}
};

}

#endif // SMARTPOINTER_H
