#include "drivers/TemperatureSensor/TemperatureSensor.hpp"

#include <iostream>
#include <math.h>

using namespace std;

TemperatureSensor::TemperatureSensor() {

}

TemperatureSensor::~TemperatureSensor() {
}

ErrorCode TemperatureSensor::initializeSensor(void) {
    if(!_initialized) {
        // Perform any necessary initialization for the temperature sensor here
        cout << "TemperatureSensor initialized." << endl;
        _initialized = true;
    } else {
        cout << "TemperatureSensor already initialized." << endl;
    }
    
    return ErrorCode::OK;
}

/**
 * Retrieves the last stored temperature.
 * @param temperature Pointer to store the current temperature, <double>.
 * @return ErrorCode indicating success or failure.
 * @note Run updateTemperature() first to ensure the temperature is up-to-date.
 */
ErrorCode TemperatureSensor::getTemperature(double *temperature){
    if(!_initialized)
        return ErrorCode::OBJECT_NOT_INITIALIZED;
    else if(temperature == nullptr)
        return ErrorCode::NULLPTR_EXCEPTION;

    *temperature = this->_temp_instantaneous;
    
    return ErrorCode::OK;
}

/**
 * Updates the temperature by generating a new random value.
 * @return ErrorCode indicating success or failure.
 * @note This function should be called periodically to refresh the temperature data from the sensor.
 */
ErrorCode TemperatureSensor::updateTemperature(void){
    if(!_initialized)
        return ErrorCode::OBJECT_NOT_INITIALIZED;

    double _temp = 0.00;

    // Generate dummy daya/read actual sensor data
    // In this case, we will generate dummy data
    // This is a placeholder for actual sensor data retrieval logic
    ErrorCode _error = this->generateTemperatureData(&_temp);

    this->_temp_instantaneous = _temp; // Update the last known temperature within the object for later retrieval
    
    if(_error != ErrorCode::OK) {
        cout << "Error generating temperature data: " << static_cast<int>(_error) << endl;
        return _error;
    }

    return ErrorCode::OK;

}

/**
 * Generates a random temperature value within the specified range.
 * @param temperature Pointer to store the generated temperature value.
 * @return ErrorCode indicating success or failure.
 * @note This function simulates the behavior of a temperature sensor by generating a random value.
 */
ErrorCode TemperatureSensor::generateTemperatureData(double *temperature) {
    double _temp = 0.00;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(35.0, 45.0);
    _temp = dist(gen);

    if(_temp > _t_max || _temp < _t_min)
        return ErrorCode::INACCURATE_SENSOR_DATA;

    *temperature = std::roundf(_temp*100) / 100.0;  

    return ErrorCode::OK;
}