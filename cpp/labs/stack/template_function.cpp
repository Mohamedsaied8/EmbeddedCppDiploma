#include <iostream>

template <class M>
M max(M a,M b)
{
    return a>b?a:b; //ternary operator
}
int main()
{

    std::cout << max(5,3) << std::endl;


    return 0;
}