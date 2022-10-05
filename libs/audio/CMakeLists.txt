cmake_minimum_required(VERSION 3.11)

project(audio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_AUTOMOC ON)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${PROJECT_SOURCE_DIR}/libs/audio/include)

file(GLOB_RECURSE SOURCES_CPP ${PROJECT_SOURCE_DIR}/libs/audio/src/*.cpp)
file(GLOB_RECURSE SOURCES_HPP ${PROJECT_SOURCE_DIR}/libs/audio/include/audio/*.hpp)

add_library(audio SHARED
    ${SOURCES_CPP}
    ${SOURCES_HPP}
)

target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS})