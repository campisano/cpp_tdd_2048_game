cmake_minimum_required(VERSION 3.3.2)

include(ExternalProject)

set(NAME doctest)

externalproject_add(
    ${NAME}_external
    DOWNLOAD_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/download
    DOWNLOAD_NAME           ${NAME}.tar.gz
    URL                     https://github.com/onqtam/doctest/archive/refs/tags/2.4.6.tar.gz
    URL_HASH                MD5=f92e48e4054443a7b93bb26cecd34d2b
    SOURCE_DIR              ${CMAKE_CURRENT_BINARY_DIR}/source
    BINARY_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    INSTALL_DIR             ${CMAKE_CURRENT_BINARY_DIR}/install
    CONFIGURE_COMMAND       ""
    BUILD_COMMAND           ""
    INSTALL_COMMAND         ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/${NAME}/${NAME}.h <INSTALL_DIR>/include/${NAME}.h
    )

externalproject_get_property(${NAME}_external INSTALL_DIR)
set(${NAME}_INCLUDE_DIRS ${INSTALL_DIR}/include CACHE STRING "")

set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)
add_custom_target(${NAME}_clean_no_custom)
add_dependencies(${NAME}_clean_no_custom ${NAME}_external)

add_library(${NAME} INTERFACE)
add_dependencies(${NAME} ${NAME}_clean_no_custom)
