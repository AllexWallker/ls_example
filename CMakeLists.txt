cmake_minimum_required(VERSION 3.6)

project(ls_example)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_INCLUDE_PATH include) 
set (PROJECT ls_example)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB COMMON_SRC src/*.cpp)
set (SOURCE ${COMMON_SRC})

add_executable(${PROJECT} ${SOURCE}) 

