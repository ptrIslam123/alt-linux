cmake_minimum_required(VERSION 3.20)

project(filter)

add_library(package_filter INTERFACE package_filter.h)

add_library(package_version package_version.cpp)

target_link_libraries(package_filter INTERFACE parser)

target_include_directories(package_filter INTERFACE ../../)
target_include_directories(package_filter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(package_version PUBLIC ../../)
target_include_directories(package_version PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})