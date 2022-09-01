#include <iostream>
using namespace std;
int GetValue(){
    return 10;
}
int& GetValueRef()
{
    static int value = 10;
    
    return value;
}

void printName(string &name)
{
    cout << name;
}

void printName(string&& name) //rvalue reference
{
    cout << name; 
}

int main()
{
   // var is lvalue , 10 is rvalue means it has no location
   int i = 10; 
   i =  GetValue(); //OK
    //10 = i; //you can't do that
   GetValueRef() = 5; // Works Fine!

    
    string firstName = "Robotics"; //temp
    string lastName = "Corner"; //temp

    string fullName = firstName + lastName ;
 
   // printName(fullName);

    printName(firstName + lastName);

    return 0;
}