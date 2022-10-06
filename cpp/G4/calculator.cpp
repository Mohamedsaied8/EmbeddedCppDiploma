// user enter two numbers
// enters operation
// apply operation
// display result

//refactor code with functions and namespace
#include <iostream>

 
namespace Computing{

    std::int32_t firstNum;
    std::int32_t secondNum;
    std::uint8_t operation; // example: '+'
    std::int32_t result;

   
    void Welcome()
    {
        std::cout << "please enter the first number" << std::endl;
        std::cin >> firstNum;
        std::cout << "please enter the second number" << std::endl;
        std::cin >> secondNum;
        std::cout << "please enter the desired operation" << std::endl;
        std::cin >> operation;
    }
    std::int32_t add()
    {
        return firstNum + secondNum;
    }
    std::int32_t sub()
    {
        return firstNum - secondNum;
    }
    void run()
    {
        switch(operation)
        {
            case '+':
                result = add();
                break;
            case '-':
                result = sub();
                break;
            
            default:
                std::cout << "please enter a valid operation" << std::endl;
                break;
         }

        std::cout << "result = " << result << std::endl;

    }
}

int main()
{
    Computing::Welcome();
    Computing::run();    

    return 0;
}