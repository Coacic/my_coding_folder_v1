#include <iostream>
using namespace std;

class X {
public:
    X() { cout << 'X'; }
    X(char c) { cout << 'X' << c; }
};

class A : virtual X {
public:
    A() : X('a') { cout << 'A'; }
};

class B : X {
public:
    B() : X('b') { cout << 'B'; }
};

class C : virtual X {
public:
    C() : X('c') { cout << 'C'; }
};

class Y : A, virtual B, C {
public:
    Y() { cout << 'Y'; }
};

int main() {
    Y a;
	return 0;
}