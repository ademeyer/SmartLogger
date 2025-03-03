project(saferecorder VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC saferecorder.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE .)