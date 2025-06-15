#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "drivers/TemperatureSensor/TemperatureSensor.hpp"
#include "drivers/MotorController/MotorController.hpp"

#define DEBUG

TemperatureSensor ts = TemperatureSensor();
MotorController mc = MotorController();

static int motorRPM = 0;
static double temperature = 0.0;

std::mutex mutex_motorRPM;
std::mutex mutex_temperature;

void motorControllerRPMReaderThread(int& motorRPM, std::mutex& mtx_motorRPM){
    // std::cout << __func__ << "started." << std::endl;
    motor_config_t motorConfig = {
        12, // Example PWM pin
        1,  // Example direction pin
        3,  // Example enable pin
        MOTOR_MAX_SPEED // Maximum speed in RPM
    };

    ErrorCode error = mc.initializeMotor(motorConfig);
    mc.setSpeed(1500);
    if(error != ErrorCode::OK) {
        std::cerr << "Failed to initialize MotorController: " << static_cast<int>(error) << std::endl;
        return;
    }

    while(true){
        
        std:int16_t _motorSpeed = 0;
        mc.readMotorSpeed();
        mc.getSpeed(&_motorSpeed);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate some delay for reading speed
        std::unique_lock<std::mutex> lock(mtx_motorRPM);
        motorRPM = _motorSpeed; // Update motor RPM
        lock.unlock();
        // std::cout << "\tAcquired MotorController Data." << std::endl;
    }
}

void temperatureSensorReaderThread(double& temperature, std::mutex& mtx_temperature){
    // std::cout << __func__ << "started." << std::endl;
    ErrorCode error = ts.initializeSensor();

    if(error != ErrorCode::OK) {
        std::cerr << "Failed to initialize TemperatureSensor: " << static_cast<int>(error) << std::endl;
        return;
    }

    double temp = 0.0;

    while(true){
        ts.updateTemperature();
        ts.getTemperature(&temp);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate some delay for reading temperature
        std::unique_lock<std::mutex> lock(mtx_temperature);
        temperature = temp; // Update temperature
        lock.unlock();
    }
}

int main(int argc, char* argv[]) {
    // std::cout << "Plexus Test #1" << std::endl;

    // cout << "Starting MotorController thread.." << endl;
    std::thread motorController(motorControllerRPMReaderThread, std::ref(motorRPM), std::ref(mutex_motorRPM));

    // cout << "Starting TemperatureSensor thread.." << endl;
    std::thread temperatureReader(temperatureSensorReaderThread, std::ref(temperature), std::ref(mutex_temperature));

    int motorRPM_mt = 0;
    double temperature_mt = 0.0;
    while(true){
        {
            std::time_t now = std::time(nullptr);
            
            std::unique_lock<std::mutex> lock_temperature(mutex_temperature);
            temperature_mt = temperature; // Copy temperature value
            lock_temperature.unlock();
            
            std::unique_lock<std::mutex> lock_motorRPM(mutex_motorRPM);
            lock_motorRPM.unlock();
            
            motorRPM_mt = motorRPM; // Copy motor RPM
            temperature_mt = temperature; // Copy temperature value

            char timeString[std::size("HH:MM:SS")];
            std::strftime(std::data(timeString), std::size(timeString), "%T", std::gmtime(&now));
            std::cout  << "\r[Time: " << timeString << "] " "Temperature:  " << temperature_mt << "°C" << " | " << "Motor Speed: " << motorRPM_mt << " RPM" << std::flush;

        }
            
        /*
            // Can be used to set the RPM manually, make sure GENERATE_DUMMY_DATA is commented out in MotorController.hpp
            {
                int newRPM = 2000;
                std::unique_lock<std::mutex> lock(mtx_motorRPM);
                cout << "Updating motor speed to " << newRPM << "RPM" << endl;
                mc.setSpeed(newRPM); // Update motor speed to 2000 RPM
                lock.unlock();   
            } 
        */
        
    
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate some delay for processing
    }
    
    return 0;
}