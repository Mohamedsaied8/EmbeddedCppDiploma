#include <iostream>

int main()
{
    int address= 0x3467;
    unsigned int *out_reg = reinterpret_cast<unsigned int *>(address);
    
    return 0;
}