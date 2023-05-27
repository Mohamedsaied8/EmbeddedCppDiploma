#include <iostream>
#include <vector>

using int_vect = std::vector<int>;

// global variables
std::vector<int> myVect;    // this the only one used

int_vect myVect_2;

int main()
{
    // local vars on the stack
    std::vector<int> myVect_local {1,2,3,4};
    int_vect myVect_2_local(4);

    std::cout << "myVect size: " << myVect.size()<< "\n";
    // std::cout << "First element: " << myVect.at(0)<< "\n";
    std::cout << "myVect capcity: " << myVect.capacity() <<"\n";

    myVect.push_back(10);
    std::cout << "myVect capcity: " << myVect.capacity() <<"\n";
    myVect.push_back(12);
    std::cout << "myVect capcity: " << myVect.capacity() <<"\n";
    myVect.push_back(13);
    std::cout << "myVect capcity: " << myVect.capacity() <<"\n";
    myVect.push_back(20);
    std::cout << "myVect capcity: " << myVect.capacity() <<"\n";
    myVect.push_back(20);
    std::cout << "myVect capcity: " << myVect.capacity() <<"\n";

    std::cout << "myVect size: " << myVect.size() << "\n";
    std::cout << "last element: " << myVect.back() << "\n";
    std::cout << "first element: " << myVect.front() << "\n";
    std::cout << "pop\n";
    myVect.pop_back();
    std::cout << "last element: " << myVect[3] << "\n";
    std::cout << "myVect size: " << myVect.size() << "\n";
    std::cout << "last element: " << myVect.back() << "\n";
    std::cout << "first element: " << myVect.front() << "\n";
    std::cout << "first element: " << myVect.at(0) << "\n";


}
