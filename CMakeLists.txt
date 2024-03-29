cmake_minimum_required(VERSION 3.3.2 FATAL_ERROR)

project(2048 LANGUAGES CXX)

# global properties
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_SKIP_RPATH TRUE)

# project dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/external/doctest)
include_directories(${doctest_INCLUDE_DIRS})

# project sources
file(GLOB_RECURSE VAR_APP_SOURCES ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/*.cpp ${PROJECT_SOURCE_DIR}/src/common/*.cpp)
file(GLOB_RECURSE VAR_TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/test/*.cpp)

# project outputs
add_library(${PROJECT_NAME}_common OBJECT ${VAR_APP_SOURCES})
#add_dependencies(${PROJECT_NAME}_common ?)

add_executable(${PROJECT_NAME}_exec $<TARGET_OBJECTS:${PROJECT_NAME}_common> ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME}_exec PUBLIC stdc++ pthread)

add_executable(${PROJECT_NAME}_test $<TARGET_OBJECTS:${PROJECT_NAME}_common> ${VAR_TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_test PUBLIC stdc++ pthread
    doctest)

# project outputs specific properties
set_target_properties(${PROJECT_NAME}_common ${PROJECT_NAME}_exec ${PROJECT_NAME}_test PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED TRUE)

# GNU compiler specific flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # global
    set(BASE_CXX_FLAGS "-pipe -fexceptions -pedantic -Wall -Wextra -Wshadow -Wnon-virtual-dtor")

    # RELEASE: use optimization, remove all symbol table
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
        set_target_properties(${PROJECT_NAME}_common ${PROJECT_NAME}_exec ${PROJECT_NAME}_test PROPERTIES
            COMPILE_FLAGS "${COMPILE_FLAGS} ${BASE_CXX_FLAGS} -O2 -s"
            LINK_FLAGS "${LINK_FLAGS}")
    endif()

    # DEBUG: use debug optimization, increase debug level to 3, mantain frame pointer to use linux 'prof' tool
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
        set_target_properties(${PROJECT_NAME}_common ${PROJECT_NAME}_exec ${PROJECT_NAME}_test PROPERTIES
            COMPILE_FLAGS "${COMPILE_FLAGS} ${BASE_CXX_FLAGS} -Og -ggdb3 -g3 -fno-omit-frame-pointer --coverage"
            LINK_FLAGS "${LINK_FLAGS} --coverage")
    endif()
endif()
