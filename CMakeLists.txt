cmake_minimum_required(VERSION 3.17)

set(TARGET_NAME 2GISTestAssignment)
project(${TARGET_NAME})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core Gui Qml Quick QuickControls2 REQUIRED)

file(GLOB_RECURSE HEADER_FILES "dev/*.h")
file(GLOB_RECURSE SOURCE_FILES "dev/*.cpp")
file(GLOB_RECURSE RESOURCE_FILES "dev/*.qrc")

add_executable(${TARGET_NAME} ${HEADER_FILES}
        ${SOURCE_FILES} ${RESOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/dev)
target_link_libraries(${TARGET_NAME} PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Gui
        Qt5::Qml
        Qt5::Quick
        Qt5::QuickControls2
        )