cmake_minimum_required(VERSION 3.14)
project(Socket_Chat)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(SOURCE ./src/)
set(INCLUDE ./include/)

include_directories(
        ${SOURCE}
        ${INCLUDE})

link_directories(
        ${SOURCE}
        ${INCLUDE})

file(GLOB all
        "${INCLUDE}*.hpp"
        "${SOURCE}*.cpp")

add_executable(${PROJECT_NAME} ${all})

target_link_libraries(${PROJECT_NAME})