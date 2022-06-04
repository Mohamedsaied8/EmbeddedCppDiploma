#include <iostream>


int main()
{
   double x = 1.2;
    // Explicit conversion from double to int
    int sum = static_cast<int>(x+1);

    std::cout << "Sum = " << sum;

    return 0;
}