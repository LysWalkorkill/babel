cmake_minimum_required(VERSION 3.11)

set(CMAKE_PROJECT_NAME babel_server)
set(CMAKE_BUILD_TYPE Release)
project(${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

# CONAN
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(server/include)
include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${PROJECT_SOURCE_DIR}/libs/network/include)
link_directories(${CMAKE_SOURCE_DIR}/build)

file(GLOB_RECURSE SOURCES_CPP ${PROJECT_SOURCE_DIR}/server/src/*.cpp)
file(GLOB_RECURSE SOURCES_HPP ${PROJECT_SOURCE_DIR}/server/include/*.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES_CPP})
target_link_libraries(${CMAKE_PROJECT_NAME} network sqlite3)