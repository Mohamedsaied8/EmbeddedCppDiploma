#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

// int main(int argc, char** argv)     // pointer to pointer
int main(int argc, char* argv[])    // pointer -> array
{
    std::cout << "argc: " << argc << "\n";

    std::string str1 = argv[1];
    if(str1 == "1")
    {
        std::cout << "arg[0]: " << argv[0] << "\n";
        std::cout << "arg[1]: " << argv[1] << "\n";
        std::cout << "arg[2]: " << argv[2] << "\n";

        std::cout<< "hello\n";
    }
}