cmake_minimum_required(VERSION 3.10)
project(polybend VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(include)
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

add_executable(polybend ${SOURCES} ${HEADERS})

target_compile_features(polybend PUBLIC cxx_std_17)
target_link_libraries(polybend Qt5::Widgets -lGL)
