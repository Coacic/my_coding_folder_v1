#include <iostream>
using namespace std;

template <typename T> class Klasa {
public:
    template <typename U> void m (U u) { cout << "1"; }
    void m (int u) {cout << "2"; }
};

template <typename T> class Klasa <T*> {
public:
    template <typename U> void m (U u) { cout << "3"; }
    void m (int u) {cout << "4"; }
};

int main () {
    Klasa <int*>().m<float>(9);
    Klasa <int> ().m(9);
    Klasa <int> ().m('a');
    Klasa <int*>().m<int>(2);
}