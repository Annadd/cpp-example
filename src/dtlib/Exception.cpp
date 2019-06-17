#include "Exception.h"

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

namespace DTLib 
{

void Exception::init(const char* message, const char* file, int line)
{
    mMessage = (message ? strdup(message) : nullptr);

	if(file != nullptr){
		char sl[16] = {0};
		sprintf(sl,"%d",line);
		
		mLocation = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
        if(mLocation != nullptr){
			mLocation = strcpy(mLocation, file);
			mLocation = strcat(mLocation, ":");
			mLocation = strcat(mLocation, sl);			
		}
    } else {
		mLocation = nullptr;
	}
}

Exception::Exception(const char* message)
{
	init(message, nullptr, 0);
}

Exception::Exception(const char* file, int line)
{
	init(nullptr, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
	init(message, file, line);
}

Exception::Exception(const Exception& e)
{
	mMessage = strdup(e.mMessage);
	mLocation = strdup(e.mLocation);
}

Exception& Exception::operator=(const Exception& e)
{
	if(this != &e){
		free(mMessage);
		free(mLocation);
		mMessage = strdup(e.mMessage);
		mLocation = strdup(e.mLocation);
	}
	
	return *this;
}

const char* Exception::message() const
{
	return mMessage;
}

const char* Exception::location() const
{
	return mLocation;
}

Exception::~Exception()
{
	free(mMessage);
	free(mLocation);
}

ArithmeticException::ArithmeticException(const char *message):Exception(message){}

ArithmeticException::ArithmeticException(const char *file, int line):Exception(file, line){}

ArithmeticException::ArithmeticException(const char *message, const char *file, int line):Exception(message,file,line){}

ArithmeticException::ArithmeticException(const ArithmeticException &e):Exception(e){}

ArithmeticException &ArithmeticException::operator=(const ArithmeticException &e)
{
    Exception::operator=(e);
    return *this;
}

NullPointerException::NullPointerException(const char *message):Exception(message){}

NullPointerException::NullPointerException(const char *file, int line):Exception(file, line){}

NullPointerException::NullPointerException(const char *message, const char *file, int line):Exception(message,file,line){}

NullPointerException::NullPointerException(const NullPointerException &e):Exception(e){}

NullPointerException &NullPointerException::operator=(const NullPointerException &e)
{
    Exception::operator=(e);
    return *this;
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char *message):Exception(message){}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char *file, int line):Exception(file, line){}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char *message, const char *file, int line):Exception(message,file,line){}

IndexOutOfBoundsException::IndexOutOfBoundsException(const IndexOutOfBoundsException &e):Exception(e){}

IndexOutOfBoundsException &IndexOutOfBoundsException::operator=(const IndexOutOfBoundsException &e)
{
    Exception::operator=(e);
    return *this;
}

NoEnoughMemeoryException::NoEnoughMemeoryException(const char *message):Exception(message){}

NoEnoughMemeoryException::NoEnoughMemeoryException(const char *file, int line):Exception(file, line){}

NoEnoughMemeoryException::NoEnoughMemeoryException(const char *message, const char *file, int line):Exception(message,file,line){}

NoEnoughMemeoryException::NoEnoughMemeoryException(const NoEnoughMemeoryException &e):Exception(e){}

NoEnoughMemeoryException &NoEnoughMemeoryException::operator=(const NoEnoughMemeoryException &e)
{
    Exception::operator=(e);
    return *this;
}

InvalidParameterException::InvalidParameterException(const char *message):Exception(message){}

InvalidParameterException::InvalidParameterException(const char *file, int line):Exception(file, line){}

InvalidParameterException::InvalidParameterException(const char *message, const char *file, int line):Exception(message,file,line){}

InvalidParameterException::InvalidParameterException(const InvalidParameterException &e):Exception(e){}

InvalidParameterException &InvalidParameterException::operator=(const InvalidParameterException &e)
{
    Exception::operator=(e);
    return *this;
}

InvalidOperationException::InvalidOperationException(const char *message):Exception(message){}

InvalidOperationException::InvalidOperationException(const char *file, int line):Exception(file, line){}

InvalidOperationException::InvalidOperationException(const char *message, const char *file, int line):Exception(message,file,line){}

InvalidOperationException::InvalidOperationException(const InvalidOperationException &e):Exception(e){}

InvalidOperationException &InvalidOperationException::operator=(const InvalidOperationException &e)
{
    Exception::operator=(e);
    return *this;
}

}
