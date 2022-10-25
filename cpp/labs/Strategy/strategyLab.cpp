#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//Abstract Class
struct Strategy
{
    //Algorithm Interface
     virtual void calculateSpeed()=0;
};

struct BMW : Strategy
{
    void calculateSpeed()
    {
       cout << "BMW\n";
    }

};

struct MiniCoper : Strategy
{
    void calculateSpeed()
    {
        cout << "Mini Coper\n";
    }

};

//Context
struct Vehicle
{
   Vehicle(Strategy *_strategy) : strategy(_strategy)
    {

    }
   void vehicleSpeed()
   {
     strategy->calculateSpeed();
   }
    
    //Ptr to implementation : pimpl idiom 
    Strategy *strategy;  
};


int main()
{
   BMW bmw;
   MiniCoper mini;
   Vehicle E36(&bmw);
   Vehicle car2(&mini);

    car2.vehicleSpeed();

    return 0;
}