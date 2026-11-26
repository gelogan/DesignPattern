cmake_minimum_required(VERSION 3.10)
project(CompositePattern)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(CompositeMethod_demo
    main.cpp
)

if(MSVC)
    target_compile_options(CompositeMethod_demo PRIVATE /W4 /utf-8)
else()
    target_compile_options(CompositeMethod_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()