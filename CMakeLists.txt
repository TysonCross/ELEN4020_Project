cmake_minimum_required(VERSION 3.0)
project(main LANGUAGES CXX)

set(EXECUTABLE ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
set(CXX_COMPILER /usr/local/Cellar/mpich/3.3_1/bin/mpicc)
#set(C_COMPILER /usr/local/Cellar/mpich/3.3_1/bin/mpi)

#set (CMAKE_CXX_FLAGS "-v")
#set (CMAKE_CXX_FLAGS "-fopenmp")

set(SOURCE_test src/hello.cpp)

set(SOURCE_lab2 src/lab2.cpp
                src/Matrix.h
                src/transpose.cpp
                src/utilities.cpp)

set(SOURCE      src/main.cpp
                src/Matrix.h
                src/transpose.cpp
                src/utilities.cpp)

add_executable(${EXECUTABLE} ${SOURCE} )
add_executable(hello ${SOURCE_test})
add_executable(lab2 ${SOURCE_lab2})

find_package(MPI REQUIRED)
if (MPI_FOUND)
    include_directories(${MPI_C_INCLUDE_PATH})
    target_include_directories(${EXECUTABLE} PRIVATE ${MPI_CXX_INCLUDE_PATH})
    target_compile_options(${EXECUTABLE} PRIVATE ${MPI_CXX_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS})
    target_link_libraries(${EXECUTABLE} ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS} )
endif()

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


