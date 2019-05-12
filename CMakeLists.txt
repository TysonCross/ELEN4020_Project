cmake_minimum_required(VERSION 3.0)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
set(CXX_COMPILER /usr/local/Cellar/mpich/3.3_1/bin/mpicc)
set(C_COMPILER /usr/local/Cellar/mpich/3.3_1/bin/mpi)


set (CMAKE_CXX_FLAGS "-v")
set (CMAKE_CXX_FLAGS "-fopenmp")


#set(INCLUDE src/Matrix.h)
#
#set(SOURCE  src/utilities.cpp
#            src/transpose.cpp
#            src/main.cpp)

set(SOURCE_test  src/test_mpi.cpp)

set(EXECUTABLE ${PROJECT_NAME})
#add_executable(${EXECUTABLE} ${INCLUDE} ${SOURCE} )
add_executable(${EXECUTABLE} ${SOURCE_test})

find_package(MPI REQUIRED)
    include_directories(${MPI_C_INCLUDE_PATH})
    target_include_directories(${EXECUTABLE} PRIVATE ${MPI_CXX_INCLUDE_PATH} ${INCLUDE})
    target_compile_options(${EXECUTABLE} PRIVATE ${MPI_CXX_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS})
    target_link_libraries(${EXECUTABLE} ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS} )
#    target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})

#find_package(OpenMP REQUIRED)
#if (OPENMP_FOUND)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif()


