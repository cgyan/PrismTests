cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(prismtestscore)

set(CMAKE_CXX_STANDARD 11)

if (WIN32)

    set(PRISM_LIB_NAME libprism)
    set(PRISM_INC_PATH C:/Users/Iain/GitHub/prism/inc)
    set(PRISM_LIB_PATH C:/Users/Iain/GitHub/prism/build)

elseif(APPLE)

    set(PRISM_LIB_NAME prism)
    set(PRISM_INC_PATH /Users/iainhemstock/GitHub/prism/inc)
    set(PRISM_LIB_PATH /Users/iainhemstock/GitHub/prism/build)

endif()

include_directories(
    inc
    ${PRISM_INC_PATH}
)

find_library(PRISM_LIB
    NAMES ${PRISM_LIB_NAME}
    PATHS ${PRISM_LIB_PATH}
)

include(sources.cmake)
add_library(prismtestscore STATIC ${SOURCES})

target_link_libraries(prismtestscore
    ${PRISM_LIB}
)
