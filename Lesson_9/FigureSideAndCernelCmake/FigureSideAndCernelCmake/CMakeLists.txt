cmake_minimum_required(VERSION 3.2.2)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")

add_executable(Figure ${SOURCES})

target_include_directories(Figure PUBLIC ${PROJECT_SOURCE_DIR}/include)


