#include <iostream>
#include <functional>   // std::function
#include <algorithm>
#include <vector>

bool isOdd(int num)
{
    bool result = (num%2);
    return result;
}


// full explication: https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170

int g_counter = 0;
const std::string g_name = "Anas";

int main()
{
    // some variables
    int myAge = 30;

    // lambda syntax
    auto lambda_func_basic_1 = [](){};
    std::function<void()> lambda_func_basic_2 = [](){};
    auto lambda_func_basic_3 = []() -> void {};

    // capture clause
    auto increment_counter = [](){
        g_counter++;
        std::cout << "incremented counter, new value: " << g_counter << "\n";
    };
    increment_counter();


    auto increment_age_1 = [&](){
        myAge++;
        lambda_func_basic_1();
        std::cout << "incremented age, new value: " << myAge << "\n";
    };
        increment_age_1();
    // increment_age_2();

    auto increment_age_2 = [&myAge](){
        ++myAge;
        std::cout << "incremented age, new value: " << myAge << "\n";
    };

    auto increment_age_3_bad = [](int& ageRef){  // copy of the original variable not reference or pointer
        ageRef++;
        std::cout << "incremented age, new value: " << ageRef << "\n";
    };

    auto isOdd_1 = [](int num) -> bool
    {
        bool result = (num%2);
        return result;
    };


    increment_age_3_bad(myAge);

    std::cout << "real age: " << myAge << "\n";

    bool result = isOdd_1(10);
    std::cout << "isOdd_1(10) return: " << result << "\n";
    bool result2 = isOdd(10);
    std::cout << "isOdd(10) return: " << result2 << "\n";

    //------------------------------------------------------------------------------
    // real example:

    std::vector<int> vec{1,2,3,4,5};

    std::for_each(vec.begin(), vec.end(), [](int num){std::cout << "for_each::lambda, num="<<num<<"\n";});

    auto found_number = std::find_if(vec.begin(), vec.end(), [](int num) ->bool {return (num==6);});

    if (found_number != vec.end())
    {
        std::cout << "number found: " << *found_number << "\n";
    }
    else
    {
        std::cout << "number was not found!\n";
    }

    return EXIT_SUCCESS;
}