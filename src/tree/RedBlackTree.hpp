#ifndef __RED_BLACK__
#define __RED_BLACK__

#include <exception>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

template <typename Comparable>
class RedBlackTree;

template <typename Comparable>
class RedBlackNode;

enum TreeColor {RED,BLACK};

class BaseException;
class DuplicateItemException;

template <typename Object>
class ValueReference;

template <typename Comparable>
class RedBlackTree{
public:
	RedBlackTree(const Comparable& negativeInfinity){
		nullNode = new RedBlackNode<Comparable>();
		header = new RedBlackNode<Comparable>(negativeInfinity);
		
		header->leftChild = header->rightChild = nullNode;
		nullNode->leftChild = nullNode->rightChild = nullNode;
	}
	
	~RedBlackTree(){
		if (!isEmpty()){
			makeEmpty();
		}
		delete nullNode;
		delete header;
	}
	
	void inorder(){
		inorder(header->rightChild);
	}
	
	void levelOrder(){
		levelOrder(header->rightChild);
	}
	
	bool isEmpty() const{
		return (header->rightChild == nullNode);
	}
	
	ValueReference<Comparable> find(const Comparable& key) const{
		if (isEmpty()) 
			return ValueReference<Comparable>();
		
		nullNode->element = key;
		RedBlackNode<Comparable> *iter = header->rightChild;
		
		while (true){
			if (key < iter->element){
				iter = iter->leftChild;
			}else if (key > iter->element){
				iter = iter->rightChild;
			}else if (iter != nullNode){
				return ValueReference<Comparable>(iter->element);
			}else {
				return ValueReference<Comparable>();
			}
		}
		
	}
	
	ValueReference<Comparable> findMax() const{
		if (isEmpty()) 
			return ValueReference<Comparable>();
		
		RedBlackNode<Comparable> *iter = header->rightChild;
		
		while (iter->rightChild != nullptr && iter->rightChild != nullNode){
			iter = iter->rightChild;
		}
		
		return ValueReference<Comparable>(iter->element);
	}
	
	ValueReference<Comparable> findMin() const{
		if (isEmpty()) 
			return ValueReference<Comparable>();
		
		RedBlackNode<Comparable> *iter = header->rightChild;
		
		while (iter->leftChild != nullptr && iter->leftChild != nullNode){
			iter = iter->leftChild;
		}
		
		return ValueReference<Comparable>(iter->element);
	}
	
	void makeEmpty(){
		reclaimMemory(header->rightChild);
		header->rightChild = nullNode;
	}
	
	bool insert(const Comparable& x){
		current = parent = grandad = header;
		nullNode->element = x;
		
		while (current->element != x){
			great = grandad;
			grandad = parent;
			parent = current;
			
			current = x < current->element ? current->leftChild : current->rightChild;
			
			if (current->leftChild->color == TreeColor::RED &&
			    current->rightChild->color == TreeColor::RED){
				handleReorient(x);
			}
		}
		
		if (current != nullNode){
			throw DuplicateItemException("red black tree element is sameness.");
		}
		
		current = new RedBlackNode<Comparable>(x,nullNode,nullNode);
		if (x < parent->element){
			parent->leftChild = current;
		} else {
			parent->rightChild = current;
		}
		
		//auto balance
		handleReorient(x);
		return true;
	}
	
#if 1
	void rotateWithLeftChild() {
		rotateWithLeftChild(header->rightChild);
	}
	
	void rotateWithRightChild() {
		rotateWithRightChild(header->rightChild);
	}
#endif 
	
private:
	void visited(RedBlackNode<Comparable> *curNode){
		static string color[] = {"RED", "BLACK"};
		if (curNode != nullptr && curNode != nullNode){
			cout << "element: " << curNode->element << " color: " << color[curNode->color] << endl;
		}
	}
	
	void inorder(RedBlackNode<Comparable> *curNode){
		if (curNode != nullptr && curNode != nullNode){
			inorder(curNode->leftChild);
			visited(curNode);
			inorder(curNode->rightChild);
		}
	}
	
	void levelOrder(RedBlackNode<Comparable> *tree){
		std::queue<RedBlackNode<Comparable>*> q;
		RedBlackNode<Comparable>* curNode = tree;
		
		while (curNode != nullptr && curNode != nullNode){
			visited(curNode);
			if (curNode->leftChild != nullNode){
				q.push(curNode->leftChild);
			}
			
			if (curNode->rightChild != nullNode){
				q.push(curNode->rightChild);
			}
			
			if (q.empty()) break;
			curNode = q.front();
			q.pop();
		}
	}
	
