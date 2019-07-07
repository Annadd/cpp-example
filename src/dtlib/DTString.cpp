#include "DTString.h"
#include <cstring>
#include <cstdlib>

#include "Exception.h"

void DTLib::String::init(const char *s)
{
    mStr = strdup(s);

    if( mStr ){
        mLength = static_cast<int>(std::strlen(mStr));
    } else {
        THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create String Object..");
    }
}

bool DTLib::String::equal(const char *l, const char *r, int len) const
{
    bool ret = true;

    for (int i = 0; i < len && ret; i++) {
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

int *DTLib::String::makePMT(const char *p)
{
    size_t len = std::strlen(p);
    int* ret = new int[len];

    if(ret != nullptr){
        int ll = 0;

        ret[0] = 0;

        for (size_t i = 1; i < len; i++) {
            while((ll > 0) && (p[ll] != p[i])){
                ll = ret[ll - 1];
            }

            if(p[ll] == p[i]){
                ll++;
            }

            ret[i] = ll;
        }
    }

    return ret;
}

int DTLib::String::kmp(const char *s, const char *p)
{
    int ret = -1;
    int sl = static_cast<int>(std::strlen(s));
    int pl = static_cast<int>(std::strlen(p));
    int* pmt = makePMT(p);

    if((pmt != nullptr) && (0 < pl) && (pl <= sl)){
        for (int i = 0, j = 0; i < sl; i++) {
            while( (j > 0) && s[i] != p[j]){
                j = pmt[j - 1];
            }

            if(s[i] == p[j]){
                j++;
            }

            if(j == pl){
                ret = i + 1 - pl;
                break;
            }
        }
    }

    delete[] pmt;

    return ret;
}

DTLib::String::String()
{
    init("");
}

DTLib::String::String(char c)
{
    char s[] = {c, '\0'};

    init(s);
}

DTLib::String::String(const char *s)
{
    init(s ? s : "");
}

DTLib::String::String(const DTLib::String &s)
{
    init(s.mStr);
}

int DTLib::String::length() const
{
    return mLength;
}

const char* DTLib::String::str() const
{
    return mStr;
}

bool DTLib::String::startWith(const char *s) const
{
    bool ret = (s != nullptr);

    if(ret) {
        int len = static_cast<int>(std::strlen(s));

        ret = (len < mLength) && equal(mStr, s, len);
    }

    return ret;
}

bool DTLib::String::startWith(const DTLib::String &s) const
{
    return startWith(s.mStr);
}

bool DTLib::String::endOf(const char *s) const
{
    bool ret = (s != nullptr);

    if(ret) {
        int len = static_cast<int>(std::strlen(s));
        char* str = mStr + (mLength - len);

        ret = (len < mLength) && equal(str, s, len);
    }

    return ret;
}

bool DTLib::String::endOf(const DTLib::String &s) const
{
    return endOf(s.mStr);
}

DTLib::String &DTLib::String::insert(int i, const char *s)
{
    if((0 <= i) && (i <= mLength)){
        if((s != nullptr) &&  s[0] != '\0'){
            int len =  static_cast<int>(std::strlen(s));
            char* str = reinterpret_cast<char*>(malloc(mLength + len + 1));

            if(str != nullptr){
                std::strncpy(str, mStr, i);
                std::strncpy(str + i, s, len);
                std::strncpy(str + i + len, mStr + i, mLength - i);

                str[mLength + len] = '\0';

                std::free(mStr);

                mStr = str;
                mLength = mLength + len;

            } else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to insert string value ...");
            }
        }
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "");
    }

    return *this;
}

DTLib::String &DTLib::String::insert(int i, const DTLib::String &s)
{
    return insert(i, s.mStr);
}

DTLib::String &DTLib::String::trim()
{
    int b = 0;
    int e = mLength - 1;

    while (mStr[b] == ' ') b++;
    while (mStr[e] == ' ') e--;

    if(b == 0){
        mStr[e + 1] = '\0';

        mLength = e + 1;
    } else {
        for (int i = 0, j = b;  j <= e; i++, j++) {
            mStr[i] = mStr[j];
        }

        mStr[e - b + 1] = '\0';

        mLength = e - b + 1;
    }

    return *this;
}

int DTLib::String::indexOf(const char *s) const
{
    return kmp(mStr, s);
}

int DTLib::String::indexOf(const DTLib::String &s) const
{
    return kmp(mStr, s.mStr);
}

DTLib::String& DTLib::String::remove(int i, int len)
{
    if((0 <= i) && (i < mLength)){
        int n = i;
        int m = i + len;

        while ((n < m) && (m < mLength)) {
            mStr[n++] = mStr[m++];
        }

        mStr[n] = '\0';
        mLength = n;
    }
}

