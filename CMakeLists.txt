cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# set project name and version
project (main)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the source directories
add_subdirectory(src/Convert)
add_subdirectory(src/Utils)

# Define the executable target
add_executable(${PROJECT_NAME} src/main.cpp)

# Link the executable with the source libraries
target_link_libraries(${PROJECT_NAME} Convert Utils)
