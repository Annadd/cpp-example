#include <iostream>
#include <cstring>

#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"
#include "StaticLinkList.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "DualCircleList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "SmartPointer.h"
#include "SharedPointer.h"
#include "StaticQueue.h"
#include "LinkQueue.h"
#include "DTString.h"
#include "Queuesolution.h"
#include "Sort.h"
#include "GTree.h"
#include "BTree.h"
//#include "MatrixGraph.h"
#include "ListGraph.h"

#include "Test.h"

using namespace std;

void testStaticList();

void testDynamicList();

void testStaticArray();

void testDynamicArray();

void testLinkList();

void testStaticLinkList();

void testCircleList();

void testDualLinkList();

void testDualCircleList();

void testSmartPointer();

void testSharedPointer();

void testStaticStack();

void testLinkStack();

void testStaticQueue();

void testLinkQueue();

void testString();

void testGTree();

void testBTree();

void testMatrixGraph();

void testListGraph();

void testPrim();

size_t sum(size_t n);

int main()
{
    try {
        testPrim();
    } catch (DTLib::Exception& e) {
        cout << e.message() << endl;
    }

    return 0;
}

void testStaticList()
{
    DTLib::StaticList<int, 5> l;
    for(int i = 0; i < l.capacity(); i++){
        l.insert(0, i);
    }

    for(int i = 0; i < l.capacity(); i++){
        cout << l[i] << endl;
    }

    l[0] *= l[0];

    for(int i = 0; i < l.capacity(); i++){
        cout << l[i] << endl;
    }

    try {
        l[5] *= l[5];
    } catch (DTLib::Exception& e) {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
}

void testDynamicList()
{
    DTLib::DynamicList<int> l(5);
    for(int i = 0; i < l.capacity(); i++){
        l.insert(0, i);
    }

    for(int i = 0; i < l.capacity(); i++){
        cout << l[i] << endl;
    }

    l[0] *= l[0];

    for(int i = 0; i < l.capacity(); i++){
        cout << l[i] << endl;
    }

    try {
        l[5] *= l[5];
    } catch (DTLib::Exception& e) {
        cout << e.message() << endl;
        cout << e.location() << endl;
        l.resize(10);
        l.insert(50);
    }

    for(int i = 0; i < l.capacity(); i++){
        cout << l[i] << endl;
    }
}

void testStaticArray()
{
    DTLib::StaticArray<int, 5> s1;

    for (int i = 0; i < s1.length(); i++) {
        s1[i] = i * i;
    }

    for (int i = 0; i < s1.length(); i++) {
        cout << s1[i] << endl;
    }

    DTLib::StaticArray<int, 5> s2;
    s2 = s1;

    for (int i = 0; i < s2.length(); i++) {
        cout << s2[i] << endl;
    }

    try {
        s2[6] = 100;
    } catch (DTLib::Exception& e) {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
}

void testDynamicArray()
{
    DTLib::DynamicArray<int> s1(5);
    for (int i = 0; i < s1.length(); i++) {
        s1[i] = i * i;
    }

    for (int i = 0; i < s1.length(); i++) {
        cout << s1[i] << endl;
    }

    DTLib::DynamicArray<int> s2(10);
    s2 = s1;
    s2.resize(8);

    for (int i = 0; i < s2.length(); i++) {
        cout << s2[i] << endl;
    }

    try {
        s2[6] = 100;
    } catch (DTLib::Exception& e) {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
}

void testLinkList()
{
    Test a(1);
    Test a2(2);

    DTLib::LinkList<Test> tlist;

    tlist.insert(a);
    tlist.insert(a2);

    cout << tlist.find(a) << endl;

    DTLib::LinkList<int> list;
    for (int i = 0; i < 5; i++) {
        list.insert(i);
        list.set(0, i * i);
    }

    for(list.move(0); !list.end(); list.next()){
        cout << list.current() << endl;
    }

    list.remove(2);

    for(list.move(0); !list.end(); list.next()){
        cout << list.current() << endl;
    }

    cout << list.find(4) << endl;
}

void testStaticLinkList()
{
    DTLib::StaticLinkList<int, 5> list;
    for (int i = 0; i < list.capacity(); i++) {
        list.insert(i);
    }

    try {
        cout << list.insert(6);
    } catch (DTLib::Exception& e) {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    for(list.move(0); !list.end(); list.next()){
        cout << list.current() << endl;
    }
}

void josephus(int n, int s, int m)
{
    DTLib::CircleList<int> c1;

    for (int i = 1; i <= n; i++) {
        c1.insert(i);
    }

    c1.move(s - 1, m - 1);

    int val = -1;

    while(c1.length() > 0){
        c1.next();
        val = c1.current();
        cout << val << endl;
        c1.remove(c1.find(val));
    }
}

void testCircleList()
{
    josephus(41, 1, 3);
}

void testDualLinkList()
{
    DTLib::DualLinkList<int> dl;

    for (int i = 0; i < 5; i++) {
        dl.insert(0, i);
        dl.insert(0, 5);
    }

    for (dl.move(0); !dl.end(); dl.next()) {
        cout << dl.current() << "-";
    }
    cout << endl;

    for (dl.move(dl.length() -1); !dl.end(); dl.pre()) {
        cout << dl.current() << "-";
    }
    cout << endl;

    dl.move(dl.length() - 1);
    while (!dl.end()) {
        if(dl.current() == 5){
            cout << dl.current() << "-";
            dl.remove(dl.find(dl.current()));
        } else {
            dl.pre();
        }
    }
    cout << endl;

    for (dl.move(dl.length() -1); !dl.end(); dl.pre()) {
        cout << dl.current() << "-";
    }
    cout << endl;
}

void testDualCircleList()
{
    DTLib::DualCircleList<int> dl;

    for (int i = 0; i < 5; i++) {
        dl.insert(0, i);
        dl.insert(0, 5);
    }

    for (int i = 0; i < dl.length(); i++) {
        cout << dl.get(i) << "-";
    }
    cout << endl;


    dl.move(dl.length() - 1);
    while (dl.find(5) != -1) {
        if(dl.current() == 5){
            cout << dl.current() << "-";
            dl.remove(dl.find(dl.current()));
        } else {
            dl.pre();
        }
    }
    cout << endl;

    for (int i = 0; i < dl.length(); i++) {
        cout << dl.get(i) << "-";
    }
    cout << endl;
}

void testSmartPointer()
{
    DTLib::SmartPointer<Test> sp = new Test(2);
    DTLib::SmartPointer<Test> spn;

    spn = sp;
}

void testSharedPointer()
{
    const DTLib::SharedPointer<Test> sp = new Test(2);
    DTLib::SharedPointer<Test> sp1 = sp;
    DTLib::SharedPointer<Test> sp2;

    sp2 = sp1;

    sp2->setValue(100);

    cout << sp->getValue() << endl;
    cout << sp1->getValue() << endl;
    cout << sp2->getValue() << endl;

    sp1.clear();
    cout << (sp == sp1) << endl;
}

void testStaticStack()
{
    DTLib::StaticStack<int, 5> stack;

    for (int i = 0; i < stack.capacity(); i++) {
        stack.push(i);
    }

    while (stack.size() > 0) {
        cout << stack.top() << endl;
        stack.pop();
    }
}

void testLinkStack()
{
    DTLib::LinkStack<Test> stack;

    for (int i = 0; i < 5; i++) {
        stack.push(i);
    }

    while (stack.size() > 0) {
        cout << stack.top().getValue() << endl;
        stack.pop();
    }
}


void testStaticQueue()
{
    DTLib::StaticQueue<int, 5> queue;

    try {
        for (int i = 0; i < 5; i++) {
            queue.add(i);
        }

        while(queue.length() > 0){
            cout << queue.front() << endl;
            queue.remove();
        }
    } catch (DTLib::Exception& e) {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

}

void testLinkQueue()
{
    DTLib::LinkQueue<int> lq;

    for (int i = 0; i < 10; i++) {
        lq.add(i);
    }

    while(lq.length() > 0){
        cout << lq.front() << endl;
        lq.remove();
    }
}

void testString()
{
    DTLib::String s;

    s = 'D';

    cout << s.str() << endl;
    cout << s.length() << endl;
    cout << (s == "D") << endl;
    cout << (s > "CCC") << endl;

    s += " Delphi Tang ";

    cout << s.str() << endl;
    cout << s.length() << endl;
    cout << (s == "D Delphi Tang ") << endl;

    DTLib::String a[] = {"E", "D", "C", "B", "A"};
    DTLib::String min = a[0];

    for (int i = 1; i < 5; i++) {
        if(min > a[i]){
            min = a[i];
        }
    }

    DTLib::String ds = "D.T.Software";
    cout << ds.startWith("D.T") << endl;
    cout << ds.endOf("Software") << endl;

    cout << ds.startWith("1D.T") << endl;
    cout << ds.endOf("2Software") << endl;

    DTLib::String tsa = "";
    tsa.insert(0, "T.A.");
    tsa.insert(4, "group");

    for (int i = 0; i < tsa.length(); i++) {
        cout << tsa[i];
    }
    cout << endl;

    for (int i = 0; i < ds.length(); i++) {
        cout << ds[i] << "-";
    }
    cout << endl;

    DTLib::String ss = " sxxdf ";
    ss.trim();
    for (int i = 0; i < ss.length(); i++) {
        cout << ss[i];
    }
    cout << endl;

    cout << "min = " << min.str() << endl;
}

size_t sum(size_t n)
{
    if(n > 1){
        return n + sum(n - 1);
    }

    return 1;
}

void testGTree()
{
    DTLib::GTree<char> t;
    DTLib::GTreeNode<char>* node = nullptr;
    DTLib::GTreeNode<char> root;

    root.value = 'A';
    root.parent = nullptr;

    t.insert(&root);

    node = t.find('A');
    t.insert('B', node);
    t.insert('C', node);
    t.insert('D', node);

    node = t.find('B');
    t.insert('E', node);
    t.insert('F', node);

    node = t.find('E');
    t.insert('K', node);
    t.insert('L', node);

    node = t.find('C');
    t.insert('G', node);

    //node = t.find('G');
    //t.insert('N', node);

    node = t.find('D');
    t.insert('H', node);
    t.insert('I', node);
    t.insert('J', node);

    node = t.find('H');
    t.insert('M', node);

    std::cout << t.count() << std::endl;
    std::cout << t.height() << std::endl;
    std::cout << t.degree() << std::endl;

    for (t.begin(); !t.end(); t.next()) {
        std::cout << t.current() << std::endl;
    }
}


void testBTree()
{
    DTLib::BTree<int> bt;
    DTLib::BTreeNode<int>* n = nullptr;

    bt.insert(1, nullptr);

    n = bt.find(1);
    bt.insert(2 ,n);
    bt.insert(3, n);

    n = bt.find(2);
    bt.insert(4 ,n);
    bt.insert(5, n);

    n = bt.find(4);
    bt.insert(8 ,n);
    bt.insert(9, n);

    n = bt.find(5);
    bt.insert(10 ,n);

    n = bt.find(3);
    bt.insert(6 ,n);
    bt.insert(7, n);

    n = bt.find(6);
    bt.insert(11 ,n, DTLib::LEFT);

    DTLib::BTreeNode<int>* head = bt.thread(DTLib::LevelOrder);
    DTLib::BTreeNode<int>* hhead = nullptr;

    while(head != nullptr){
        hhead = head;
        head = head->right;
    }

    while(hhead != nullptr){
        cout << hhead->value << " ";
        hhead = hhead->left;
    }

//    std::cout << bt.count() << std::endl;
//    std::cout << bt.height() << std::endl;
//    std::cout << bt.degree() << std::endl;

//    using namespace DTLib;
//    SharedPointer<BTree<int>> btClone = bt.clone();
//    std::cout << btClone->count() << std::endl;
//    std::cout << btClone->height() << std::endl;
//    std::cout << btClone->degree() << std::endl;


//    std::cout << (bt == *btClone) << std::endl;

//    BTree<int> nbt;

//    nbt.insert(0, nullptr);
//    n = nbt.find(0);
//    nbt.insert(6, n);
//    nbt.insert(2, n);

//    n = nbt.find(2);
//    nbt.insert(7, n);
//    nbt.insert(8, n);

//    SharedPointer<BTree<int>> addBt = nbt.add(bt);
//    for (addBt->begin(); !addBt->end(); addBt->next()) {
//        cout << addBt->current() << " ";
//    }
//    cout << endl;

    /*
    auto sp = bt.remove(3);

    int a[] = {8, 9, 10, 11, 7};

    for (auto &vla : a) {
        DTLib::TreeNode<int>* node = sp->find(vla);

        while(node){
            cout << node->value << " ";
            node = node->parent;
        }
        cout << endl;
    }
    */
//    for (bt.begin(); !bt.end(); bt.next()) {
//       cout << bt.current() << " ";
//    }
//    cout << endl;

//    for (btClone->begin(); !btClone->end(); btClone->next()) {
//        cout << btClone->current() << " ";
//    }
//    cout << endl;

//    auto tpr = bt.traversal(DTLib::PreOrder);
//    for (int i = 0; i < tpr->length(); i++) {
//        cout << (*tpr)[i] << " ";
//    }
//    cout << " PreOrder" << endl;

//    auto tin = bt.traversal(DTLib::InOrder);
//    for (int i = 0; i < tin->length(); i++) {
//        cout << (*tin)[i] << " ";
//    }
//    cout << " InOrder" << endl;

//    auto tr = bt.traversal(DTLib::PostOrder);
//    for (int i = 0; i < tr->length(); i++) {
//        cout << (*tr)[i] << " ";
//    }
//    cout << " PostOrder" << endl;
}

void testMatrixGraph()
{
#if 0
    DTLib::MatrixGraph<3, int, int> g;

    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 2);
    g.setEdge(1, 2, 3);

    cout << "vCount: " << g.vCount() << endl;
    cout << "eCount: " << g.eCount() << endl;
    cout << "ID(1): " << g.ID(1) << endl;
    cout << "OD(1): " << g.OD(1) << endl;
    cout << "TD(1): " << g.TD(1) << endl;

    cout << "W(0, 1): " << g.getEdge(0, 1) << endl;
    cout << "W(1, 0): " << g.getEdge(1, 0) << endl;
    cout << "W(1, 2): " << g.getEdge(1, 2) << endl;

    auto aj = g.getAdjacent(1);
    for (int i = 0; i < aj->length(); i++) {
        cout << (*aj)[i] << " ";
    }

    cout << endl;

    g.removeEdge(0, 1);
    cout << "eCount: " << g.eCount() << endl;

    g.setVertex(0, 100);
    cout << "V(0): " << g.getVertex(0) << endl;

    g.setVertex(1, 200);
    cout << "V(1): " << g.getVertex(0) << endl;

    g.setVertex(2, 300);
    cout << "V(2): " << g.getVertex(0) << endl;

    cout << "W(0, 1): " << g.getEdge(0, 1) << endl;
#endif
}


void testListGraph()
{
    DTLib::ListGraph<char, int> g;

//    g.setVertex(0, 'A');
//    g.setVertex(1, 'B');
//    g.setVertex(2, 'C');
//    g.setVertex(3, 'D');

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');

    //g.removeVertex();

    for (int i = 0; i < g.vCount(); i++) {
        cout << i << " : " << g.getVertex(i) << "\n";
    }

    g.setEdge(0, 1, 5);
    g.setEdge(0, 3, 6);
    g.setEdge(1, 2, 8);
    g.setEdge(2, 3, 2);
    g.setEdge(3, 1, 9);

    cout << "W(0, 1) : " << g.getEdge(0, 1) << "\n";
    cout << "W(0, 3) : " << g.getEdge(0, 3) << "\n";
    cout << "W(1, 2) : " << g.getEdge(1, 2) << "\n";
    cout << "W(2, 3) : " << g.getEdge(2, 3) << "\n";
    cout << "W(3, 1) : " << g.getEdge(3, 1) << "\n";

    cout << "ID(1) : " << g.ID(1) << "\n";
    cout << "OD(1) : " << g.OD(1) << "\n";
    cout << "TD(1) : " << g.TD(1) << "\n";

    cout << "eCount() : " << g.eCount() << "\n";
    g.removeEdge(3, 1);
    cout << "eCount() : " << g.eCount() << "\n";

    auto aj = g.getAdjacent(0);
    for (int i = 0; i < aj->length(); i++) {
        cout << (*aj)[i] << " \n";
    }

    g.removeVertex();
    cout << "eCount() : " << g.eCount() << "\n";
    cout << "W(0, 1) : " << g.getEdge(0, 1) << "\n";
    cout << "W(1, 2) : " << g.getEdge(1, 2) << "\n";
    cout << "W(3, 1) : " << g.getEdge(3, 1) << "\n";
}

void testPrim()
{

}
