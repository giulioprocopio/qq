cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(qq)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)  # GoogleTest requires at least C++14.

option(BUILD_SHARED_LIBS "Build libraries as SHARED" FALSE)

add_library(qq)

# Update with `ls -1 src/*.c`.
target_sources(qq
    PRIVATE
        src/out.c
        src/verbose.c
)

target_include_directories(qq
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
    include/qq.h
)
set_target_properties(qq PROPERTIES PUBLIC_HEADER "${public_headers}")