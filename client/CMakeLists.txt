cmake_minimum_required(VERSION 3.11)

set(CMAKE_PROJECT_NAME babel_client)
set(CMAKE_BUILD_TYPE Debug)
project(${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
add_definitions(-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=1)

# CONAN
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# QT COMPONENTS
find_package(Qt5 REQUIRED COMPONENTS Core Network Widgets)

# QT INCLUDES
include_directories(${Qt5Network_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

# INCLUDES
include_directories(client/include)
include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${PROJECT_SOURCE_DIR}/libs/network/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/graphical/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/audio/include)
include_directories(${CONAN_INCLUDE_DIRS})

link_directories(${CMAKE_SOURCE_DIR}/build)
link_directories(${CMAKE_SOURCE_DIR}/build/bin)
link_directories(${CMAKE_SOURCE_DIR}/build/lib)

file(GLOB_RECURSE SOURCES_CPP ${PROJECT_SOURCE_DIR}/client/src/*.cpp)
file(GLOB_RECURSE SOURCES_HPP ${PROJECT_SOURCE_DIR}/client/include/*.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES_CPP} ${SOURCES_HPP})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS} Qt5::Widgets network graphical audio)
