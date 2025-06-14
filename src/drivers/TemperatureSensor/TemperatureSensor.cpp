#include "drivers/TemperatureSensor/TemperatureSensor.hpp"

#include <iostream>
#include <math.h>

using namespace std;

TemperatureSensor::TemperatureSensor() {
    if(!_initialized) {
        time_t _currentTime = std::time(nullptr);
        std::srand(_currentTime);
        _initialized = true;
        cout << "TemperatureSensor initialized." << endl;
    } else {
        cout << "TemperatureSensor already initialized." << endl;
    }
}

TemperatureSensor::~TemperatureSensor() {
}

ErrorCode TemperatureSensor::getTemperature(double *temperature){
    if(!_initialized)
        return ErrorCode::OBJECT_NOT_INITIALIZED;
    else if(temperature == nullptr)
        return ErrorCode::NULLPTR_EXCEPTION;

    *temperature = this->_temp_instantaneous;
    
    return ErrorCode::OK;
}

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

ErrorCode TemperatureSensor::generateTemperatureData(double *temperature) {
    static_assert(_t_max > _t_min, "Invalid reference temprature range provided, please check again.");

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