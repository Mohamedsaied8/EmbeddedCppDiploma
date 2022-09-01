
//Modular Programming

#include <iostream>
#include <iomanip>
#include <cctype>

//protortpe
void displayName();


namespace calculations
{

    std::uint16_t add(std::uint16_t n1,std::uint16_t n2)
    {
        return n1+n2;
    }
      std::int16_t sub(std::uint16_t n1,std::uint16_t n2)
    {
        return n1-n2;
    }

}


int main()
{
   // displayName();
    char op = '+';
    std::uint16_t num1=0;
    std::uint16_t num2 = 0;
    std::cout << "Enter first number\n";
    std::cin >> num1;
    std::cout << "Enter second number\n";
    std::cin >> num2;
    std::cout << "Enter operator\n";
    std::cin >> op;
    switch(op)
    {
        case '+': 
            std::cout << calculations::add(num1,num2) << std::endl;
            break;
        case '-':
            std::cout  << calculations::sub(num1,num2) << std::endl;
            break;
        default:
            std::cout << "please enter a valid operator" << std::endl;
            break;
    }



    return 0;
}

