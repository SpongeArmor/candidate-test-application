#include <iostream>
#include <unistd.h>
#include "drivers/TemperatureSensor/TemperatureSensor.hpp"
#include "drivers/MotorController/MotorController.hpp"

TemperatureSensor ts;
MotorController mc;

int main(int argc, char* argv[]) {
    std::cout << "Plexus Test #1" << std::endl;

    ts = TemperatureSensor();
    
    mc.setSpeed(200); // Set a fixed speed for testing

    while(1)
    {
        double _temp = 0.00;
        ts.updateTemperature();
        ts.getTemperature(&_temp);

        std::int16_t _motorSpeed = 0;
        mc.readMotorSpeed();
        mc.getSpeed(&_motorSpeed);

        std::cout << "Temperature: " << _temp << endl;
        std::cout << "Motor Speed: " << _motorSpeed << " RPM" << std::endl;
        std::cout << endl;
        sleep(1);
    }
    
    return 0;
}