#include <climits>

#include "RedBlackTree.hpp"

void TestSingle()
{
	int source[] = {30,15,70,20};
	
	RedBlackTree<int> t(INT_MIN);
	
	for (int i = 0; i < sizeof(source) / sizeof(source[0]); i++){
		t.insert(source[i]);
	}
	
	cout << "inorder --" << endl;
	t.inorder();
	
	cout << "level Order --" << endl;
	t.levelOrder();
	
	cout << "rotate right --" << endl;
	t.rotateWithLeftChild();
	
	cout << "level Order --" << endl;
	t.levelOrder();
	
	cout << "rotate left --" << endl;
	t.rotateWithRightChild();
	
	cout << "level Order --" << endl;
	t.levelOrder();
}

void TestTwice()
{
	int source[] = {12,16,8,10,4,14,2,6,5};
	
	RedBlackTree<int> t(INT_MIN);
	
	for (int i = 0; i < sizeof(source) / sizeof(source[0]); i++){
		t.insert(source[i]);
	}
	
	cout << "level Order --" << endl;
	t.levelOrder();
	
	cout << "inorder --" << endl;
	t.inorder();
}

void TestThird()
{
	int source[] = {50,40,30,101,8,88,77};
	
	RedBlackTree<int> t(INT_MIN);
	
	for (int i = 0; i < sizeof(source) / sizeof(source[0]); i++){
		t.insert(source[i]);
	}
	
	cout << "level Order --" << endl;
	t.levelOrder();
	
	cout << "inorder --" << endl;
	t.inorder();
	
	cout << t.isEmpty() << endl;

		
	try{
		cout << "min: " << t.findMin().get() << endl;
		cout << "max: " << t.findMax().get() << endl;
		cout << "find: " << t.find(30).get() << endl;
		cout << "find: " << t.find(45).get() << endl;
	}catch(BaseException& e){
		cout << e.what() << endl;
	}
	
	t.makeEmpty();
	cout << t.isEmpty() << endl;
}

int main()
{
	cout << "begin red black tree testing..." << endl;
	
	TestSingle();
	
	cout << "------" << endl;
	TestTwice();
	
	cout << "------" << endl;
	TestThird();
	cout << "end red black tree tested..." << endl;
	return 0;
}