	void rotateWithLeftChild(RedBlackNode<Comparable>*& k2) const{
		RedBlackNode<Comparable>* k1 = k2->leftChild;//k2 left
		k2->leftChild = k1->rightChild;
		k1->rightChild = k2;
		k2 = k1;
	}
	
	void rotateWithRightChild(RedBlackNode<Comparable>*& k1) const{
		RedBlackNode<Comparable>* k2 = k1->rightChild;
		k1->rightChild = k2->leftChild;
		k2->leftChild = k1;
		k1 = k2;
	}
	
	void twiceRotateWithLeftChild(RedBlackNode<Comparable>*& k3) const{
		rotateWithRightChild(k3->leftChild);
		rotateWithLeftChild(k3);
	}
	
	void twiceRotateWithRightChild(RedBlackNode<Comparable>*& k1) const{
		rotateWithLeftChild(k1->rightChild);
		rotateWithRightChild(k1);
	}
	
	void handleReorient(const Comparable& item){
		//change color
		current->color = TreeColor::RED;
		current->leftChild->color = TreeColor::BLACK;
		current->rightChild->color = TreeColor::BLACK;
		
		if (parent->color == TreeColor::RED){
			grandad->color = TreeColor::RED;
			if (item < grandad->element != item < parent->element){
				parent = rotate(item, grandad);//single rotate
			}
			//twice rotate
			current = rotate(item, great);
			current->color = TreeColor::BLACK;
		}
		
		header->rightChild->color = TreeColor::BLACK;
	}
	
	RedBlackNode<Comparable>* rotate(const Comparable& item,RedBlackNode<Comparable> *parentNode){
		if (item < parentNode->element){
			(item < parentNode->leftChild->element) ? 
			rotateWithLeftChild(parentNode->leftChild) : 
			rotateWithRightChild(parentNode->leftChild);//LL LR
			return parent->leftChild;
		}else {
			(item < parentNode->rightChild->element) ? 
			rotateWithLeftChild(parentNode->rightChild) : 
			rotateWithRightChild(parentNode->rightChild);//RL RR
			return parent->rightChild;
		}
	}
	
	void reclaimMemory(RedBlackNode<Comparable>* tree){
		if (tree != nullptr && tree != nullNode){
			reclaimMemory(tree->leftChild);
			reclaimMemory(tree->rightChild);
			//cout << "delete : " << tree->element << endl; 
			delete tree;
		}
	}
	
private:
	RedBlackNode<Comparable> *header;
	RedBlackNode<Comparable> *nullNode;
	RedBlackNode<Comparable> *current;
	RedBlackNode<Comparable> *parent;
	RedBlackNode<Comparable> *grandad;
	RedBlackNode<Comparable> *great;
};

template <typename Comparable>
class RedBlackNode{
public:
	RedBlackNode(const Comparable& ele = Comparable(), 
		RedBlackNode<Comparable> *left = nullptr,
		RedBlackNode<Comparable> *right = nullptr,
		TreeColor tc = TreeColor::BLACK):element(ele),
		leftChild(left),rightChild(right),color(tc){}
		
private:
	TreeColor color;
	Comparable element;
	RedBlackNode<Comparable> *leftChild;
	RedBlackNode<Comparable> *rightChild;
	friend class RedBlackTree<Comparable>;
};

class BaseException : public exception{
private:
	string message;
public:
	BaseException(string msg = ""):message(msg){}
	virtual ~BaseException(){}
	virtual const char* what(){ return message.c_str(); }
};

class DuplicateItemException : public BaseException{
public:
	DuplicateItemException(string msg = "")
	:BaseException("DuplicateItemException: " + msg){}
};

class NullPointerException : public BaseException{
public:
	NullPointerException(string msg = "")
	:BaseException("NullPointerException: " + msg){}
};

template <typename Object>
class ValueReference{
public:
	ValueReference():object(nullptr){}
	
	explicit ValueReference(const Object& value):object(&value){}
	
	bool isNull()const{ return object == nullptr; }
	
	const Object& get() const{
		if (isNull()){
			throw NullPointerException("value is empty.");
		}
		return *object;
	}
	
private:
	const Object* object;
};

#endif // __RED_BLACK__