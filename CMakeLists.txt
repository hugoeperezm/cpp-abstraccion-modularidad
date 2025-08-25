cmake_minimum_required(VERSION 3.20)
project(cpp_abstraccion_modularidad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(app_lib
    src/analytics.cpp
    src/inventory.cpp
    src/pricing.cpp
    src/utils.cpp
)
target_include_directories(app_lib PUBLIC include)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE app_lib)

# Salida limpia
set_target_properties(app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
