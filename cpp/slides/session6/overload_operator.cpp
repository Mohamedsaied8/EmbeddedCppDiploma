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

    // complex operator+ (int &obj) ;
    complex operator+ (complex& araby) {
        complex result;
        result.real = this->real + araby.real;
        result.imag = this->imag + araby.imag;
        return result;
    }

    //
    complex operator+ (int num) {
        complex result;
        result.real = this->real + num;
        result.imag = this->imag + 0;
        return result;
    }

    void display() {
    cout<<real<<" + i"<<imag<<endl;
    }
};


int main() {
    complex c1(12.4, 6), c2(7.9, 8);
    // complex c3 = c1 + c2;
    complex c3 = c1.operator+(c2);
    c3.display();

    int num = 3;
    // complex c4 = c1.operator+(3);
    complex c4 = c1.operator+(num);
    c4.display();

    // complex c5 = c1 + 3;
    complex c5 = c1 + num;
    c5.display();

    return 0;
}