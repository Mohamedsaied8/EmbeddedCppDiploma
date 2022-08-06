#include <iostream>
#include "employee.h"

employee::employee() //default constructor
{
    std::cout << "Default Constructor" <<std::endl;
}
employee::employee(int id) //parameterized constructor
{
     std::cout << "paramterized Constructor" <<std::endl;
}
int main()
{
    employee emp;

    employee emp_me(5);
    
    std::cout << sizeof(employee) << std::endl;
    return 0;
}