cmake_minimum_required(VERSION 3.15)

# name of project
project(all VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

# set project to debug configuration
set(CMAKE_BUILD_TYPE Debug)

# add sub dirs
add_subdirectory(libraries)

# add main src
add_subdirectory(src)