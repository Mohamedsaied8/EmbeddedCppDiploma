#include <iostream>
#include <list>
#include <algorithm>

int main() {
    // https://cplusplus.com/reference/list/list/?kw=list
    std::list<int> myList; // Create an empty linked list

    // Insert elements at the back of the list
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    myList.push_back(40);
    myList.push_back(50);

    // Insert elements at the front of the list
    myList.push_front(5);
    myList.push_front(2);
    myList.push_front(0);

    // Print the list
    std::cout << "List after insertions: ";
    for (const auto& element : myList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Delete elements from the list
    myList.pop_front(); // Remove the first element
    myList.pop_back();  // Remove the last element

    // Print the list after deletions
    std::cout << "List after deletions: ";
    for (const auto& element : myList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Delete an element from the middle of the list
    int elementToDelete = 10;
    auto it = std::find(myList.begin(), myList.end(), elementToDelete); // https://cplusplus.com/reference/algorithm/find/?kw=find

    if (it != myList.end()) {
        // Element found, erase it
        myList.erase(it);

        // Print the list after deletion
        std::cout << "List after deletion: ";
        for (const auto& element : myList) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    else{
        std::cout << "Element not found in the list." << std::endl;
    }

    // return 0;
}
