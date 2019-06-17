#include "Exception.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

namespace DTLib 
{

void Exception::init(const char* message, const char* file, int line){
	mMessage = strdup(message);
	
	if(file != nullptr){
		char sl[16] = {0};
		sprintf(sl,"%d",line);
		
		mLocation = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
		if(mLocation == nullptr){
			mLocation = strcpy(mLocation, file);
			mLocation = strcat(mLocation, ":");
			mLocation = strcat(mLocation, sl);			
		}
	}else {
		mLocation = nullptr;
	}
}

Exception::Exception(const char* message){
	init(message, nullptr, 0);
}

Exception::Exception(const char* file, int line){
	init(nullptr, file, line);
}

Exception::Exception(const char* message, const char* file, int line){
	init(message, file, line);
}

Exception::Exception(const Exception& e){
	mMessage = strdup(e.mMessage);
	mLocation = strdup(e.mLocation);
}

Exception& Exception::operator=(const Exception& e){
	if(this != &e){
		free(mMessage);
		free(mLocation);
		mMessage = strdup(e.mMessage);
		mLocation = strdup(e.mLocation);
	}
	
	return *this;
}

const char* Exception::message() const{
	return mMessage;
}

const char* Exception::location() const{
	return mLocation;
}

Exception::~Exception(){
	free(mMessage);
	free(mLocation);
}

}