#include <iostream>


int main()
{
    std::string name = "Robotics";
    std::string secondName = "Corner";
    name += secondName;

    std::cout << "name " << name  << std::endl;

    return 0;
}