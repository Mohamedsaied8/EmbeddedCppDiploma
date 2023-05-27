#include <iostream>
#include <array>

int main()
{
    std::array<int, 10> array;

    // c style loop
    for(int x; x<array.size() ; ++x)
    {
        std::cout << "arr[" << x << "]: " << array[x] << "\n";
        array[x]++;
    }

    // new C++
    // loop by reference
    for (auto& var : array)
    {
        std::cout << "arr[" << "?" << "]: " << var << "\n";
        var++;
    }
    for (int& var : array)
    {
        std::cout << "arr[" << "?" << "]: " << var << "\n";
        var++;
    }

    // loop by value
    for (auto var : array)
    {
        std::cout << "arr[" << "?" << "]: " << var << "\n";
        var++;
    }
    // loop by value
    for (float var : array)
    {
        std::cout << "arr[" << "?" << "]: " << var << "\n";
        var++;
    }

    // loop by const reference
    for (const auto& var : array)
    {
        std::cout << "arr[" << "?" << "]: " << var << "\n";
        // var++; // error
    }
    for (const int& var : array)
    {
        std::cout << "arr[" << "?" << "]: " << var << "\n";
        // var++; // error
    }
}