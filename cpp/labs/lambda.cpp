#include <iostream>
#include <algorithm>
#include <array>

int main() {
  //  int arr[] = { 1, 2, 3, 4, 5 };
   std::array<int,5> arr = { 1, 2, 3, 4, 5 };
    int mul = 5;
  //   std::for_each(arr, arr + sizeof(arr) / sizeof(int), [&](int x) {
    //     std::cout<<x<<" ";
     std::for_each(arr.begin(), arr.end(), [&](int x) {
        std::cout<< x <<" ";
        // Can modify the mul inside this lambda function because
        // all outer scope elements has write access here.
            mul = 3;
        });
    std::cout << std::endl;
    std::for_each(arr.begin(), arr.end(), [=](int &x) {
        x= x*mul;
        // Can not modify the mul inside this lambda function because
        // all outer scope elements has read only access here.
        // mul = 9;
        });
    std::cout << std::endl;
    std::for_each(arr.begin(), arr.end(), [](int x) {
        // No access to mul inside this lambda function because
        // all outer scope elements are not visible here.
        // std::cout<<mul<<" ";
        });
    std::cout << std::endl;

}