#include <iostream>
#include <array>

// c style
typedef unsigned long int mytype;

// C++ style
using phoneNumber_t = unsigned long int;

// C++ style example
using myArray_t = std::array<std::array<float,3>, 3>;

int main()
{
    myArray_t                          array_1 = {0,0,1,2,2,2,2,3,4};
    std::array<std::array<float,3>, 3> array_2 {};

    std::array<int, 11> array_3;

    // objective modify only the first 5 elements = 1
    mytype counter = 0;

    // you can see the limitation for range based for
    // for(auto& i : array_3)
    // {
    //     if(counter < 6)
    //     {
    //         i = ++counter;
    //     }
    // }

    // for(int i = 0 ; i < array_3.size(); ++i)
    // {
    //     std::cout << "before if current index: " << i << "\n";
    //     if(i == 5)
    //     {
    //         continue;
    //     }
    //     // lines
    //     std::cout << "after if current index: " << i << "\n";
    // }

    counter = 10;
    while((counter < 10))
    {
        std::cout << "incrementing the counter: " << counter << "\n";
        // counter++;
    }

    do
    {
        std::cout << "inside do while\n";
        continue;
    }
    while ((counter < 10));

    // good C++ syntax but bad practice
    for(double i = 0 ; i < 3.7 ; i=i+0.1)
    {
        std::cout << "the weird if\n";
    }


    // for(; ;)
    // {
    //     std::cout << "the ;; for" << "\n";
    // }

    for (int i = 1; i < 5 ; i++)
    {
        // i = 2
        for (int j = 1; j <= i; j++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    std::cout << "exited for loop\n";
}
