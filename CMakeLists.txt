cmake_minimum_required(VERSION 3.10.0)
project(DesignPatterns VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(02_Flyweight)
add_subdirectory(01_Singleton)
add_subdirectory(03_observer)
