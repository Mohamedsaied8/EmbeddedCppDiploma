#include <cctype>
#include <string>
#include <iostream>
#include <algorithm>

int main() {

    std :: string str_ = "AUstralian FrencH WimBleDon Us";
    std :: cout << "Mixed case string : " << str_ << std :: endl;

    // Declare lambda
    auto lambda_to_lower = [] ( unsigned char c ) { return std :: tolower(c); };
    auto lambda_to_upper = [] ( unsigned char c ) { return std :: toupper(c); };

    // Converting a string to lower case using transform algorithm and a lambda expression.
    std :: transform (str_.begin(), str_.end(), str_.begin(), lambda_to_lower); 
    std :: cout << "String lowercase : " << str_ << std :: endl;

    // Converting to upper case
    std :: transform (str_.begin(), str_.end(), str_.begin(), lambda_to_upper); 
    std :: cout << "String uppercase : " << str_ << std :: endl;

    return 0;
}