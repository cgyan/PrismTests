cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("Prism Tests")
set(EXE_NAME runner)

include_directories(c:/inc inc)

include(sources.cmake)
add_executable(${EXE_NAME} ${SOURCES})

find_library(PRISM_LIB prism)
find_library(GTEST_LIB gtest)
target_link_libraries(${EXE_NAME} ${PRISM_LIB} ${GTEST_LIB})
