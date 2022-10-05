cmake_minimum_required(VERSION 3.11)

project(${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

include(${PROJECT_SOURCE_DIR}/libs/network/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/libs/graphical/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/libs/audio/CMakeLists.txt)