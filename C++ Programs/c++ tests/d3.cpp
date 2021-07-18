#include <iostream>
using namespace std;

void f() noexcept {}
void g() noexcept (!noexcept (f())) {}
void h() noexcept (noexcept (g())) {}
void m() noexcept (noexcept (f()) || noexcept (g())) {}

int main () {
    cout << (noexcept (f()) ? 1:0);
    cout << (noexcept (g()) ? 1:0);
    cout << (noexcept (h()) ? 1:0);
    cout << (noexcept (m()) ? 1:0);
    return 0;
}