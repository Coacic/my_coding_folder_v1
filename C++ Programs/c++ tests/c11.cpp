#include <iostream>

class B;

class A {
public: 
    A(int i) {}
    A(const B &b) { std::cout << "1"; }
    A& operator=(const A& a) { std::cout << "2"; return *this; }
};

class B {
public: 
    operator A() { std::cout << "3"; return 1; }
};

int main() {
    B b;
    A a(1);
    a = b;
}