#include <iostream>
#include <string>

using namespace std;

// syntax
// common mistake is to forget the ; at the end of the class\struct
// classes can hold data\variables and functions
// you can think of classes as a user defined data type
class class_name
{
    private:
    // data private
};

struct struct_name
{
    public:
    // data public
};

//------------------------------------------------------------------------------------------

class Person_class
{
    public:
    std::string m_name;

    // this is called a member function or sometimes it's called method
    void printName()
    {
        cout << __PRETTY_FUNCTION__ << " || person Name: " << m_name << "\n";
    }

    void setName(const std::string& name)
        {
            m_name = name;
        }

    void setName()
    {
        std::cout << "please enter the name\n";
        std::cin >> m_name;
    }
};

namespace my_struct_namespace
{
    struct Person_struct
    {
        // this is called a member function or sometimes it's called method
        void printName()
        {
            cout << __PRETTY_FUNCTION__ << " || person Name: " << m_name << "\n";
        }

        void setName(const std::string& name)
        {
            m_name = name;
        }

        private:
        // this is called a member variable
        std::string m_name;
    };
}

int main()
{
    // printName();     // compiler error, printName is part of the class\method

    Person_class person1;       // the variable person1 is called an object
    // person1.setName("Ahmed");
    person1.m_name="ahmed";
    person1.setName();
    person1.printName();

    Person_class person3;       // the variable person1 is called an object
    person3.setName("Ali");
    person3.printName();

    // Person_struct is within my_struct_namespace namespace so we must use `my_struct_namespace::` to access the namespace
    // or expand the namespace by calling `using namespace my_struct_namespace`
    my_struct_namespace::Person_struct person2;      // the variable person2 is also called an object
    person2.setName("Ahmed");
    person2.printName();
}