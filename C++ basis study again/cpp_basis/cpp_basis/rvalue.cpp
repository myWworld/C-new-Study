#include <iostream>

void foo(int& x) { std::cout << "lvalue ref\n"; }
void foo(int&& x) { std::cout << "rvalue ref\n"; }

//int main() {
//    int a = 10;
//    foo(a);    // lvalue → foo(int&) 호출
//    foo(20);   // rvalue → foo(int&&) 호출
//    foo(a + 1); // rvalue → foo(int&&) 호출
//}