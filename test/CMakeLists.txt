cmake_minimum_required(VERSION 3.27)

project(XVFS.Test LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
"${CMAKE_CURRENT_SOURCE_DIR}/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

message(STATUS "Project source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(XVFS.Test ${TEST_SOURCES})

target_include_directories(XVFS.Test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(XVFS.Test PRIVATE XVFS)