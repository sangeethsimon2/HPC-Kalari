cmake_minimum_required(VERSION 3.23)

project(
    HeatKernelND
    VERSION 0.1
    LANGUAGES CXX
    )

#Set CXX version and make it required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/app")

add_executable( HeatKernelND )
target_include_directories(HeatKernelND PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_sources(HeatKernelND PRIVATE
               src/main.cpp
               src/parameterObject.cpp
               src/structuredGrid.cpp
               #src/allocateMemory.cpp
               #src/deAllocateMemory.cpp
               #src/initialize.cpp
               #src/update.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Enabling -O3 optimization flag")
    add_compile_options(-O3 -funroll-loops -march=skylake-avx512)
endif()