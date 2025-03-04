
# name of project
project(smartlogger VERSION 1.0 LANGUAGES CXX)

# add lib file
add_library(${PROJECT_NAME} STATIC smartlogger.cpp)

# target_link_libraries(${PROJECT_NAME} PRIVATE saferecorder)

# add include file
target_include_directories(${PROJECT_NAME} PRIVATE . ../saferecorder)   