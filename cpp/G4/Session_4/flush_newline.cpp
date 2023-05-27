/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <unistd.h>
#include <thread>

using namespace std;

// source: https://stackoverflow.com/a/38112106/6184259
int main() {

    cout << "Line 1..." << endl; // flush will force a print(endl is -> "\n" << flush)
    cout << "Line x` \n";    // no flush so the print will be delayed till buffer is full
    std::this_thread::sleep_for(2s);
    cout << "a\n";    // no flush so the print will be delayed till buffer is full

    std::this_thread::sleep_for(3s);
    cout << "Line 2" << "\n" << std::flush;   // will be printed immediatly since we're using std flush(std::endl)

    cout << "Line 3" << endl ;

    return 0;
}

