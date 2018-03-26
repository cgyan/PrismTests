set(MAIN_SOURCE ${MAIN_SOURCE}
    integration/src/main.cpp
)

set(CORE_SOURCES ${CORE_SOURCES}
    integration/src/core/FileInfoIntegrationTests.cpp
)

set(INTEGRATION_SOURCES ${INTEGRATION_SOURCES}
    # ${MAIN_SOURCE}
    ${CORE_SOURCES}
)
