cmake_minimum_required(VERSION 3.10)
project(BridgePattern)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Bridge_demo
    main.cpp
)

if(MSVC)
    target_compile_options(Bridge_demo PRIVATE /W4 /utf-8)
else()
    target_compile_options(Bridge_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()