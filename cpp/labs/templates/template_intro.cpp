#include <iostream>

// templates are the core of STL library
// template must be defined in the same header it was declared
// the compiler will use the function to generate new function according to what you used

// template<typename T>
template<class T, class b>
T add(T num1, b num2)
{
    return num1 + num2;
}

template<typename T>
bool isEven(T num)
{
    return !(num%2);
}

int main()
{
    int num1 = 5;
    int num2 = -3;
    float num3 = 2.1;
    float num4 = -7.6;

    auto result1 = add<int,int>(num1, num3); // same as above
    // int result1 = add(num1, num2); // OK --> will deduce the type form the input
    int result1 = add(num1, num3); // OK --> will deduce the type form the input
    std::cout << "add int: " << result1 << "\n";

    auto result2 = add<float>(num3, num1); //OK
    // auto result2 = add(num3, num4); //OK
    std::cout << "add float: " << result2 << "\n";

    // bool even = isEven(num1);
    bool even = isEven<int>(num1);
    std::cout << "isEven int: " << even << "\n";

    bool even2 = isEven(num3);   // ill-formed float can't use %
}