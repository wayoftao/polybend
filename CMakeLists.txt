cmake_minimum_required(VERSION 3.10)
project(polybend)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(polybend ${SOURCES} ${HEADERS})

target_compile_features(polybend PUBLIC cxx_std_17)
target_link_libraries(polybend Qt5::Widgets -lGL)
