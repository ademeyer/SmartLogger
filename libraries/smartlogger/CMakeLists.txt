
# name of project
project(smartlogger VERSION 1.0 LANGUAGES CXX)

# add lib file
add_library(smartlogger STATIC smartlogger.cpp)

# add include file
target_include_directories(smartlogger PRIVATE .)