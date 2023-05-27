#include <iostream>

//New data-type
//تجمعيه داتا
struct Fruit{

    double weight;
    double price;
    std::string name;

};

// - + 1 2 3 4
int var;

void Buy(Fruit *fruit)
{
    //calculate total amount and price
    std::cout << fruit->name <<" " << fruit->price <<" "<< fruit->weight << std::endl;

}

void Buy(Fruit& fruit)
{
    //calculate total amount and price
    std::cout << fruit.name <<" " << fruit.price <<" "<< fruit.weight << std::endl;

}

// struct Fruit{
//     double weight;
//     double price;
//     std::string name;
// };
int main()
{
    Fruit orange; 
    orange.name = "Orange";
    orange.price = 7.20;
    orange.weight = 2.0;
    Buy(orange);

    Fruit banana; 
    banana.name = "Banana";
    banana.price = 5.20;
    banana.weight = 3.0;    
    Buy(&banana);

    return 0;
}