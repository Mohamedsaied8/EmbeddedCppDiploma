#include <iostream>

namespace mystd{

    class SmartPtr {
        int* ptr; // Actual pointer
    public:
        // Constructor: Refer https:// www.geeksforgeeks.org/g-fact-93/
        // for use of explicit keyword
        SmartPtr(int* p = NULL)
        {
            ptr = p;
        }

        // Destructor
        ~SmartPtr()
        {
            std::cout << "\ndeleting the pointer\n";
            delete (ptr);
        }


        // Overloading dereferencing operator
        int& operator*()
        {
            return *ptr;
        }
    };
}

int main()
{

    mystd::SmartPtr ptr(new int()); //address : value
    *ptr = 20;
    printf("%d", *ptr);

    std::cout << "in main\n";

    // We don't need to call delete ptr: when the object
    // ptr goes out of scope, the destructor for it is automatically
    // called and destructor does delete ptr.
    return 0;
}