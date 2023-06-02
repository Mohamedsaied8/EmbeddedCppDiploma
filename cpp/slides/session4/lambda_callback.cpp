#include <iostream>
#include <functional>
#include <thread>

void subscribeToSensorValue(std::function<void(bool)> callback_)
{
    std::cout << "Received the subscription callback\n";
    // say the sensor will be triggered after 3 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));
    callback_(true);
}

void callback_1(bool var)
{
    std::cout << "callback_1\n";
}

int main()
{
    bool sensorValue = 0;
    auto x = 10;

    // auto callback = [&](bool isSensorTriggered) -> void {
    std::function<void(bool)> callback;     // declaration
    callback = [&](bool isSensorTriggered) -> void {
        std::cout << "got a new sensor value: " << isSensorTriggered << "\n";
        sensorValue = isSensorTriggered;
    };

    std::cout << "current sensor value: " << sensorValue << "\n";
    std::cout << "subscribing to the sensor change values\n";
    // assuming that the sensorManger will trigger the sensor
    // std::thread th(subscribeToSensorValue, callback);
    std::thread th([&](){
        // subscribeToSensorValue(callback);
        subscribeToSensorValue(callback_1);
    });
    th.join();  // Wait for the thread to finish

    std::cout << "current sensorValue:" << sensorValue << "\n";
}