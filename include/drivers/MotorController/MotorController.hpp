#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP
#include "errors.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <random>

#define MOTOR_MAX_SPEED 3000 // Maximum speed in RPM
#define GENERATE_DUMMY_DATA // uncomment to be able to set the motor speed manually for testing purposes

constexpr std::int16_t _min_speed = 450; // Minimum temperature in Celsius for randim value generation
constexpr std::int16_t _max_speed = 550; // Maximum temperature in Celsius for random value generation
constexpr float _min_current = 1.1; 
constexpr float _max_current = 1.3;
static_assert(_max_speed > _min_speed, "Invalid reference temprature range provided, please check again.");

typedef struct {
    std::uint8_t pin_pwm;        // PWM pin for motor control
    std::uint8_t pin_direction;  // Direction control pin
    std::uint8_t pin_enable;     // Enable pin for the motor
    std::uint16_t max_speed;     // Maximum speed in RPM
} motor_config_t;


enum Direction {
    FORWARD,
    REVERSE
};

typedef struct {
    std::int16_t speed;          // Current speed of the motor in RPM
    float current;               // Current drawn by the motor in Amperes
    std::uint8_t status;         // Status of the motor (e.g., running, stopped)
} motor_data_t;

using namespace std;

class MotorController {
    private:
        bool _initialized = false;
        bool _motorRunning = false;
        Direction _motorDirection = Direction::FORWARD;
        std::int16_t _motorSpeed = 0; // Current speed of the motor in RPM
        motor_config_t _motorConfig = {0, 0, 0, MOTOR_MAX_SPEED}; // Default motor configuration
        
        ErrorCode generateMotorData(motor_data_t *motorData);
        
        public:
        MotorController();
        ~MotorController();
        
        ErrorCode initializeMotor(motor_config_t motorconfig);
        
        ErrorCode startMotor(std::int16_t speed, Direction direction = Direction::FORWARD);
        ErrorCode setSpeed(std::int16_t speed);
        ErrorCode readMotorSpeed(void);
        ErrorCode getSpeed(std::int16_t *speed);
        ErrorCode setDirection(Direction direction);
        ErrorCode getDirection(Direction *direction);
        ErrorCode stopMotor(void);
        
};

#endif // MOTOR_CONTROLLER_HPP
