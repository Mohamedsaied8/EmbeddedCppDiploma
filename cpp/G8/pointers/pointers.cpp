#include <iostream>

namespace
{
    int* int_ptr1;
}

bool assignPtrValue(int* ptr);

int main()
{
    int* int_ptr1;  // variable shadowing
    int myInt = 10;
    std::cout << "myint: " << myInt << ", add int_ptr1: " << ::int_ptr1 << ", value int_ptr1: "
                << *int_ptr1 << "\n";

    int_ptr1  = &myInt; // get address
    *int_ptr1 = 11; // myInt = 11; * access the value
    std::cout << "myint: " << myInt << ", add int_ptr1: " << int_ptr1 << ", value int_ptr1: "
                << *int_ptr1 << "\n";

    int* new_ptr = nullptr;
    void* new_void_ptr = &myInt;
    // std::cout << "new_void_ptr: " << *((int*)new_void_ptr) << "\n";
    std::cout << "new_void_ptr: " << *(static_cast<int*>(new_void_ptr)) << "\n";

    // std::cout << "value new_ptr: " << *new_ptr << "\n";
    auto rc = assignPtrValue(new_ptr);
    if(rc == true)
    {
        std::cout << "value new_ptr: " << *new_ptr << "\n";
    }

    return 0;
}

bool assignPtrValue(int* ptr)
{
    // if(!ptr)
    if(ptr != nullptr)
    {
        std::cout << "new_ptr is not null\n";
        *ptr = 10;

        return true;
    }
    else
    {
        return false;
    }
}