cmake_minimum_required(VERSION 3.20)
project(GA_implimentation VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-march=native -Wall -Wextra -Wpedantic)
endif()

# add_library(lib_GA STATIC src/GA.cpp)
# target_include_directories(lib_GA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(lib_GA_BIN STATIC src/GA_BIN_struct.cpp src/GA_BIN_func.cpp)
target_include_directories(lib_GA_BIN PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(lib_tools STATIC src/tools.cpp)
target_include_directories(lib_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add_executable(test_GA test/test_GA.cpp)
# target_link_libraries(test_GA PRIVATE lib_GA)

add_executable(test_GA_BIN test/test_GA_BIN.cpp)
target_link_libraries(test_GA_BIN PRIVATE lib_GA_BIN)


# add_executable(test_performance test/performance.cpp)
# target_link_libraries(test_performance PRIVATE lib_GA lib_tools)