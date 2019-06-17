#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "LinkList.h"
#include "LinuxList.h"

namespace DTLib
{

template<typename T>
class LinkQueue : public Queue<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head mHeader;
    int mLength;

public:
    LinkQueue()
    {
        mLength = 0;

        INIT_LIST_HEAD(&mHeader);
    }

    ~LinkQueue()
    {
        clear();
    }

    // Queue interface
public:
    void add(const T &e) override
    {
        Node* node = new Node();

        if(node != nullptr){
            node->value = e;

            list_add_tail(&node->head, &mHeader);

            mLength++;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
        }
    }

    void remove() override
    {
        if(mLength > 0){
            list_head* toDel = mHeader.next;

            list_del(toDel);

            mLength--;

            delete list_entry(toDel, Node, head);
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
        }
    }

    T front() const override
    {
        if(mLength > 0){
            return list_entry(mHeader.next, Node, head)->value;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
        }
    }

    void clear() override
    {
        while (mLength > 0) {
            remove();
        }
    }

    int length() const override
    {
        return mLength;
    }
};

}

#endif//
