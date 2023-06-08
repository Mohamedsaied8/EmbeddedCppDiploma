#include <iostream>
#include <memory>
 
class Rectangle {
    int length;
    int breadth;
 
public:
    Rectangle(int l, int b){
        length = l;
        breadth = b;
    }
 
    int area(){
        return length * breadth;
    }
};

class Calculator
{
    public:
    Calculator(std::shared_ptr<Rectangle> ptr) : m_rectanglePtr(ptr)
    {
    }

    int getArea()
    {
        // check if pointer is valid
        if(m_rectanglePtr.get() != nullptr)
        {
            return m_rectanglePtr->area();
        }
        else
        {
            std::cout << "Pointer is Null\n";
            return 0;
        }
    }

    private:
    std::shared_ptr<Rectangle> m_rectanglePtr;
};

int main(){

    // std::unique_ptr<Rectangle> P1(new Rectangle(10, 5));
    //std::unique_ptr<int> intPTR(new int[10]);
    auto P1 = std::make_unique<Rectangle>(10,5);
    //make_unique
    std::cout << P1->area() << std::endl; // This'll print 50

    std::shared_ptr<Rectangle> P2;
    P2 = std::make_shared<Rectangle>(10,10);
    auto calc = Calculator(P2);
    std::cout << "calc.getArea(): " << calc.getArea() << "\n";

    std::cout << "number of objects havening a reference to P2: " << P2.use_count() << "\n";

    // This'll print 100
    std::cout << P2->area() << std::endl;
    return 0;
}