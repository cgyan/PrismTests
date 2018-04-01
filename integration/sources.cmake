set(MAIN_SOURCE ${MAIN_SOURCE}
    integration/src/main.cpp
)

set(FILE_INFO_SOURCES ${CORE_SOURCES}
    integration/src/core/FileInfo/FileInfoIntegrationTests.cpp
    integration/src/core/FileInfo/FileInfoAbsolutePathIntegrationTests.cpp
    integration/src/core/FileInfo/FileInfoSizeIntegrationTests.cpp
)

set(INTEGRATION_SOURCES ${INTEGRATION_SOURCES}
    # ${MAIN_SOURCE}
    ${FILE_INFO_SOURCES}
)
