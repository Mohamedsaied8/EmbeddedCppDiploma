#include <iostream>  // standard
// #include "iostream"     // non standard
#include <array>

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};   // POD
    //             0,1,2,3,4,5,6,7,8,9

    std::cout << "size of array: " <<    sizeof(arr) << "\n";
    std::cout << "size of array[0]: " << sizeof(arr[0]) << "\n";

    return EXIT_SUCCESS;
}