#include <iostream>
#include <array>

using namespace std;

// int main(int argc, char** argv)     // pointer to pointer
int main(int argc, char* argv[])    // pointer -> array
{
    // matrix**
    int  matrix[2]
                    [3] { {1,20,7} , {12,15,600} };

    std::cout << &matrix[0][2] << "\n";
    std::cout << "value of matrix[[0][3]]:"
                <<  matrix[0][3] << "\n";
    std::cout << "value of matrix[[1][0]]:"
                <<  matrix[1][0] << "\n";
    std::cout << "address of matrix[[0][3]]:"
                <<&matrix[0][3] << "\n";

    std::cout << "--------------------------------\n";
    // stl array
    std::array< std::array<int,3> , 2> stl_array { 1, 20 ,7 , 12, 15,600 };
  // large array, smaller array

    std::cout << &stl_array[0][2] << "\n";
    std::cout << "value of stl_array[[0][3]]:"
                <<  stl_array[0][3] << "\n";
    std::cout << "value of stl_array[[1][0]]:"
                <<  stl_array[1][0] << "\n";
    std::cout << "address of stl_array[[0][3]]:"
                <<&stl_array[0][3] << "\n";

    // good
    std::cout << "stl_array[[0][2]]:"
                << stl_array.at(0).at(2) << "\n";

    // out of range
    std::cout << "stl_array[[0][3]]:"
                << stl_array.at(0).at(3) << "\n";

    return EXIT_SUCCESS;
}