cmake_minimum_required(VERSION 3.20)
project(GA_implimentation VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Debug/Release/RelWithDebInfo/MinSizeRel)" FORCE)
    message(STATUS "No build type selected, default to ${CMAKE_BUILD_TYPE}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-march=native -Wall -Wextra -Wpedantic)
endif()

add_library(lib_GA_BIN STATIC src/GA_BIN.cpp src/GA_BIN_wrapper.cpp)
target_include_directories(lib_GA_BIN PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Current mode: Debug. Will compile test executables.")
    
    add_executable(test_GA_BIN test/test_GA_BIN.cpp)
    target_link_libraries(test_GA_BIN PRIVATE lib_GA_BIN)

    add_executable(test_performance test/performance.cpp)
    target_include_directories(test_performance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(test_performance PRIVATE lib_GA_BIN)
else()
    message(STATUS "Not in Debug mode, will skip compilation of test executables.")
endif()

add_executable(Schwefel Schwefel.cpp)
target_link_libraries(Schwefel PRIVATE lib_GA_BIN)

add_executable(Rastrigin Rastrigin.cpp)
target_link_libraries(Rastrigin PRIVATE lib_GA_BIN)