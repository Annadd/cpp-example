#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace DTLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder
};

template<typename T>
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> mQueue;

    virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = nullptr;


        if(node != nullptr){
            if(node->value == value){
                ret = node;
            }
            else {
                if(ret == nullptr){
                    ret = find(node->left, value);
                }

                if(ret == nullptr){
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = nullptr;

        if(node == obj){
            ret = node;
        }
        else {
            if(node != nullptr){
                if(ret == nullptr){
                    ret = find(node->left, obj);
                }

                if(ret == nullptr){
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

    virtual bool insert(BTreeNode<T> *n, BTreeNode<T> *np, BTNodePos pos)
    {
        bool ret = true;

        if(pos == ANY){
            if(np->left == nullptr){
                np->left = n;
            } else if(np->right == nullptr){
                np->right = n;
            } else {
                ret = false;
            }
        } else if(pos == LEFT){
            if(np->left == nullptr){
                np->left = n;
            } else {
                ret = false;
            }
        } else if(pos == RIGHT){
            if(np->right == nullptr){
                np->right = n;
            } else {
                ret = false;
            }
        } else {
            ret = false;
        }

        return ret;
    }

    virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if(ret == nullptr){
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create tree ...");
        } else {
            if(root() == node){
                this->mRoot = nullptr;
            } else {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if(parent->left == node){
                    parent->left = nullptr;
                }
                else if (parent->right == node) {
                    parent->right = nullptr;
                }

                node->parent = nullptr;
            }

            ret->mRoot = node;
        }
    }

    virtual void free(BTreeNode<T>* node)
    {
        if(node != nullptr){
            free(node->left);

            free(node->right);

            if(node->flag()){
                delete node;
            }
        }
    }

    int count(BTreeNode<T>* node) const
    {
        return (node != nullptr) ? (count(node->left) + count(node->right) + 1) : 0;
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != nullptr){
            int lh = height(node->left);
            int rh = height(node->right);

            ret = ((lh > rh) ? lh : rh) + 1;
        }

        return ret;
    }


    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != nullptr) {
            BTreeNode<T>* child[] = {node->left, node->right};

            ret = (!!node->left + !!node->right);

            for (int i = 0; (ret < 2) && (i < 2); i++) {
                int d = degree(child[i]);

                if(ret < d){
                    ret = d;
                }
            }
        }

        return ret;
    }

    void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr){
            queue.add(node);
            preOrderTraversal(node->left, queue);
            preOrderTraversal(node->right, queue);
        }
    }

    void inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr){
            inOrderTraversal(node->left, queue);
            queue.add(node);
            inOrderTraversal(node->right, queue);
        }
    }

    void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr){
            postOrderTraversal(node->left, queue);
            postOrderTraversal(node->right, queue);
            queue.add(node);
        }
    }

    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = nullptr;

        if(node != nullptr){
            ret = BTreeNode<T>::NewNode();

            if(ret != nullptr){
                ret->value = node->value;

                ret->left = clone(node->left);
                ret->right = clone(node->right);

                if(ret->left != nullptr){
                    ret->left->parent = ret;
                }

                if(ret->right != nullptr){
                    ret->right->parent = ret;
                }

            } else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create new node ...");
            }
        }

        return ret;
    }

    bool equal(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        if(lh == rh){
            return true;
        } else if (lh != nullptr && rh != nullptr) {
            return (lh->value == rh->value) && equal(lh->left, rh->left) && equal(lh->right, rh->right);
        } else {
            return false;
        }
    }

    BTreeNode<T>* add(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        BTreeNode<T>* ret = nullptr;

        if(lh == nullptr && rh != nullptr){
            ret = clone(rh);
        }
        else if (lh != nullptr && rh == nullptr) {
            ret = clone(lh);
        }
        else if ((lh != nullptr) && (rh != nullptr)) {
            ret = BTreeNode<T>::NewNode();

            if(ret != nullptr){
                ret->value = lh->value + rh->value;

                ret->left = add(lh->left, rh->left);
                ret->right = add(lh->right, rh->right);

                if(ret->left != nullptr){
                    ret->left->parent = ret;
                }

                if(ret->right != nullptr){
                    ret->right->parent = ret;
                }
            } else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create new node...");
            }
        }

        return ret;
    }

    // Tree interface
