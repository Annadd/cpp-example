#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include "SharedPointer.h"

namespace DTLib
{

template<typename T>
class Tree : public Object
{
protected:
    TreeNode<T>* mRoot;
    Tree(const Tree<T>&);
    Tree<T>& operator=(const Tree<T>&);

public:
    Tree():mRoot(nullptr){}
    virtual bool insert(TreeNode<T>* node) = 0;
    virtual bool insert(const T& value, TreeNode<T>* parent) = 0;
    virtual SharedPointer<Tree<T>> remove(const T& value) = 0;
    virtual SharedPointer<Tree<T>> remove(TreeNode<T>* node) = 0;
    virtual TreeNode<T>* find(const T& value) const = 0;
    virtual TreeNode<T>* find(TreeNode<T>* node) const = 0;
    virtual TreeNode<T>* root() const = 0;
    virtual int degree() const = 0;
    virtual int count() const = 0;
    virtual int height() const = 0;
    virtual void clear() = 0;
};

}

#endif//
