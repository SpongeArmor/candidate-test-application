#include <iostream>
#include <unistd.h>
#include "drivers/TemperatureSensor/TemperatureSensor.hpp"

TemperatureSensor ts;

int main(int argc, char* argv[]) {
    std::cout << "Plexus Test #1" << std::endl;

    ts = TemperatureSensor();
    while(1)
    {
        double _temp = 0.00;
        ts.updateTemperature();
        ts.getTemperature(&_temp);

        std::cout << "Temperature: " << _temp << endl;
        sleep(1);
    }
    
    return 0;
}