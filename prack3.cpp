#include <iostream>

using namespace std;

class A1
{
protected:
    int a1;
public:
    A1(int val=0) {
        a1 = val;
    }

    virtual void print() {
        cout << "A1, contains: a1=" << a1 << endl;
    }

    virtual void show() {
        cout << "a1 = " << a1 << endl;
    }
};
class B1: virtual public A1
{
protected:
    int b1;
public:
    B1(int val=0):A1(val){
        b1=val;
    }
    void print() {
        cout << "B1, contains: b1=" << b1 << endl;
    }

    void show() {
        cout << "a1 = " << A1::a1 << endl;
        cout << "b1 = " << b1 << endl;
    }
};
class B2: virtual public A1
{
protected:
    int b2;
public:
    B2(int val=0):A1(val){
        b2=val;
    }
    void print() {
        cout << "B2, contains: b2=" << b2 << endl;
    }

    void show() {
        cout << "a1 = " << A1::a1 << endl;
        cout << "b2 = " << b2 << endl;
    }
};
class B3: virtual public A1
{
protected:
    int b3;
public:
    B3(int val=0):A1(val){
        b3=val;
    }
    void print() {
        cout << "B3, contains: b3=" << b3 << endl;
    }

    void show() {
        cout << "a1 = " << A1::a1 << endl;
        cout << "b3 = " << b3 << endl;
    }
};
class B4: virtual public A1
{
protected:
    int b4;
public:
    B4(int val=0):A1(val){
        b4=val;
    }
    void print() {
        cout << "B4, contains: b4=" << b4 << endl;
    }

    void show() {
        cout << "a1 = " << A1::a1 << endl;
        cout << "b4 = " << b4 << endl;
    }
};
class C1: virtual public B1, virtual public B2, virtual public B3, virtual public B4
{
protected:
    int c1;
public:
    C1(int val=0):B1(val),B2(val),B3(val),B4(val){
        c1=val;
    }
    void print() {
        cout << "C1, contains: c1=" << c1 << endl;
    }

    void show() {
        cout << "a1 = " << A1::a1 << endl;
        cout << "b1 = " << B1::b1 << endl;
        cout << "b2 = " << B2::b2 << endl;
        cout << "b3 = " << B3::b3 << endl;
        cout << "b4 = " << B4::b4 << endl;
        cout << "c1 = " << c1 << endl;
    }
};

int main(){
    A1 a1(11);
    a1.print();
    a1.show();

    B1 b1(21);
    b1.print();
    b1.show();

    B2 b2(22);
    b2.print();
    b2.show();

    B3 b3(23);
    b3.print();
    b3.show();

    B4 b4(24);
    b4.print();
    b4.show();

    C1 c1(31);
    c1.print();
    c1.show();
}
