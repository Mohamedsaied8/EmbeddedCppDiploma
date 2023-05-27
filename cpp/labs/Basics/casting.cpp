#include <iostream>
#include <limits>

void modify(float& pi)
{
    pi = 3.04;
}

void print(float& value)
{
    std::cout<< "Input value is: " << value << "\n";
}

// static_cast  /// xxxxxxx
// const_cast   // ??
// dynamic_cast // xx
// reinterpret_cast // ?

int main()
{
    // any POD can be converted
    // int num = 20;
    // float bigFloat = num; //No Error : implicit casting
   
   //  4                        1
   int x = std::numeric_limits<uint8_t>::max() + 1 +1;
    // Explicit conversion from double to int
    // int sum = x; //C-Style // wild card casting
    // int sum = (int)x; //C-Style // wild card casting

    // int sum = static_cast<int>(x); //C++-Style // static_cast
    // char 1 byte --> 0 to 255
    // auto sum = static_cast<char>(x); //C++-Style // static_cast

    // if num == 0 -> false otherwise true
    //              4             8
    auto sum = static_cast<uint8_t>(x); //C++-Style // static_cast
    std::cout << "Sum = " << static_cast<int>(sum) << "\n";

    sum = static_cast<int>(x+1);

    std::cout << "Sum = " << sum << "\n";

    //-------------------------------------------------------
    // const cast
    const float pi = 3.14;

    // Using const_cast to remove const qualifier
    float& nonConstRef = const_cast<float&>(pi);
    float* nonConstPTr = const_cast<float*>(&pi);

    std::cout << "Before modification: " << pi << std::endl;
    // modify(nonConstRef);
    const_cast<float&>(pi) = 3.04;  // undefined behaviour
    std::cout << "After modification: " << pi << std::endl; // undefined behaviour

    const float* pi_ptr = &pi;
    std::cout << "pi = " << *pi_ptr << "\n";

    // why we need it?
    // print(pi);  // compiler error
    print(const_cast<float&>(pi));

    return 0;
}