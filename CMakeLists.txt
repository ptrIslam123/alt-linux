cmake_minimum_required(VERSION 3.20)

project(package-checker)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)
add_subdirectory(external)
add_subdirectory(core)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    core
)
