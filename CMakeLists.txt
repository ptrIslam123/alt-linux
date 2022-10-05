cmake_minimum_required(VERSION 3.20)

project(package-checker)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)
add_subdirectory(external/json)
add_subdirectory(core/parser)
add_subdirectory(core/net)
add_subdirectory(core/filter)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    nlohmann_json::nlohmann_json
    parser
    net
    curl
    package_filter
)
