#include <iostream>
#include <algorithm>

using namespace std;

class A
{
    char *a;
public:
    A()
    {
        cout << "Const A" << endl;  a = new char[100];
    }

    A(const A& other)
    {
        cout << "A(A&)"<< endl;
        a = new char[100];
        std::memcpy(a, other.a, 100); // eventually std::copy
    }

    A(A&& other)
    {
        cout << "A(A&&)"  << endl;  a = other.a;
        other.a = nullptr;
    }
    
    virtual ~A()
    {
        cout << "Dest  A" << endl;
        delete [] a;
    }
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
    cout <<  "------------------------"  << endl;
    A *a = new A; // Const A
    deleteA(a); // Delteting Object -> Dest A


    cout <<  "------------------------"  << endl;
    A *c = new C; // Const A -> Const B -> Const C
    deleteA(c); // Dest C -> Dest B -> Dest A


    cout <<  "------------------------"  << endl;
    A a1 = A(); // Const A
    A a2(std::move(a1));

    // delete for nullptr is safe, so no need to check if a1.a is nullptr

    return 0;
}