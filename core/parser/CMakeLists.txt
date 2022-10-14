cmake_minimum_required(VERSION 3.20)

project(parser)

add_library(${PROJECT_NAME} SHARED
        package_parser.cpp
        package_version.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PRIVATE ../../)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})