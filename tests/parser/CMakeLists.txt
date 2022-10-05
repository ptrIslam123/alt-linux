cmake_minimum_required(VERSION 3.20)

project(test_parser)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} package_parser.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ../../)

target_link_libraries(${PROJECT_NAME} parser)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)