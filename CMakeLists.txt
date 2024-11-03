# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MultithreadedTaskScheduler VERSION 1.0 LANGUAGES CXX)

# Set C++ standard to 11 or higher
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the executable
add_executable(MultithreadedTaskScheduler main.cpp Scheduler.cpp Task.cpp)

# Include headers
target_include_directories(MultithreadedTaskScheduler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Enable warnings (optional but recommended)
if (MSVC)
    target_compile_options(MultithreadedTaskScheduler PRIVATE /W4)
else()
    target_compile_options(MultithreadedTaskScheduler PRIVATE -Wall -Wextra -pedantic)
endif()
