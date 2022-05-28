cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### Project Metadata
set(CMDARGS_PROJECT_NAME        "cmdargs")
set(CMDARGS_PROJECT_DESCRIPTION "a C++ CLI template")
set(CMDARGS_AUTHOR_DOMAIN       "https://www.sukesh.me")
set(CMDARGS_VERSION_MAJOR       "0")
set(CMDARGS_VERSION_MINOR       "0")
set(CMDARGS_VERSION_PATCH       "1")
set(CMDARGS_VERSION             "${CMDARGS_VERSION_MAJOR}.${CMDARGS_VERSION_MINOR}.${CMDARGS_VERSION_PATCH}")
set(CMDARGS_NAME_VERSION        "${CMDARGS_PROJECT_NAME} v${CMDARGS_VERSION} (${CMDARGS_VERSION_REVISION})")

### Declare Project
project(${CMDARGS_PROJECT_NAME})

set(CMDARGS_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(CMDARGS_INC_DIR ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(extern/cxxopts)
add_subdirectory(src)

configure_file(
        "${PROJECT_SOURCE_DIR}/version.hpp.in"
        "${PROJECT_BINARY_DIR}/version.hpp")