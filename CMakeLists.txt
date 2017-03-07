project(tapetenwechsel)
cmake_minimum_required( VERSION 2.6 )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-long-long -pedantic" )

file( GLOB SRCS src/*.cpp src/*.hh )

add_executable( ${PROJECT_NAME} ${SRCS} )

target_link_libraries(${PROJECT_NAME} yaml-cpp)