public:
    bool insert(TreeNode<T>* node) override
    {
        return insert(node, ANY);
    }

    virtual bool insert(TreeNode<T> *node, BTNodePos pos)
    {
        bool ret = true;

        if(node != nullptr){
            if(this->mRoot == nullptr){
                node->parent = nullptr;
                this->mRoot = node;
            }
            else {
                BTreeNode<T>* np = find(node->parent);

                if(np != nullptr){
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                } else {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node can note be null ...");
        }

        return ret;
    }

    bool insert(const T &value, TreeNode<T> *parent) override
    {
        return insert(value, parent, ANY);
    }

    virtual bool insert(const T &value, TreeNode<T> *parent, BTNodePos pos)
    {
        bool ret = true;

        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if(node == nullptr){
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create new node ...");
        } else {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if(!ret){
                delete node;
            }
        }

        return ret;
    }

    SharedPointer<Tree<T>> remove(const T &value) override
    {
        BTree<T>* ret = nullptr;

        BTreeNode<T>* node = find(value);

        if(node == nullptr){
            THROW_EXCEPTION(InvalidParameterException, "Can not find the tree node via value...");
        } else {
            remove(node, ret);

            mQueue.clear();
        }

        return ret;
    }

    SharedPointer<Tree<T>> remove(TreeNode<T> *node) override
    {
        BTree<T>* ret = nullptr;

        node = find(node);

        if(node == nullptr){
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalied");
        } else {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);

            mQueue.clear();
        }

        return ret;
    }

    BTreeNode<T>* find(const T& value) const override
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T> *node) const override
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const override
    {
        return dynamic_cast<BTreeNode<T>*>(this->mRoot);
    }

    int degree() const override
    {
        return degree(root());
    }

    int count() const override
    {
        return count(root());
    }

    int height() const override
    {
        return height(root());
    }

    void clear() override
    {
        free(root());

        mQueue.clear();

        this->mRoot = nullptr;
    }

    bool begin() override
    {
        bool ret = (root() != nullptr);

        if(ret){
            mQueue.clear();
            mQueue.add(root());
        }

        return ret;
    }

    bool end() override
    {
        return (mQueue.length() == 0);
    }

    bool next() override
    {
        bool ret = (mQueue.length() > 0);

        if(ret){
            BTreeNode<T>* node = mQueue.front();

            mQueue.remove();

            if(node->left != nullptr){
                mQueue.add(node->left);
            }

            if(node->right != nullptr){
                mQueue.add(node->right);
            }
        }

        return ret;
    }

    T current() override
    {
        if(!end()){
            return mQueue.front()->value;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    SharedPointer<Array<T>> traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = nullptr;
        LinkQueue<BTreeNode<T>*> queue;

        switch (order) {
        case PreOrder:
            preOrderTraversal(root(), queue);
            break;
        case InOrder:
            inOrderTraversal(root(), queue);
            break;
        case PostOrder:
            postOrderTraversal(root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid....");
            break;
        }

        ret = new DynamicArray<T>(queue.length());

        if(ret != nullptr){
            for (int i = 0; i < ret->length(); i++, queue.remove()) {
                ret->set(i, queue.front()->value);
            }
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create return array ...");
        }

        return ret;
    }

    SharedPointer<BTree<T>> clone() const
    {
        BTree<T>* ret = new BTree<T>();

        if(ret != nullptr){
            ret->mRoot = clone(root());
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create new tree...");
        }

        return ret;
    }

    bool operator== (const BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }

    bool operator!= (const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    SharedPointer<BTree<T>> add(const BTree<T>& btree) const
    {
        BTree<T>* ret = new BTree<T>();

        if(ret != nullptr){
            ret->mRoot = add(root(), btree.root());
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create new tree...");
        }

        return ret;
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif//BTREE_H
