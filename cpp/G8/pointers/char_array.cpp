#include <iostream>
#include <string>

int main()
{
    // char  str1[14] = "Hello, world!\n"; // error, cant place null terminator
    char  str1[15] = "Hello, world!\n"; // ok
    char str2[]     = "Hello, world!\n";

    std::cout << "str1: " << str1 << "\n";
    std::cout << "str2: " << str2 << "\n";

    // https://cplusplus.com/reference/string/string/
    std::string str3 = "Hello, world!\n";
    std::cout << "str3: " << str3 << "size of str3: " << str3.size();
    str3 += "hi again\n";
    std::cout << "str3: " << str3 << "size of str3: " << str3.size();
}