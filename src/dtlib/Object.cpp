#include "Object.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace DTLib 
{

void *Object::operator new(unsigned long int size) throw(){
    cout << "Object::operator new:" << size << endl;
    return malloc(size);
}

void Object::operator delete(void* p){
    cout << "Object::operator delete: " << p << endl;
    free(p);
}

void * Object::operator new[](unsigned long int size) throw(){
    return malloc(size);
}

void Object::operator delete[](void * p){
    free(p);
}

Object::~Object(){

}

}