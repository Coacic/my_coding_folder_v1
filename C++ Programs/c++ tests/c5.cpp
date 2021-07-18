#include <iostream>

class A
{
public:
    virtual ~A() { std::cout << "Destructor A" << std::endl;}
    virtual void test() = 0;
};

class B : public A
{
public:
    B() { std::cout << "Constructor B" << std::endl;}
    virtual ~B() { std::cout << "Destructor B" << std::endl;}
};

void f(int i, int& j) { i++; j++; }

int main(){
    for (int i = 0, j = 0; i < 3 && j < 4; f(i, j))
        std::cout << '*';
    return 0;
}