#include <iostream>
#include <vector>


int main()
{

    std::vector<int> container {1,2,4};

    char num = 9;
    auto qNum = num; 

    std::cout << sizeof(qNum) << " " << sizeof(num) << std::endl;
    
    for(auto it = container.begin(); it !=container.end() ;it++)
    {

        std::cout << *it << " " ;
    }

    return 0;
}