DTLib::String &DTLib::String::remove(const char *s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

DTLib::String &DTLib::String::remove(const DTLib::String &s)
{
    return remove(indexOf(s), s.length());
}

DTLib::String &DTLib::String::replace(const char *t, const char *s)
{
    int index = indexOf(t);

    if(index >= 0){
        remove(t);
        insert(index, s);
    }

    return *this;
}

DTLib::String &DTLib::String::replace(const char *t, const DTLib::String &s)
{
    return replace(t, s.mStr);
}

DTLib::String &DTLib::String::replace(const DTLib::String &t, const char *s)
{
    return replace(t.mStr, s);
}

DTLib::String &DTLib::String::replace(const DTLib::String &t, const DTLib::String &s)
{
    return replace(t.mStr, s.mStr);
}

DTLib::String DTLib::String::sub(int i, int len) const
{
    String ret;

    if((0 <= i) && (i < mLength)){
        if(len < 0) len = 0;
        if(len + i > mLength) len = mLength - i;
        char* str = reinterpret_cast<char*>(std::malloc(len + 1));

        std::strncpy(str, mStr + i, len);

        str[len] = '\0';

        ret = str;
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invaid ...");
    }

    return ret;
}

char& DTLib::String::operator[](int i)
{
    if((0 <= i) && (i < mLength)){
        return mStr[i];
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }
}

char DTLib::String::operator[](int i) const
{
    return (const_cast<String&>(*this))[i];
}

bool DTLib::String::operator == (const String& s) const
{
    return (std::strcmp(mStr, s.mStr) == 0);
}

bool DTLib::String::operator == (const char* s) const
{
    return (std::strcmp(mStr, s ? s : "") == 0);
}

bool DTLib::String::operator != (const String& s) const
{
    return !(*this == s);
}

bool DTLib::String::operator != (const char* s) const
{
    return !(*this == s);
}

bool DTLib::String::operator > (const String& s) const
{
    return (std::strcmp(mStr, s.mStr) > 0);
}

bool DTLib::String::operator > (const char* s) const
{
    return (std::strcmp(mStr, s ? s : "") > 0);
}

bool DTLib::String::operator >= (const String& s) const
{
    return (std::strcmp(mStr, s.mStr) >= 0);
}

bool DTLib::String::operator >= (const char* s) const
{
    return (std::strcmp(mStr, s ? s : "") >= 0);
}

bool DTLib::String::operator <= (const String& s) const
{
    return (std::strcmp(mStr, s.mStr) <= 0);
}

bool DTLib::String::operator <= (const char* s) const
{
    return (std::strcmp(mStr, s ? s : "") <= 0);
}

DTLib::String DTLib::String::operator + (const String& s) const
{
    return (*this + s.mStr);
}

DTLib::String DTLib::String::operator + (const char* s) const
{
    String ret;

    size_t len = static_cast<size_t>(mLength) + (std::strlen(s ? s : ""));
    char* str = reinterpret_cast<char*>(std::malloc(len + 1));

    if(str){
        std::strcpy(str, mStr);
        std::strcat(str, s);

        std::free(ret.mStr);

        ret.mStr = str;
        ret.mLength = static_cast<int>(len);
    } else {
        THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create String object...");
    }
    return ret;
}

DTLib::String& DTLib::String::operator += (const String& s)
{
    return (*this = *this + s.mStr);
}

DTLib::String& DTLib::String::operator += (const char* s)
{
    return (*this = *this + s);
}

DTLib::String DTLib::String::operator -(const DTLib::String &s) const
{
    return String(*this).remove(s);
}

DTLib::String DTLib::String::operator -(const char *s) const
{
    return String(*this).remove(s);
}

DTLib::String &DTLib::String::operator -=(const DTLib::String &s)
{
    return remove(s);
}

DTLib::String &DTLib::String::operator -=(const char *s)
{
    return remove(s);
}

DTLib::String& DTLib::String::operator = (const String& s)
{
    return (*this = s.mStr);
}

DTLib::String& DTLib::String::operator = (const char* s)
{
    if(mStr != s){
        char* str = strdup(s ? s : "");
        if(str){
            std::free(mStr);

            const_cast<String&>(*this).mStr = str;

            const_cast<String&>(*this).mLength = static_cast<int>(std::strlen(str)) ;
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to assign new String object...");
        }
    }

    return const_cast<String&>(*this);
}

DTLib::String& DTLib::String::operator = (const char c)
{
    char s[] = {c , '\0'};

    return (*this = s);
}

DTLib::String::~String()
{
    std::free(mStr);
}
