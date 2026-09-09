cmake_minimum_required(VERSION 4.0)

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

set( TARGET_NAME tool )

file( GLOB_RECURSE SANDBOX_HEADERS src/*.h)
file( GLOB_RECURSE SANDBOX_SOURCES src/*.cpp)
file( GLOB_RECURSE SANDBOX_RCFILES res/*.qrc)

find_package( Qt5 COMPONENTS Core Qml Quick Network REQUIRED )

add_executable( ${TARGET_NAME} ${SANDBOX_HEADERS} ${SANDBOX_SOURCES} ${SANDBOX_RCFILES} )

target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Qml Qt5::Quick Qt5::Network )

target_link_libraries( ${TARGET_NAME} SimDS )

target_include_directories( ${TARGET_NAME} PRIVATE src)
