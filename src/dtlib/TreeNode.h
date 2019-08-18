#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib
{

template<typename T>
class TreeNode : public Object
{
protected:
    bool mFlag;

    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator=(const TreeNode<T>&);

    void* operator new(size_t size)
    {
        return Object::operator new(size);
    }

public:
    T value;
    TreeNode<T>* parent;

    TreeNode() : parent(nullptr), mFlag(false){}

    virtual ~TreeNode() = 0;

    bool flag() const
    {
        return mFlag;
    }
};

template<typename T>
TreeNode<T>::~TreeNode(){}

}

#endif
