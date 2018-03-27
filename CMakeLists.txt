cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME runner)
project(${PROJECT_NAME})

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

# elseif(APPLE)
#
#         set(PRISM_LIB_NAME prism)
#         set(PRISM_INC_PATH /Users/iainhemstock/GitHub/prism/inc)
#         set(PRISM_LIB_PATH /Users/iainhemstock/GitHub/prism/build)
#
endif()

include_directories(
        integration/inc
        unit/inc
        core/inc
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

find_library(SHLWAPI
        NAMES libshlwapi
        PATHS C:/Program_Files/mingw-w64/x86_64-6.3.0-posix-sjlj-rt_v5-rev2/mingw64/x86_64-w64-mingw32/lib
)

include(core/sources.cmake)
include(integration/sources.cmake)
include(unit/sources.cmake)

add_executable(${PROJECT_NAME}
        main.cpp
        ${CORE_SOURCES}
        ${INTEGRATION_SOURCES}
        ${UNIT_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
        ${PRISM_LIB}
        ${GMOCK_LIB}
        ${GTEST_LIB}
        ${SHLWAPI}
)


# cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
#
# project(PrismTests)
#
# # pass arg from cmd line with -Dunit=ON
# option(integration "BuildIntegrationTests" OFF)
# option(unit "BuildUnitTests" ON)
#
# if (integration AND unit)
#     message("PrismTests: include integration tests = YES")
#     message("PrismTests: include unit tests = YES")
#     add_subdirectory(integration)
#     add_subdirectory(unit)
# elseif(integration)
#     message("PrismTests: include integration tests = YES")
#     message("PrismTests: include unit tests = NO")
#     add_subdirectory(integration)
# elseif(unit)
#     message("PrismTests: include integration tests = NO")
#     message("PrismTests: include unit tests = YES")
#     add_subdirectory(unit)
# else()
#     message("PrismTests: include integration tests = NO")
#     message("PrismTests: include unit tests = NO")
#     message("PrismTests: NO TESTS INCLUDED IN BUILD!!")
# endif()
