#include <string>
#include <iostream>

/*

Access      Same Class        Child       Outside

Public        true            true         true

Protected     true             true         False

Private        true            False        False

*/

class Vehicle
{
    private:    // those can't be changed by child classes
    std::string m_VIN;
    std::string m_color;
    int m_wheelsNumer;

    protected:
    int m_distance = 0;     // this can be changed by child classes
    std::string m_name;

    public:
        Vehicle(std::string vin, std::string color, int wheelsNumer, std::string name)
                                : m_VIN(vin), m_color(color), m_wheelsNumer(wheelsNumer), m_name(name)
        {
            std::cout << "Vehicle Constructor\n";
        }

        void printVehicleInfo(){
            std::cout << "vehicle VIN: " << m_VIN
                        << ", color: " << m_color
                        << ", name: " << m_name
                        << ", traveled distance: " << m_distance
                        << ", number of wheels: " << m_wheelsNumer << "\n";
        }

        void move(int distance_km)
        {
            m_distance += distance_km;
            std::cout << "car is moving, current traveled distance: " << m_distance << "Km\n";
        }
};

class Car : public Vehicle
{
    private:
    bool m_ACState = false;

    public:
    Car(std::string vin, std::string color)
            : Vehicle(vin, color, 4, "car")
    {
        std::cout << "Car Constructor\n";
    }

    void switchAC(bool state)
    {
        std::cout << "switching AC state to: " << state << "\n";
        m_ACState = state;
    }
};

class Motorcycle : public Vehicle
{
    private:
    bool m_balanced = true;

    void setBalance(bool state)
    {
        m_balanced = state;
    }

    public:
    Motorcycle(std::string vin, std::string color)
            : Vehicle(vin, color, 2, "motorcycle")
    {
        std::cout << "Motorcycle Constructor\n";
    }

    bool isMotorcycleBalanced()
    {
        return m_balanced;
    }

    void printMotorcycleInfo()
    {
        printVehicleInfo();
        std::cout << "balanced state: " << m_balanced << "\n";
    }
};

int main()
{
    Vehicle myVehicle = Vehicle("000000000000000", "Black", 3, "Toktok");
    myVehicle.move(10);
    myVehicle.printVehicleInfo();

    std::cout << "--------------------------------------------\n";

    Car myCar{"000000000000001", "Red"};
    myCar.move(15);
    myCar.switchAC(true);
    myCar.printVehicleInfo();

    std::cout << "--------------------------------------------\n";

    Motorcycle myMotorcycle("000000000000002", "White");
    myMotorcycle.move(7);
    bool balance_state = myMotorcycle.isMotorcycleBalanced();
    // myMotorcycle.printVehicleInfo();
    myMotorcycle.printMotorcycleInfo();
}