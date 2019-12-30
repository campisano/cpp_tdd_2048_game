cmake_minimum_required(VERSION 3.3.2)

project(2048 LANGUAGES CXX)

# global properties
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SKIP_RPATH ON)

# project dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/external/cpputest)
include_directories(${cpputest_INCLUDE_DIRS})
link_directories(${cpputest_LIBRARY_DIRS})

# project sources
file(GLOB_RECURSE VAR_APP_SOURCES ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/*.cpp)
file(GLOB_RECURSE VAR_TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/test/*.cpp)

# project outputs
add_library(common_objects OBJECT ${VAR_APP_SOURCES})
#add_dependencies(common_objects ?)

add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:common_objects> ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC stdc++ pthread)

add_executable(${PROJECT_NAME}_test $<TARGET_OBJECTS:common_objects> ${VAR_TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_test PUBLIC stdc++ pthread
    cpputest)

# project outputs specific properties
set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test PROPERTIES
    CMAKE_CXX_STANDARD 11
    CMAKE_CXX_STANDARD_REQUIRED ON)

# GNU compiler specific flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # global
    set(BASE_CXX_FLAGS "-pipe -fexceptions -pedantic -Wall -Wextra -Wshadow -Wnon-virtual-dtor")

    # RELEASE: use optimization, remove all symbol table
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
        set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test PROPERTIES
            COMPILE_FLAGS "${COMPILE_FLAGS} ${BASE_CXX_FLAGS} -O3 -s"
            LINK_FLAGS "${LINK_FLAGS}")
    endif()

    # DEBUG: use debug optimization, increase debug level to 3, mantain frame pointer to use linux 'prof' tool
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
        set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test PROPERTIES
            COMPILE_FLAGS "${COMPILE_FLAGS} ${BASE_CXX_FLAGS} -Og -ggdb3 -g3 -fno-omit-frame-pointer"
            LINK_FLAGS "${LINK_FLAGS}")
    endif()
endif()
