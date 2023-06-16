#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Searching example
    std::vector<int> numbers = {5, 2, 9, 1, 7, -5, 3, 6, -33};

    int searchValue = 2;
    // std::find works with iterators so it's working for most of stl containers
    auto it = std::find(numbers.begin()+1, numbers.end() , searchValue);   // https://cplusplus.com/reference/algorithm/find/?kw=find

    if (it != numbers.end()) {
        std::cout << "Found " << searchValue << " at index " << std::distance(numbers.begin(), it) << std::endl;

        // remember that you can access the value using *it like a pointer
        // Get the address of the element using the & operator(someone asked me about this before)
        int* address = &(*it);
    }
    else
    {
        std::cout << searchValue << " not found." << std::endl;
    }

    // Sorting example
    std::vector<int> unsortedNumbers = {5, 2, 9, 1, 7, 3, 6};

    std::sort(unsortedNumbers.begin(), unsortedNumbers.end());  // same as the line below
    // std::sort(unsortedNumbers.begin(), unsortedNumbers.end(), std::less<int>());    // https://cplusplus.com/reference/functional/less/
    std::sort(unsortedNumbers.begin(), unsortedNumbers.end(), std::greater<int>()); // reverse the sorting, descending order

    std::cout << "Sorted numbers: ";
    for (const auto& num : unsortedNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // return 0;
}
