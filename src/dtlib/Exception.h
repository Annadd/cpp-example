#ifndef __EXCEPTION_H_
#define __EXCEPTION_H_

#include "Object.h"

namespace DTLib 
{

#define THROW_EXCEPTION(e, msg) (throw e(msg, __FILE__, __LINE__))

class Exception : public Object{
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

class ArithmeticException : public Exception{
public:
	ArithmeticException(const char* message):Exception(message){}
	ArithmeticException(const char* file, int line):Exception(file, line){}
	ArithmeticException(const char* message, const char* file, int line):Exception(message,file,line){}
	
	ArithmeticException(const ArithmeticException& e):Exception(e){}
	ArithmeticException& operator=(const ArithmeticException& e){
		Exception::operator=(e);
		return *this;
	}
};

class NullPointerException : public Exception{
public:	
	NullPointerException(const char* message):Exception(message){}
	NullPointerException(const char* file, int line):Exception(file, line){}
	NullPointerException(const char* message, const char* file, int line):Exception(message,file,line){}
	
	NullPointerException(const NullPointerException& e):Exception(e){}
	NullPointerException& operator=(const NullPointerException& e){
		Exception::operator=(e);
		return *this;
	}
};

class IndexOutOfBoundsException : public Exception{
public:	
	IndexOutOfBoundsException(const char* message):Exception(message){}
	IndexOutOfBoundsException(const char* file, int line):Exception(file, line){}
	IndexOutOfBoundsException(const char* message, const char* file, int line):Exception(message,file,line){}
	
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e):Exception(e){}
	IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException& e){
		Exception::operator=(e);
		return *this;
	}
};

class NoEnoughMemeoryException : public Exception{
public:	
	NoEnoughMemeoryException(const char* message):Exception(message){}
	NoEnoughMemeoryException(const char* file, int line):Exception(file, line){}
	NoEnoughMemeoryException(const char* message, const char* file, int line):Exception(message,file,line){}
	
	NoEnoughMemeoryException(const NoEnoughMemeoryException& e):Exception(e){}
	NoEnoughMemeoryException& operator=(const NoEnoughMemeoryException& e){
		Exception::operator=(e);
		return *this;
	}
};

class InvalidParameterException : public Exception{
public:	
	InvalidParameterException(const char* message):Exception(message){}
	InvalidParameterException(const char* file, int line):Exception(file, line){}
	InvalidParameterException(const char* message, const char* file, int line):Exception(message,file,line){}
	
	InvalidParameterException(const InvalidParameterException& e):Exception(e){}
	InvalidParameterException& operator=(const InvalidParameterException& e){
		Exception::operator=(e);
		return *this;
	}
};

class InvalidOperationException : public Exception{
public:	
	InvalidOperationException(const char* message):Exception(message){}
	InvalidOperationException(const char* file, int line):Exception(file, line){}
	InvalidOperationException(const char* message, const char* file, int line):Exception(message,file,line){}
	
	InvalidOperationException(const InvalidOperationException& e):Exception(e){}
	InvalidOperationException& operator=(const InvalidOperationException& e){
		Exception::operator=(e);
		return *this;
	}
};

}
#endif //__EXCEPTION_H_