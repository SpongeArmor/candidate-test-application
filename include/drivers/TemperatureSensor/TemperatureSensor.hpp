#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>

#include "errors.h"

using namespace std;

constexpr double _t_min = 35.0;
constexpr double _t_max = 45.0;

class TemperatureSensor {
    public:
        bool _initialized = false;
        double _temp_instantaneous = 0.0;

        TemperatureSensor();
        ~TemperatureSensor();
        ErrorCode getTemperature(double *temperature);
        ErrorCode updateTemperature(void);
    private:
        ErrorCode generateTemperatureData(double *temperature);
};

#endif