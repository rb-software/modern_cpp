#include <iostream>

using namespace std;

class A
{
    char *a;
public:
    A()                { cout << "Const A" << endl;  a = new char[100]; }
    A(const A& other)  { cout << "A(A&)"   << endl;  a = other.a; }
    A(const A&& other) { cout << "A(A&&)"  << endl;  a = other.a; }
    virtual ~A()       { cout << "Dest  A" << endl;  delete [] a; }
};

class B : public A
{
    char *b;
public:
    B()  { cout << "Const B" << endl;  b = new char[100]; }
    ~B() { cout << "Dest  B" << endl;  delete [] b; }
};

class C : public B
{
    char *c;
public:
    C()  { cout << "Const C" << endl; c = new char[100]; }
    ~C() { cout << "Dest  C" << endl; delete [] c; }
};

void deleteA(A* a)
{
    cout << "Deleting Object" << endl;
    delete  a;
}

int main()
{
    A *a = new A; // Const A
    deleteA(a); // Delteting Object -> Dest A

    cout <<  "------------------------"  << endl;

    A *c = new C; // Const A -> Const B -> Const C
    deleteA(c); // Dest C -> Dest B -> Dest A 

    cout <<  "------------------------"  << endl;

    A a1 = A(); // Const A -> A(A&)
    A a2(a1); // A(A&) -> Dest A

    cout <<  "------------------------"  << endl;

    // TODO:Double free problem to be solved by implementing move constructor and move assignment operator

    return 0;
}