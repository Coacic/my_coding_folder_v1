#include <iostream>
using namespace std;

void fun(int p) {
    try {
        throw p;
    }
    catch (int p) { cout << ++p; throw; }
}

int main() {
    int p = 1;
    try {
        try {
            fun(p);
            cout << ++p;
        }
        catch (int p) { cout << ++p; }
        cout << ++p;
    }
    catch (int p) { cout << ++p; }
    return 0;
}