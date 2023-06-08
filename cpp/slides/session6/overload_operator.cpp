#include <iostream>
using namespace std;

class complex {
private:
    float real, imag;
public:
    complex(float r=0, float i=0){
        real = r;
        imag = i;
    }

    complex operator+ (complex const &obj) {
        complex result;
        result.real = real + obj.real;
        result.imag = imag + obj.imag;
        return result;
    }

    void display() {
    cout<<real<<"+i"<<imag<<endl;
    }
};


int main() {
    complex c1(12.4, 6), c2(7.9, 8);
    complex c3 = c1 + c2;
    c3.display();
    return 0;
}