#include<iostream>
#include<vector>
#include<functional>
#include<cstdlib>

// Below Calculate functions takes a vector and 2 lambda functions in the argument list.
void Calculate (const std :: vector<int>& vec_num, const std::function<void (int)> &calculateS,
                                                   const std :: function< void (int) >& calculate_cube) {
     
     
     for (const auto& num : vec_num) {
          if (num % 2 == 0) {
              calculateS(num); 
          } else {
              calculate_cube (num); 
          }
     }   
}

int main() {

    // Seed the random function.
    srand(time(NULL));

    std :: vector<int> vec_num;

    int stepSize = 5;
    
    for (int i=0; i<10; i++) {
         vec_num.push_back(i); //rand() % 20
    }   
 
    /* []  - Capture list
       ()  - Parameter list
       -> return_type - return type
       {}  - Body of lambda function */
            
    auto lambda_square = [] (int num) -> void { std :: cout << "Number : " << num << " Square : " << num * num << std :: endl; };
    auto lambda_cube   = [] (int num) -> void { std :: cout << "Number : " << num << " Cube   : " << num * num * num << std :: endl; };
  
     Calculate (vec_num, lambda_square , lambda_cube);

    return 0;
}