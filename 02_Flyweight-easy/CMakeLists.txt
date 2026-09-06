cmake_minimum_required(VERSION 3.15)
project(02_Flyweight)
if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>" "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    # 或者简单直接写：
    # add_compile_options(/utf-8)
endif()
add_executable(Flyweight main.cpp
    CharacterGlyph.h
    GlyphFactory.h
    TextDocument.h)
