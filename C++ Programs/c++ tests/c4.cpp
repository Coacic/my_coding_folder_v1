#include <iostream>
using namespace std;

class A {
public:
    virtual void m() {}
};
class B : public A {};
class C : public B {};

int main () {
    A *pa = new B();
    B *pb = new C();
    B *b = dynamic_cast <B*>(pa);
    C *c = dynamic_cast <C*> (pa);
    C *d = dynamic_cast <C*> (pb);
    if (b == nullptr) cout << 'b';
    if (c == nullptr) cout << 'c';
    if (d == nullptr) cout << 'd';
    return 0;
}
