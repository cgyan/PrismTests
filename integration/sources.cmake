set(FILE_INFO_SOURCES ${CORE_SOURCES}
    integration/src/core/FileInfo/FileInfoAbsolutePathIntegrationTests.cpp
    integration/src/core/FileInfo/FileInfoSizeIntegrationTests.cpp
    integration/src/core/FileInfo/FileInfoExistsIntegrationTests.cpp
)

set(INTEGRATION_SOURCES ${INTEGRATION_SOURCES}
    ${FILE_INFO_SOURCES}
)
