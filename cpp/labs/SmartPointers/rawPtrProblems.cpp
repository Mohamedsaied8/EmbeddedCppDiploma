#include <iostream>

void fun()
{
    char *ptr = new char[10]; //heap
    delete ptr; 
    delete ptr; 
    //some logic
    memcpy(ptr,"string",10); //dangling pointer

}
int main()
{

   while(1)
    {
        fun(); //memory leak problem
    }


    return 0;
}