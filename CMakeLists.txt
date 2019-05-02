cmake_minimum_required(VERSION 3.0)
project(project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")

 set(CMAKE_VERBOSE_MAKEFILE ON)
# set (CMAKE_CXX_FLAGS "-O0")
# set (CMAKE_CXX_FLAGS "-O3")
set (CMAKE_CXX_FLAGS "-Wno-unused-command-line-argument")

set(SOURCE  src/Matrix.h
            src/utilities.cpp
            src/transpose.cpp
            src/main.cpp)

set(EXECUTABLE ${PROJECT_NAME})

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} ")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(${EXECUTABLE} ${SOURCE})

