#include <iostream>
// A normal function with an int parameter
// and void return type
void fun(int a)
{
    std::cout << "Value of a is "
              << a << "\n";
    return;
}

// typedef void (*)(int) ptr;

using mySize = unsigned long;
// using the "using" keyword in C++ to define a pointer to a function that takes int and returns void(nothing)
using ptrFnc = void (*)(int);

int main()
{
    // fun_ptr is a pointer to function fun()
    void (*fun_ptr)(int) = &fun;
    // void (*fun_ptr)(int) = fun;

    // myPtr is a pointer to some function(not yet set) that takes int and returns void(nothing)
    ptrFnc myPtr;
    // myPtr is is now assigned the address of fun() which is a function that takes int and returns void(nothing)
    myPtr = fun;
    /* The above line is equivalent of following two
    void (*fun_ptr)(int);
    fun_ptr = &fun;
    */
    // Invoking fun() using fun_ptr
    (*fun_ptr)(10);
    fun_ptr(10);
    myPtr(10);
    return 0;
}