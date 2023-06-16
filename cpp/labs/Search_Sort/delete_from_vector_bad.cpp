#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> myVector = {10, 20, 30, 40, 50}; // Create a vector

    // Print the vector before deletion
    std::cout << "Vector before deletion: ";
    for (const auto& element : myVector) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Find the element to delete
    int elementToDelete = 30;
    auto it = std::find(myVector.begin(), myVector.end(), elementToDelete);

    if (it != myVector.end()) {
        // Element found, erase it
        ///WARNING: this is very inefficient as it requires shifting all subsequent elements to fill the gap left by the removed element, resulting in a linear time complexity.
        myVector.erase(it);

        // Print the vector after deletion
        std::cout << "Vector after deletion: ";
        for (const auto& element : myVector) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Element not found in the vector." << std::endl;
    }

    return 0;
}
