cmake_minimum_required(VERSION 3.11)

project(graphical)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 REQUIRED COMPONENTS Core Network Widgets)

include_directories(${Qt5Network_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/libs/graphical/include)


add_library(graphical SHARED
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/GraphicalManager.cpp
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/Scene.cpp
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/GraphicalException.cpp
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/DialogBox.cpp
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/Label.cpp
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/LineEdit.cpp
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/QButton.cpp
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/Widget.cpp
    ${PROJECT_SOURCE_DIR}/libs/graphical/src/AWidgets.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS} Qt5::Widgets)