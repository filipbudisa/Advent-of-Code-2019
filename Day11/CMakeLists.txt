cmake_minimum_required(VERSION 3.15)
project(Day11)

set(CMAKE_CXX_STANDARD 17)

add_executable(Day11 src/main.cpp src/Computer.cpp src/IComputerListener.h src/Robot.cpp src/Robot.h)