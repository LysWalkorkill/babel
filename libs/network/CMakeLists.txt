cmake_minimum_required(VERSION 3.11)

project(network)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_AUTOMOC ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 REQUIRED COMPONENTS Network)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

set(CMAKE_CXX_STANDARD 17)

include_directories(${Qt5Network_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/libs/network/include)

file(GLOB_RECURSE SOURCES_CPP ${PROJECT_SOURCE_DIR}/libs/network/src/*.cpp)
file(GLOB_RECURSE SOURCES_HPP ${PROJECT_SOURCE_DIR}/libs/network/include/network/*.hpp)

add_library(network SHARED
    ${SOURCES_CPP}
    ${SOURCES_HPP}
)

set_property(TARGET network PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded")

target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS} Qt5::Network)
