#include <iostream>
#include <array>

void fillArray(float* array, int elementsCount)
{
    for(int i = 0 ; i<elementsCount; ++i)
    {
        std::cout << "fillArray_c::current iteration: " << i << "\n";
        array[i] = 0;
    }
}

///---------------------------------------------------------------------------
//! \brief overloaded function
//! 
//! \param myArray
//!
void fillArray(std::array<float,4>* myArray)
{
    for(int i = 0; i < myArray->size(); i++)
    {
        std::cout << "fillArray_cpp*::current iteration: " << i << "\n";
        // (*myArray).at(i) = 0;
        myArray->at(i) = 0;
    }
}

//---------------------------------------------------------------------------
//! \brief overload function
//! 
//! \param myArray
//!
void fillArray(std::array<float,4>& myArray)
{
    for(int i = 0; i < myArray.size(); i++)
    {
        std::cout << "fillArray_cpp&::current iteration: " << i << "\n";
        // (*myArray).at(i) = 0;
        myArray.at(i) = 0;
    }
}

// bool fillArray(std::array<float,4>& myArray)
// {
//     for(int i = 0; i < myArray->size(); i++)
//     {
//         std::cout << "fillArray_cpp::current iteration: " << i << "\n";
//         // (*myArray).at(i) = 0;
//         myArray->at(i) = 0;
//     }
// }

int main()
{
    float arr[4];
    float arr2[4];
    std::array<float,4> myArr;

    float myFloat = 3.14;

    float* arr_ptr;      // no init
    arr_ptr = arr2;   // init after deceleration
    arr_ptr = &myFloat;        // reassigned to a new value
    *arr_ptr = 5.8;

    std::cout << "myFloat: " << myFloat << "\n";
    float& arr_ref = myFloat;   // must be init
    arr_ref = 5.7;              // treated the same way as normal variables

    std::cout << "myFloat: " << myFloat << "\n";
    std::cout << "arr_ref: " << arr_ref << "\n";

    // fillArray(arr, 4);
    // fillArray(&arr[0], 4);
    // fillArray(&myArr);
    fillArray(myArr);
}