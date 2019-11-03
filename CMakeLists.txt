cmake_minimum_required(VERSION 3.3.2)

project(2048 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SKIP_RPATH ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(
        CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -pipe -fexceptions -pedantic -Wall -Wextra")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/external/cpputest)
include_directories(${cpputest_INCLUDE_DIRS})
link_directories(${cpputest_LIBRARY_DIRS})

file(GLOB_RECURSE VAR_APP_SOURCES ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/*.cpp)
file(GLOB_RECURSE VAR_TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/test/*.cpp)

add_library(common_objects OBJECT ${VAR_APP_SOURCES})
#add_dependencies(common_objects ?)

add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:common_objects> ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC stdc++ pthread)

add_executable(${PROJECT_NAME}_test $<TARGET_OBJECTS:common_objects> ${VAR_TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_test PUBLIC stdc++ pthread
    cpputest)
