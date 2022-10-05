cmake_minimum_required(VERSION 3.20)

project(net)

add_library(${PROJECT_NAME} http_request.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC curl)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})