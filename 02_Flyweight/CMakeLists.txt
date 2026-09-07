cmake_minimum_required(VERSION 3.10)
project(FlyweightPatternDemo)

# 显式指定 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 根据不同的编译器设置对应的警告级别
if(MSVC)
    # MSVC 编译器的警告选项 (/W4 相当于开启大部分合理警告)
    add_compile_options(/W4)
else()
    # GCC 或 Clang 编译器的警告选项
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 添加可执行文件
add_executable(flyweight_demo main.cpp)