cmake_minimum_required(VERSION 3.11)

set(CMAKE_PROJECT_NAME babel)
project(${CMAKE_PROJECT_NAME})

add_definitions(-DRESOURCES_PATH="${CMAKE_SOURCE_DIR}/resources/")
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_definitions(-D_WIN32_WINNT=0x0601)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(${PROJECT_SOURCE_DIR}/libs/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/client/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/server/CMakeLists.txt)
