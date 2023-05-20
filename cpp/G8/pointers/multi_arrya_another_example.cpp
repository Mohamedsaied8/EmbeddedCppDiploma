#include <array>
#include <iostream>

using namespace std;

int main()
{
    int matrix[4][3];

    array<array<int ,3>, 4> myArray =
        {0,1,2, // of 0
        3,4,5,  // of 1
        6,7,8,  // of 2
        9,10,11};// of 3

    int x = 13;
    int x2{13};
    // https://stackoverflow.com/questions/17759757/multidimensional-stdarray
    array<array<int ,3>, 4> myArray2 {  // init
        { {1,20,7} , {12,15,600}, {12,15,600}, {12,15,600} }  // value
        };

    std::cout << "5 === " << myArray[1][2] << "\n";

    // for(auto& var : myArray)
    for(array<int ,3>& var : myArray)
    {
        // for(auto& secondVar : var)
        for(int& secondVar : var)
        {
            std::cout << secondVar << ",";
        }

        std::cout << "\n";
    }

    // return EXIT_SUCCESS;
    return 0;
}