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
        //alorithm
    }

};

struct MiniCoper : Strategy
{
    void calculateSpeed()
    {
        //alorithm
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
   Vehicle car1(&bmw);
   Vehicle car2(&mini);

    return 0;
}