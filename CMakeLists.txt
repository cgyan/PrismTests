cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("PrismTests")
set(EXE_NAME runner)

# add_definitions(-std=c++11)
set(CMAKE_CXX_STANDARD 11)

if (WIN32)

    set(PRISM_LIB_NAME libprism)
    set(PRISM_INC_PATH C:/Users/Iain/GitHub/prism/inc)
    set(PRISM_LIB_PATH C:/Users/Iain/GitHub/prism/build)

    set(GMOCK_LIB_NAME libgmock)
    set(GMOCK_INC_PATH C:/Users/Iain/GitHub/googletest/googlemock/include)
    set(GMOCK_LIB_PATH C:/Users/Iain/GitHub/googletest/build/googlemock)

    set(GTEST_LIB_NAME libgtest)
    set(GTEST_INC_PATH C:/Users/Iain/GitHub/googletest/googletest/include)
    set(GTEST_LIB_PATH C:/Users/Iain/GitHub/googletest/build/googlemock/gtest)

elseif(APPLE)

    set(PRISM_LIB_NAME prism)
    set(PRISM_INC_PATH /Users/iainhemstock/GitHub/prism/inc)
    set(PRISM_LIB_PATH /Users/iainhemstock/GitHub/prism/build)

    set(GMOCK_LIB_NAME gmock)
    set(GMOCK_INC_PATH /Users/iainhemstock/GitHub/googletest/googlemock/include)
    set(GMOCK_LIB_PATH /Users/iainhemstock/GitHub/googletest/build/googlemock)

    set(GTEST_LIB_NAME gtest)
    set(GTEST_INC_PATH /Users/iainhemstock/GitHub/googletest/googletest/include)
    set(GTEST_LIB_PATH /Users/iainhemstock/GitHub/googletest/build/googlemock/gtest)

    message(${PRISM_INC_PATH})

endif()

include_directories(
    inc
    ${PRISM_INC_PATH}
    ${GMOCK_INC_PATH}
    ${GTEST_INC_PATH}
)

find_library(PRISM_LIB
    NAMES ${PRISM_LIB_NAME}
    PATHS ${PRISM_LIB_PATH}
)

find_library(GMOCK_LIB
    NAMES ${GMOCK_LIB_NAME}
    PATHS ${GMOCK_LIB_PATH}
)

find_library(GTEST_LIB
    NAMES ${GTEST_LIB_NAME}
    PATHS ${GTEST_LIB_PATH}
)

include(sources.cmake)
add_executable(${EXE_NAME} ${SOURCES})
target_link_libraries(${EXE_NAME} ${PRISM_LIB} ${GMOCK_LIB} ${GTEST_LIB})
