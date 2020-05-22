cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(qsts)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

include_directories(qsts) 

enable_testing()

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

add_subdirectory(qsts)
add_subdirectory(examples)
add_subdirectory(docs)

