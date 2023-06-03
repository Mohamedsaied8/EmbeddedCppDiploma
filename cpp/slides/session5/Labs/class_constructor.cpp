#include <iostream>
#include <string>

// enum class is better that enum because it's type safe
enum class OEM : uint8_t    // the underlying type ": uint8_t" is optional, if not specified then it defaults to int
{
    Toyota = 0,     // the = 0 is optional
    Kia,
    Nissan,
    BMW,
    Mercedes
};

// don't forget the ; at the end
enum class Color
{
    RED,
    GREEN,
    WHITE,
    BLACK,
};

void add(int,int);
void add(int,int,int);
class Vehicle
{
    public:

    // constructor syntax:
    // 1. the name must match the class name
    // 2. there is no return type
    Vehicle()
    {
        std::cout << "no parameter constructor\n";

        m_customData = new int;
        *m_customData = 7;
    }

    Vehicle(const std::string& vin, const OEM manufacture, const Color color)
                : m_VIN(vin), m_OEM(manufacture), m_color(color)    // this is called initialization list
    {
        std::cout << "Constructor with parameters\n";
        m_customData = new int;
        *m_customData = 5;
    }

    std::string getVehicleData() const
    {
        std::string data;
        data = m_VIN + ", " + std::to_string(static_cast<int>(m_OEM)) + ", " + std::to_string(static_cast<int>(m_color))
                    + ", custom data: " + std::to_string(*m_customData);

        return data;
    } // const keyword means that this method won't change objects data

    // destructor syntax:
    // same as constructor but has ~ at the beginning
    ~Vehicle()
    {
        // this is RAII concept
        std::cout << "Destructor\n";
        delete m_customData;
    }

    private:
    std::string m_VIN = "00000000000000000";
    OEM m_OEM = OEM::BMW;
    Color m_color = Color::BLACK;
    int* m_customData;
};

// must be added (or use = default)


// Vehicle::Vehicle(const std::string& vin, const OEM manufacture, const Color color)
// {
//     m_VIN = vin;
//     m_OEM = manufacture;
//     m_color = color;
// }

//------------------------------------------------------

int main()
{

    Vehicle myCar_1;    // the constructor with no parameters
    std::cout << "myCar_1 data: " << myCar_1.getVehicleData() << "\n";


    myCar_1.getVehicleData();

    Vehicle myCar_2("123456789", OEM::Kia, Color::GREEN);   // the second constructor
    std::cout << "myCar_2 data: " << myCar_2.getVehicleData() << "\n";
}