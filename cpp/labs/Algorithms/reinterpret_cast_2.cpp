#include <iostream>

int main() {
    const char* originalString = "Hello, world!";

    // Casting the original string to a void pointer using reinterpret_cast
    void* voidPointer = const_cast<char*>(originalString);

    // Converting the void pointer back to a char pointer using reinterpret_cast
    char* charPointer = reinterpret_cast<char*>(voidPointer);

    // Printing the original string
    std::cout << "Original string: " << charPointer << std::endl;

    return 0;
}
