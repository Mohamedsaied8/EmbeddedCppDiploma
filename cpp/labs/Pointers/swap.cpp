
// x = 8 , y = 5 
//swap(x,y)
// x = 5 , y =8

#include <iostream>

void swap(int *n1,int *n2)
{
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
int add(int n1,int n2)
{
    return n1+n2;
}

int main()
{
    int x = 8;
    int y = 5;

    x = add(x,y); //pass by value
    
    swap(&x,&y); //pass by reference

    std::cout << "x:" << x <<" y:" << y << std::endl;

    return 0;
}