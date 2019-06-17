#include <iostream>

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

int main()
{
    //testStaticList();
    //testDynamicList();
    //testStaticArray();
    //testDynamicArray();
    //testLinkList();
    //testStaticLinkList();
    //testSmartPointer();
    //testSharedPointer();
    //testCircleList();
    //testDualLinkList();
    //testDualCircleList();
    //testStaticStack();
    //testLinkStack();
    //testStaticQueue();

    //testLinkQueue();

    testString();
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
