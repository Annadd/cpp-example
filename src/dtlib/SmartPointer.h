#ifndef __SMARTPOINTER_H_
#define __SMARTPOINTER_H_
#include "Object.h"

namespace DTLib
{

template <typename T>
class SmartPointer : public Object{
protected:
	T* mPointer;
public:
	SmartPointer(T* p = nullptr){
		mPointer = p;
	}
	
	SmartPointer(const SmartPointer<T>& obj){
		mPointer = obj.mPointer;
		const_cast<SmartPointer<T>&>(obj).mPointer = nullptr;
	}
	
	SmartPointer<T>& operator=(const SmartPointer<T>& obj){
		if(this != &obj){
			delete mPointer;
			mPointer = obj.mPointer;
			const_cast<SmartPointer<T>&>(obj).mPointer = nullptr;
		}
		
		return *this;
	}
	
	~SmartPointer(){
		delete mPointer;
	}
	
	T* operator->(){
		return mPointer;
	}
	
	T& operator*(){
		return *mPointer;
	}
	
	bool isNull(){
		return (mPointer == nullptr);
	}
	
	T* get(){
		return mPointer;
	}
};

}

#endif // __SMARTPOINTER_H_