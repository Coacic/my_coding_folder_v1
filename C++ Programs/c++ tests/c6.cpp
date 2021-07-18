#include <iostream>
using namespace std;

class A {
    int x, y;
public:
    A(int xx, int yy) : x(xx) , y(yy){}
    double div() { if (y == 0) throw x; return x/y; }
    int mod() { if (y == 0) throw 0; return x % y; }
};

int main() {
    A a(4, 0), aa(3, 5);
    try { cout << a.div(); } catch(int x) { cout << x; }
    try { cout << a.mod(); } catch(int x) { cout << x; }
    try { cout << aa.div(); } catch(int x) { cout << x; }
    try { cout << aa.mod(); } catch(int x) { cout << x; }
    return 0;
}