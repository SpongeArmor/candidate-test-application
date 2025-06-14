#include "drivers/MotorController/MotorController.hpp"

MotorController::MotorController() {
    if (!_initialized) {
        _motorRunning = 0;
        _initialized = true;
        std::cout << "MotorController initialized." << std::endl;
    } else {
        std::cout << "MotorController already initialized." << std::endl;
    }
}

MotorController::~MotorController() {
}

ErrorCode MotorController::initializeMotor(motor_config_t motorconfig){
    if(!_initialized)
    {
        return ErrorCode::OBJECT_NOT_INITIALIZED;
    }

    // Initialize motor here i.e. set up GPIO pins, PWM, etc.

    return ErrorCode::OK;
}

ErrorCode MotorController::setDirection(Direction direction) {
    if (!_initialized) {
        return ErrorCode::OBJECT_NOT_INITIALIZED;
    }

    _motorDirection = direction;

    // Set the motor direction here

    return ErrorCode::OK;
}

ErrorCode MotorController::setSpeed(std::int16_t speed) {
    if (!_initialized) {
        return ErrorCode::OBJECT_NOT_INITIALIZED;
    }

    if (speed < 0 || speed > _motorConfig.max_speed) {
        return ErrorCode::INACCURATE_SENSOR_DATA; // Assuming this is the closest error code
    }

#ifndef GENERATE_DUMMY_DATA
    _motorSpeed = speed;
#endif

    // Set the motor speed here using PWM

    return ErrorCode::OK;
}

ErrorCode MotorController::startMotor(std::int16_t speed, Direction direction){
    if (!_initialized) {
        return ErrorCode::OBJECT_NOT_INITIALIZED;
    }

    if (speed < 0 || speed > _motorConfig.max_speed) {
        return ErrorCode::INVALID_VALUE; // Assuming this is the closest error code
    }

    _motorSpeed = speed;
    _motorDirection = direction;
    
    // Start the motor here using PWM and set direction
    
    _motorRunning = true;

    return ErrorCode::OK;
}

/**
 * Retrieve the last updated motor speed from the object.
 * @return ErrorCode indicating success or failure.
 * @param Pointer to store the current speed, <std::int16_t>.
 */
ErrorCode MotorController::getSpeed(std::int16_t *speed) {
    if (!_initialized) {
        return ErrorCode::OBJECT_NOT_INITIALIZED;
    }

    *speed = this->_motorSpeed;

    return ErrorCode::OK;
}

ErrorCode MotorController::getDirection(Direction *direction) {
    if (!_initialized) {
        return ErrorCode::OBJECT_NOT_INITIALIZED;
    }

    *direction = this->_motorDirection;

    return ErrorCode::OK;
}

/**
 * Read motor speed and update the internal state.
 * @param None
 * @return ErrorCode indicating success or failure.
 * @note This function should be called periodically to refresh the motor speed data from the sensor. Assumed to produce value in revolutions per minute (RPM).
 */
ErrorCode MotorController::readMotorSpeed(void){
    if(!_initialized)
        return ErrorCode::OBJECT_NOT_INITIALIZED;

    motor_data_t _dummy_motor_data;

    // Generate dummy data/read actual sensor data
    // In this case, we will generate dummy data
    ErrorCode _error;

#ifdef GENERATE_DUMMY_DATA
    _error = generateMotorData(&_dummy_motor_data);  // to generate random data within a given rage
    this->_motorSpeed = _dummy_motor_data.speed;
#endif

    if(_error != ErrorCode::OK) {
        std::cout << "Error generating motor data: " << static_cast<int>(_error) << endl;
        return _error;
    }

    return ErrorCode::OK;
}

/**
 * Generates random motor data for testing purposes.
 * @param motorData Pointer to the motor_data_t structure to fill with data.
 * @return ErrorCode indicating success or failure.
 * @note This function simulates the behavior of a motor by generating random values.
 */
ErrorCode MotorController::generateMotorData(motor_data_t *motorData) {
    std::int16_t _speed = 0;
    float _current = 0.0;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> _dist_speed(_min_speed, _max_speed);
    std::uniform_real_distribution<> _dist_current(_min_current, _max_current);
    _speed = _dist_speed(gen);
    _current = _dist_current(gen);

    if(_speed > _max_speed || _speed < _min_speed)
        return ErrorCode::INACCURATE_SENSOR_DATA;

    motorData->speed = _speed;
    motorData->current = _current;
    motorData->status = _motorRunning ? 1 : 0;

    return ErrorCode::OK;
}