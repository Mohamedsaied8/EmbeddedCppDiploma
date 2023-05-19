#include <iostream>  // standard
// #include "iostream"     // non standard
#include <array>    // https://cplusplus.com/reference/array/array/

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};   // POD
    //             0,1,2,3,4,5,6,7,8,9

    std::cout << "first element: " << arr[0] << "\n";
    std::cout << "last element: " << arr[10] << "\n";
    std::cout << "-1 element: " << arr[-1000000] << "\n";

    std::cout << "--------------------------------------\n";

    std::array<int, 10> arr_stl = {1,2,3,4,5,6,7,8,9,10};
    // std::array<float, 10> arr_stl;
    // std::array<std::string, 10> arr_stl;

    // https://cplusplus.com/reference/array/array/size/
    std::cout << "size of array: " << arr_stl.size() << "\n";
    // https://cplusplus.com/reference/array/array/front/
    std::cout << "first element: " << arr_stl.front() << "\n";
    // https://cplusplus.com/reference/array/array/back/
    std::cout << "last element: " << arr_stl.back() << "\n";

    std::cout << "--------------------bad access------------------\n";
    std::cout << "first element: " << arr_stl[0] << "\n";
    std::cout << "last element: " << arr_stl[10] << "\n";
    std::cout << "-1 element: " << arr_stl[-1000000] << "\n";
    std::cout << "--------------------secure access------------------\n";
    // https://cplusplus.com/reference/array/array/at/
    std::cout << "first element: " << arr_stl.at(0) << "\n";
    std::cout << "last element: " << arr_stl.at(11) << "\n";
    std::cout << "-1 element: " << arr_stl.at(-1000000) << "\n";

    return EXIT_SUCCESS;
}