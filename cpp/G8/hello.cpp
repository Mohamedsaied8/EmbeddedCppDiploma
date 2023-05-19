#include <iostream>
#define NAME "ANAS"

// forward decleration
void print_info(float num); // protptye

float divideByTwo(int num)
{
    // num automatic variable --> stack
    float ret = num/2.0;  // automatic variable --> stack
    return ret;
}

int main()
{
    std::cout << "hello world" << NAME << std::endl;
    print_info(3.14f);

    int num = 11;
    divideByTwo(num);
    float myReturn = divideByTwo(num); // rvalue

    float myReturnXX = 10;          // literal(rvalue)
    float myReturnYY = myReturn;    // variable(lvalue)

     std::cout << myReturn << "\n";

    return 0;
}