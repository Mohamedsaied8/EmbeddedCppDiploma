#include <iostream>
using namespace std;

// int calc();
auto calc(int, int) -> int;
int divide(int x, int y);

int main() {

  int num1;
  int num2;
  cout<<"Enter Number1: ";
  cin>>num1;
  cout<<"Enter Number2: ";
  cin>>num2;

// num1 = 10
  calc(num1 , num2);
  float Sum = calc(num1,num2);
  auto Div = divide(num1,num2);
  cout << "Sum=  " << Sum  <<endl;
  cout << "Div=  " << Div  <<endl;
    return 0;
}

int calc(int x, int y)
{
    int sum=x+y;
    return sum;
}

int divide(int x, int y)
{
    int divi=x/y;
    return divi;
}