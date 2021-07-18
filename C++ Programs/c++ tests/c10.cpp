#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "A"; }
    A(int a) { cout << "A" << a; }
};

class B {
    A a;
public:
    B() { cout << "B"; }
    B(int b) { cout << "B" << b; }
};

class C {
    B b;
    A a;
public:
    C() { cout << "C"; }
    C(int c) : a(c) { cout << "C" << c; }
};

int main() {
    C c(1);
    return 0;
}