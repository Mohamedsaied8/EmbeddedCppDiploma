#include <iostream>

class Entry
{

};
int main()
{
    char buf[20]; //in stack
    Entry *entry = new (buf) Entry(); 
    

    return 0;
}