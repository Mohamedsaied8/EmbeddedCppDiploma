#include <iostream>
#include <vector>

using int_vect = std::vector<int>;

// global variables
std::vector<int> myVect;    // this the only one used

int_vect myVect_2;

int main()
{
    // local vars on the stack
    std::vector<int> myVect_local;
    int_vect myVect_2_local;

    std::cout << "myVect size: " << myVect.size()<< "\n";
    // std::cout << "First element: " << myVect.at(0)<< "\n";

    myVect.push_back(10);
    myVect.push_back(12);
    myVect.push_back(13);
    myVect.push_back(20);

    std::cout << "myVect size: " << myVect.size() << "\n";
    std::cout << "last element: " << myVect.back() << "\n";
    std::cout << "first element: " << myVect.front() << "\n";
    std::cout << "pop\n";
    myVect.pop_back();
    std::cout << "last element: " << myVect.back() << "\n";
    std::cout << "first element: " << myVect.front() << "\n";
    myVect.at(0) = 11;

    std::cout << "myVect size: " << myVect.size() << "\n";
    std::cout << "First element: " << myVect.at(0)<< "\n";
    std::cout << "First element: " << myVect[0]<< "\n";

}