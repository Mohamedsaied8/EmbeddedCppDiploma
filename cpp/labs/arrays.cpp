
#include <iostream>
#include <array>

int main(){

    std::array<int,3> a;

    for(auto &i : a)
    {
      //  std::cin >> a[i];
       std::cin >> i;
    }
    
    for(auto i : a)
    {
        std::cout << i ;
    }


    return 0;
}