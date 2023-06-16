#include <iostream>
#include <vector>
#include <algorithm>

// Custom sorting function
bool customSort(const std::string& str1, const std::string& str2) {
    return (str1.length() > str2.length()); // Sort by string length
}

int main() {
    std::vector<std::string> words = {"apple", "orange", "banana", "grape", "pear"};

    std::sort(words.begin(), words.end(), customSort);

    std::cout << "Sorted words by character number: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;


    // --------------------------------------------------
    // Finding
    std::string name = "anas";
    std::string fruit = "pear";

    auto it1 = std::find(words.begin(), words.end(), name);
    if(it1 != words.end())
    {
        std::cout << "word: " << name << " was found in the vector.\n";
    }
    else
    {
        std::cout << "word: " << name << " was NOT found\n";
    }

    auto it2 = std::find(words.begin(), words.end(), fruit);
    if(it2 != words.end())
    {
        std::cout << "word: " << fruit << " was found in the vector.\n";
    }
    else
    {
        std::cout << "word: " << fruit << " was NOT found\n";
    }

    return 0;
}
