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
 
int main(){
 
   std::unique_ptr<Rectangle> P1(new Rectangle(10, 5));
   std::unique_ptr<Rectangle> P2 = std::make_unique<Rectangle>();
    //make_unique
    std::cout << P1->area() << std::endl; // This'll print 50
 
   // unique_ptr<Rectangle> P2(P1); //ERROR
   
    std::unique_ptr<Rectangle> P2;
    P2 = std::move(P1);
 
    // This'll print 50
    std::cout << P2->area() << std::endl;
 
    // cout<<P1->area()<<endl;
    return 0;
}