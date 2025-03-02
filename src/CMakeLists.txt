# set project name, version and language
project(app VERSION 1.0 LANGUAGES CXX)

# add cpp project files
add_executable(${PROJECT_NAME} main.cpp)

# link smartlogger lib
target_link_libraries(${PROJECT_NAME} PRIVATE smartlogger)

# add smartlogger include file
target_include_directories(${PROJECT_NAME} PRIVATE ../libraries/smartlogger)