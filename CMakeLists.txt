cmake_minimum_required(VERSION 3.10)

project(plexus_mini_assignment)
set(CMAKE_CXX_STANDARD 20)

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp
    src/drivers/TemperatureSensor/TemperatureSensor.cpp
)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    
)