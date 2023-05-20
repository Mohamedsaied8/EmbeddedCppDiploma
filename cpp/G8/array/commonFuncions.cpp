#include <iostream>
#include <array>

// auto print_array(std::array<float,4> myArray) -> void
void print_array(std::array<float,4> myArray)
{
    // 0 : 3
    std::cout << "----------------------------------\n";
    for(int it=0; it<myArray.size() ; ++it)
    {
        std::cout << "arr["<<it<<"]: "<< myArray.at(it) << "\n";
    }
    std::cout << "----------------------------------\n";
}
