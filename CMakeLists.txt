cmake_minimum_required(VERSION 3.10)
project(polybend VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(OpenGL 3 REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(include)
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)
file(GLOB UI ui/*.ui)
file(GLOB RESOURCES src/*.qrc)

add_executable(polybend ${SOURCES} ${HEADERS} ${UI} ${RESOURCES})

target_compile_features(polybend PUBLIC cxx_std_17)
target_link_libraries(polybend Qt5::Widgets OpenGL::OpenGL OpenGL::GL)
