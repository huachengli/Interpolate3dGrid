cmake_minimum_required(VERSION 3.19)
project(Interpolate3dGrid)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(src)

add_executable(Interpolate3dGrid
        src/Divide.cpp
        src/Divide.h
        src/Form.h
        src/GridIO.cpp
        src/GridIO.h
        src/Interpolate.cpp
        src/Interpolate.h
        src/main.cpp)
