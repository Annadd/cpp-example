#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace DTLib 
{

#define THROW_EXCEPTION(e, msg) (throw e(msg, __FILE__, __LINE__))

class Exception : public Object
{
protected:
	char* mMessage;
	char* mLocation;
	
	void init(const char* message, const char* file, int line);
	
public:
	Exception(const char* message);
	Exception(const char* file, int line);
	Exception(const char* message, const char* file, int line);
	
	Exception(const Exception& e);
	Exception& operator=(const Exception& e);
	
	virtual const char* message() const;
	virtual const char* location() const;
	
	virtual ~Exception() = 0;
};

class ArithmeticException : public Exception
{
public:
    ArithmeticException(const char* message);
    ArithmeticException(const char* file, int line);
    ArithmeticException(const char* message, const char* file, int line);
	
    ArithmeticException(const ArithmeticException& e);
    ArithmeticException& operator=(const ArithmeticException& e);
};

class NullPointerException : public Exception
{
public:	
    NullPointerException(const char* message);
    NullPointerException(const char* file, int line);
    NullPointerException(const char* message, const char* file, int line);
	
    NullPointerException(const NullPointerException& e);
    NullPointerException& operator=(const NullPointerException& e);
};

class IndexOutOfBoundsException : public Exception
{
public:	
    IndexOutOfBoundsException(const char* message);
    IndexOutOfBoundsException(const char* file, int line);
    IndexOutOfBoundsException(const char* message, const char* file, int line);
	
    IndexOutOfBoundsException(const IndexOutOfBoundsException& e);
    IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException& e);
};

class NoEnoughMemeoryException : public Exception
{
public:	
    NoEnoughMemeoryException(const char* message);
    NoEnoughMemeoryException(const char* file, int line);
    NoEnoughMemeoryException(const char* message, const char* file, int line);
	
    NoEnoughMemeoryException(const NoEnoughMemeoryException& e);
    NoEnoughMemeoryException& operator=(const NoEnoughMemeoryException& e);
};

class InvalidParameterException : public Exception
{
public:	
    InvalidParameterException(const char* message);
    InvalidParameterException(const char* file, int line);
    InvalidParameterException(const char* message, const char* file, int line);
	
    InvalidParameterException(const InvalidParameterException& e);
    InvalidParameterException& operator=(const InvalidParameterException& e);
};

class InvalidOperationException : public Exception
{
public:	
    InvalidOperationException(const char* message);
    InvalidOperationException(const char* file, int line);
    InvalidOperationException(const char* message, const char* file, int line);
	
    InvalidOperationException(const InvalidOperationException& e);
    InvalidOperationException& operator=(const InvalidOperationException& e);
};

}
#endif //EXCEPTION_H
