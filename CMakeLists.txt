cmake_minimum_required(VERSION 3.12)
project(DroneSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add this line to include the 'include' directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(drone_system_test
    src/main.cpp
)