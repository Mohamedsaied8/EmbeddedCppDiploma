#include <iostream>
#include <vector>

int main()
{
    
    // POD -> plain old datatype
    // int float bool double uint8_t int*
    std::vector<int> container {1,2,4};
    std::vector<int> container2 {1,2,7,7};

    container.at(1);
    // int*

    //          container.at(0)             container.at(3)
    // for(std::vector<int>::iterator it = container2.begin(); it < container2.end() ;it++)
    for(auto it = container2.begin(); it < container2.end() ;it++)
    {
        // (*it)++;
        std::cout << *it << " " ;
    }
    std::cout<<"\n";

    return 0;
}