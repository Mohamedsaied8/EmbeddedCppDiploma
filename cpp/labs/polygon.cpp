#include <iostream>
using namespace std;

// if you have virtual keyword then dynamic dispatch, from type on the right
// if we don't have virtual then static dispatch, from type on the right
class Polygon { //base
    public:
    // virtual void show() = 0 ; // this is called a pure virtual function, meaning that someone should implement it, you can't creat an instance of this class
    virtual void show() {
        cout<<"Its a polygon"<<endl;
    }

    void whoAmI()
    {
        cout << "I'm Polygon" << "\n";
    }
};

class Triangle : public Polygon {
    public:
    void show() override // it's much better to add override keyword
    {
        // Polygon::show();
        cout<<"Triangle is 3 sided polygon"<<endl;
    }

    void whoAmI()
    {
        cout << "I'm Triangle" << "\n";
    }
};
class Rectangle : public Polygon {
    public:
    void show() // but you're not required to add override keyword, C++ already knows it's virtual
    {
        cout<<"Rectangle is 4 sided polygon"<<endl;
    }

    void whoAmI()
    {
        cout << "I'm Rectangle" << "\n";
    }
};
void printInfo(Polygon&);

int main() {
    Polygon *p; //pointer to the base class

    Triangle t; //vptr will be created vptr -> vtable -> Triangle ..

    p = &t; //points to triangle object [vptr is obtained]

    p->show();//vtable is accessed to obtain address of show in the triangle object
    p->whoAmI();

    // t.show();
    // t.whoAmI();
    // cout << "---------------------\n";
    // printInfo(t);


    Rectangle r;

    p = &r;
    p->show();
    p->whoAmI();
    // printInfo(r);
    return 0;
}

void printInfo(Polygon& obj)
{
    obj.show();
    obj.whoAmI();
}