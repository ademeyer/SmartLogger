# set project name, version and language
project(app VERSION 1.0 LANGUAGES CXX)

# set project version to C++ 20
set(CMAKE_CXX_STANDARD 20)

# add cpp project files
add_executable(${PROJECT_NAME} main.cpp)

# set list of user static libs
set(STATIC_LIBS smartlogger saferecorder)

# link user libs
target_link_libraries(${PROJECT_NAME} PRIVATE ${STATIC_LIBS})

# add smartlogger, saferecorder include file path
target_include_directories(${PROJECT_NAME} PRIVATE ../libraries/smartlogger
                                                    ../libraries/saferecorder)
