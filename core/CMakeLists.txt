cmake_minimum_required(VERSION 3.20)

project(core)

add_subdirectory(net)
add_subdirectory(parser)

add_library(${PROJECT_NAME} SHARED utils.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    parser
    net
)