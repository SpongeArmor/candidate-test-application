/**
 * TemperatureSensor driver to read/simulate temperature data.
 */
#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>

#include "errors.hpp"

using namespace std;

constexpr double _t_min = 35.0; // Minimum temperature in Celsius for randim value generation
constexpr double _t_max = 45.0; // Maximum temperature in Celsius for random value generation
static_assert(_t_max > _t_min, "Invalid reference temprature range provided, please check again.");

class TemperatureSensor {
    public:
        bool _initialized = false;
        double _temp_instantaneous = 0.0;

        TemperatureSensor();
        ~TemperatureSensor();
        ErrorCode initializeSensor(void);
        ErrorCode getTemperature(double *temperature);
        ErrorCode updateTemperature(void);
    
        private:
        ErrorCode generateTemperatureData(double *temperature);
};

#endif