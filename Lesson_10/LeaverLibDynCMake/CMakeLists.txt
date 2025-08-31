
cmake_minimum_required(VERSION 3.2.2)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Lib SHARED Lib/Lib.cpp Lib/Lib.h)

target_compile_definitions(Lib PRIVATE LEAVERLIBDYN_EXPORTS) 

add_executable (LeaverLibD main.cpp)

target_link_libraries(LeaverLibD PRIVATE Lib)
