#include <vector>
#include <iostream>
#include <algorithm>

int main()
{

    std::vector<int> vec;
    vec.push_back(3);
    vec.push_back(5);
    std::for_each(vec.begin(),vec.end(),[](int &element)->void{ element*=2; } );

    for(auto &item : vec)
    {
       std::cout << item << std::endl;
    }

    return 0;
}