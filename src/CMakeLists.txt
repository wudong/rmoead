project(rmoead)

cmake_minimum_required(VERSION 2.8)

set (rmoead_VERSION_MAJOR 1)
set (rmoead_VERSION_MINOR 0)

set (CMAKE_BUILD_TYPE Debug)

file(GLOB RMOEAD_SOURCES *.cpp)

add_executable(rmoead ${RMOEAD_SOURCES})

target_link_libraries(rmoead gsl blas confuse)





