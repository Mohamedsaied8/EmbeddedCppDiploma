#include <iostream>
#include <functional>   // std::function
#include <algorithm>
#include <vector>

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

    auto increment_counter = [](){
        g_counter++;
        std::cout << "incremented counter, new value: " << g_counter << "\n";
    };

    auto increment_age_1 = [&](){
        myAge++;
        std::cout << "incremented age, new value: " << myAge << "\n";
    };

    auto increment_age_2 = [&myAge](){
        ++myAge;
        std::cout << "incremented age, new value: " << myAge << "\n";
    };

    auto increment_age_3_bad = [](int ageRef){  // copy of the original variable not reference or pointer
        ageRef++;
        std::cout << "incremented age, new value: " << ageRef << "\n";
    };

    auto isOdd_1 = [](int num) -> bool
    {
        bool result = (num%2);
        return result;
    };

    // -----------------------------------------------------------------------

    auto increment_age_3_good = [](int& ageRef){
        ageRef++;
        std::cout << "incremented age, new value: " << ageRef << "\n";
    };

    auto increment_age_copy_1 = [=](){
        // myAge++;
        std::cout << __PRETTY_FUNCTION__ << ": incremented age, new value: " << myAge << "\n";
    };

    auto increment_age_copy_2 = [=]() mutable{
        myAge++;
        std::cout << __PRETTY_FUNCTION__ << ": incremented age, new value: " << myAge << "\n";
    };

    //------------------------------------------------------------------------------

    increment_counter();
    increment_age_1();
    increment_age_2();
    increment_age_3_bad(myAge);
    increment_age_3_good(myAge);
    increment_age_copy_1();
    increment_age_copy_2();

    std::cout << "real age: " << myAge << "\n";

    bool result = isOdd_1(10);
    std::cout << "isOdd_1(10) return: " << result << "\n";

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

    //------------------------------------------------------------------------------

    // this will crash the app
    auto lambda_with_throw_1_deprecated = [=]() mutable throw() -> int {
        myAge++;
        throw 3;    // this will give a warning because we said there will be no throwing
        return myAge;
    };

    auto lambda_with_throw_2_deprecated = [=]() throw() -> int { // deprecated, don't use
        return myAge;
    };

    auto lambda_with_throw_2_DO_NOT_THROW = [=]() noexcept -> int { // use this instead
        return myAge;
    };

    auto lambda_with_throw_2_can_throw = [=]() -> int { // use this instead
        throw 3;
        return myAge;
    };

    // this will crash even in try catch
    // int ret_throw_1 = lambda_with_throw_1_deprecated();

    lambda_with_throw_2_DO_NOT_THROW();

    try{
        int ret_throw_1 = lambda_with_throw_2_can_throw();
        std::cout << "ret_throw_1 return: " << ret_throw_1 << "\n";
    }
    catch(int exception)
    {
        std::cout << "lambda_with_throw_2_can_throw throw: " << exception << "\n";
    }
    catch(...)
    {
        std::cout << "lambda_with_throw_2_can_throw throw something\n";
    }

    int ret_throw_2_deprecated = lambda_with_throw_2_deprecated();
    std::cout << "lambda_with_throw_2_deprecated return: " << ret_throw_2_deprecated << "\n";


    std::cout << "real age: " << myAge << "\n";
    std::cout << "End\n";

    return EXIT_SUCCESS;
}