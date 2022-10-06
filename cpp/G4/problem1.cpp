//Program Description
// Get input from user
// Apply conversion formula
// display output on console

//fundamental data types
// integers : char ,int , unsigned int , long , unsigned long
// decimal point number : float , double , long double
#include <iostream>

int main()
{
    float mile;
    std::cout << "size of float " << sizeof(float) << std::endl;

    //compile time replacement
    constexpr float MILE_TO_KM = 1.6;

    std::cout << "please enter Distance in miles";
    std::cin >> mile;

    float  kilometer = mile * MILE_TO_KM;

    std::cout << kilometer << std::endl;

    return 0;
}
