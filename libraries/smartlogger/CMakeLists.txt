
# name of project
project(smartlogger VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

# add lib file
add_library(${PROJECT_NAME} STATIC smartlogger.cpp)

# target_link_libraries(${PROJECT_NAME} PRIVATE saferecorder)

# add include file
target_include_directories(${PROJECT_NAME} PRIVATE . ../saferecorder)   