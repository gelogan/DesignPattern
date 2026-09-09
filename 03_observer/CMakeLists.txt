cmake_minimum_required(VERSION 3.10)
project(ObserverPatternTest)

# 要求使用 C++11 标准，以兼容代码结构
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>" "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()
# 将源文件编译为可执行程序
add_executable(ObserverPatternTest main.cpp)