#include <iostream>
using namespace std;

class Klasa {};

int main () {
    try {
        try {
            cout << "0";
            throw Klasa();
            cout << "1";
        }
        catch (...) { cout << "2"; }
        cout << "3";
    }
    catch (Klasa i) {cout << "4"; }
    cout << "5";
    return 0;
}