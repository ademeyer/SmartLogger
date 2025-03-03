# set project name, version and language
project(app VERSION 1.0 LANGUAGES CXX)

# add cpp project files
add_executable(${PROJECT_NAME} main.cpp)

# link user libs
target_link_libraries(${PROJECT_NAME} PRIVATE smartlogger saferecorder)

# add smartlogger, saferecorder include file path
target_include_directories(${PROJECT_NAME} PRIVATE ../libraries/smartlogger
                                                    ../libraries/saferecorder)
