#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DTLib
{

template<typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node
    {
        void* operator new(size_t size, void* loc)
        {
            (void)size;
            return loc;
        }
    };

    unsigned char mSpace[sizeof(SNode) * N];
    bool mUsed[N];

protected:
    Node *create()
    {
        SNode* ret = nullptr;

        for (int i = 0; i < N; i++) {
            if(!mUsed[i]){
                ret = reinterpret_cast<SNode*>(mSpace) + i;
                ret = new(ret)SNode();
                mUsed[i] = true;
                break;
            }
        }

        return ret;
    }

    void destory(Node *ptr)
    {
        SNode* space = reinterpret_cast<SNode*>(mSpace);
        SNode* psn = dynamic_cast<SNode*>(ptr);

        for (int i = 0; i < N; i++) {
            if(psn == (space + i)){
                mUsed[i] = false;
                psn->~SNode();
                break;
            }
        }
    }

public:
    StaticLinkList()
    {
        for (int i = 0; i < N; i++) {
            mUsed[i] = false;
        }
    }

    int capacity() const
    {
        return N;
    }

    ~StaticLinkList()
    {
        this->clear();
    }
};

}

#endif//STATICLINKLIST_H
