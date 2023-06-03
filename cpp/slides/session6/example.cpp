#include <iostream>
using namespace std;

class base {
public:
    virtual void display() {
        cout<<"Function of base class"<<endl;
    }
};

class derived : public base {
public:
    void display() {
        cout<<"Function of derived class"<<endl;
    }
};

int main() {

    base b1 = base();
    b1.display();

    base d0 = derived();
    d0.display();

    derived d1;
    d1.display();

    return 0;
}