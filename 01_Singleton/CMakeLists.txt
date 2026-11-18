cmake_minimum_required(VERSION 3.15)
project(02_Singleton)

# 显式指定 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 针对 MSVC 编译器的特定设置：确保中文输出不乱码，并忽略一些安全警告
if(MSVC)
    add_compile_options(/utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# 生成可执行文件
add_executable(SingletonDemo main.cpp)
