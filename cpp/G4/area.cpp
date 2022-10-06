// compute circle area
//1) Get the raduis
//2) Compute area with formula area = r * r * PI
//3) Display Area
#include <iostream>
typedef double CircleRadius;
typedef double CircleArea;

int main()
{
    constexpr double PI = 3.14;
    CircleRadius circleRadius;
    
    std::cout << "Please Enter Circle Radius" << std::endl;
    std::cin >> circleRadius;
    
    CircleArea area = circleRadius * circleRadius * PI;
    std::cout << "Area is " << area << std::endl;

    return 0;
}