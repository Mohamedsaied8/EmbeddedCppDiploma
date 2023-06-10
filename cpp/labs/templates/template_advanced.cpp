#include <iostream>
#include <type_traits>

// templates are the core of STL library
// template must be defined in the same header it was declared
// the compiler will use the function to generate new function according to what you used

// template<typename T>
template<class T1, class T2>
auto add(T1 num1, T2 num2) -> decltype(num1+num2)
{
    return num1 + num2;
}

// Calc<long> longCalc = Calc(13L , 10L);
template <typename T>
class Calc
{
    T m_num1;
    T m_num2;

    public:
    Calc(T num1, T num2) : m_num1(num1), m_num2(num2)
    {
    }

    void add()
    {
        std::cout << "t: " << typeid(decltype(m_num1+m_num2)).name() << "\n";
        std::cout << "Calc:: adding: " << m_num1+m_num2 << "\n";
    }

    void multi()
    {
        std::cout << "Calc:: multi: " << m_num1*m_num2 << "\n";
    }

    void div()
    {
        std::cout << "Calc:: div: " << m_num1/m_num2 << "\n";
    }
    void sub()
    {
        std::cout << "Calc:: sub: " << m_num1-m_num2 << "\n";
    }
};

int main()
{
    int num1 = 5;
    int num2 = -3;
    float num3 = 2.1;
    float num4 = -7.6;

    auto result1 = add(num1, num2); // OK --> will deduce the type form the input
    auto result2 = add(num1, num3); // OK --> will deduce the type form the input
    auto result3 = add(num3, num4); // OK --> will deduce the type form the input

    std::cout << "add int,int: " << result1 << "\n";
    std::cout << "add int,float: " << result2 << "\n";
    std::cout << "add float,float: " << result3 << "\n";

    // Calc longCalc = Calc(10,3);      // this will auto deduce type to int
    // Calc<long> longCalc = Calc(10, 3);   // this won't compile as default numbers are int not long
    Calc<long> longCalc = Calc(13L , 10L);
    // Calc longCalc = Calc(13 , 10);
    // std::vector<long> longCalc2;
    longCalc.add();
    longCalc.sub();
    longCalc.div();
    longCalc.multi();

}

