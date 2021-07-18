#include <iostream>

class K {
public:
    K(int k) { std::cout << k; }
};

class A {
    K k2 = 1, k1 = 2;
public:
    A(int i, int j) : k1(i), k2(j) {}
};

class B
{
public:
    B(){std::cout<<"B\n";}
    ~B(){std::cout<<"~B\n";}
};

class C
{
public:
    C(){std::cout<<"C\n";}
    ~C(){std::cout<<"~C\n";}
};

class D : public C
{
public:
    D(){std::cout<<"D\n";}
    ~D(){std::cout<<"~D\n";}
};

int main() {
    //A a(3, 4);
    D d;

    return 0;
}