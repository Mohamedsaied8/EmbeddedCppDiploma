#include <iostream>
using namespace std;

// int calc();
auto calc(int, int) -> int;
int divide(int x, int y);

int main() {
  int arr;
  arr = 10;
  std::cout << "address of arr: " << &arr
            << "\nsize of  arr: " << sizeof(arr);

  int* ptr; // point point to address in memory
  ptr = &arr;
  std::cout << "\naddress of ptr: " << ptr;
  //ptr = &arr;
  *ptr = 15;
  std::cout << "\naddress of ptr: " << arr;

  void* ptrToptr =  &ptr;

  int myArray[10]; //4
  myArray[0] = 0;
  myArray[1] = 5;
  //int* arr_ptr1 = &myArray[0];
  int* arr_ptr1 = myArray;

  //arr_ptr1 += 1;    // myArray[1]
  arr_ptr1 ++;

  std::cout << "\n\n val arr of 1: " << myArray[1]
            << "\ntest_ptr:" << *arr_ptr1;

  std::cout << "\n\n add arr of 1: " << &myArray[1]
            << "\ntest_ptr:" << arr_ptr1;

  int* ptrx = &myArray[1];
  ptrx = arr_ptr1 + 2;
  std::cout << "\n\nptrx : " << ptrx << "\n";

  int* ptry = NULL;
  // this will cause a crash
  std::cout << "\n\nptr Crash : " << *(ptry+1) << std::endl;

}
