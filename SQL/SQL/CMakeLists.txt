cmake_minimum_required(VERSION 3.10)
project(ClientManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(libpqxx CONFIG REQUIRED)

add_executable(ClientManager main.cpp)

target_link_libraries(ClientManager PRIVATE     libpqxx::pqxx)


set_target_properties(ClientManager PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)