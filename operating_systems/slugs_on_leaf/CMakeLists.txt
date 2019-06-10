cmake_minimum_required(VERSION 2.8)
project(slugs_on_leaf)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

file(GLOB_RECURSE OS_SOURCES
    "src/*.cpp")

add_executable(${PROJECT_NAME} ${OS_SOURCES})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})



#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

#file(GLOB_RECURSE TEST_SOURCES
#    "test/*.cpp")
#add_executable("${PROJECT_NAME}_test" ${TEST_SOURCES})
#target_link_libraries("${PROJECT_NAME}_test" ${GTEST_LIBRARIES} pthread)
