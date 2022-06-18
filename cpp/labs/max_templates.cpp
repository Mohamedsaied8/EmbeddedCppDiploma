#include <iostream>
using namespace std ;
 
    //max returns the maximum of the two elements
    template <class D>
    D maxT(D a, D b)
    {
        return a > b ? a : b ;
    }

 

int main()
{
   float x = 10.0;
   float y = 15.9;
	cout << "max(10, 15) = " << maxT(x, y) << endl ;
	cout << "max('k', 's') = " << maxT('k', 's') << endl ;
	cout << "max(10.1, 15.2) = " << maxT(10.1, 15.2) << endl ;
    return 0;
}