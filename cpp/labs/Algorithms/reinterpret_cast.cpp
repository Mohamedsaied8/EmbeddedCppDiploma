#include <iostream>

int main()
{
    int address= 0x3467;
    unsigned int* out_reg = reinterpret_cast<unsigned int *>(address);
    

    char stream[] = "A45C78_";   // null terminated c string
    std::cout << "sizeof(stream): " << sizeof(stream) << std::endl;
    std::cout << "stream: " << stream << "\n";
    void* ptr = static_cast<void*>(stream);
    // ptr --> wire
    std::cout << "stream as int: " << *reinterpret_cast<int*>(ptr) << "\n";
    std::cout << "stream as char: " << reinterpret_cast<char*>(ptr) << "\n";
    return 0;
}