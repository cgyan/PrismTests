set(MAIN_SOURCE ${MAIN_SOURCE}
    unit/src/main.cpp
)

set(CORE_SOURCES ${CORE_SOURCES}
    unit/src/core/AlgorithmMoveTests.cpp
    unit/src/core/IteratorTests.cpp
    unit/src/core/json/JsonArrayTests.cpp
    unit/src/core/json/JsonDocTests.cpp
    unit/src/core/json/JsonLexerTests.cpp
    unit/src/core/json/JsonObjectIteratorTests.cpp
    unit/src/core/json/JsonObjectTests.cpp
    unit/src/core/json/JsonParserExceptionTests.cpp
    unit/src/core/json/JsonStringBuilderTests.cpp
    unit/src/core/json/JsonValueTests.cpp
    unit/src/core/ObjectTests.cpp
    unit/src/core/PairTests.cpp
    unit/src/core/PointTests.cpp
    unit/src/core/PStringTests.cpp
    unit/src/core/RectTests.cpp
    unit/src/core/SizeTests.cpp
    unit/src/core/StackTests.cpp
    unit/src/core/StringBuilderTests.cpp
    unit/src/core/VectorTests.cpp
)

set(FILE_INFO_SOURCES ${FILE_INFO_SOURCES}
        unit/src/core/FileInfo/FileInfoExistsTests.cpp
        unit/src/core/FileInfo/FileInfoBasenameTests.cpp
        unit/src/core/FileInfo/FileInfoFilenameTests.cpp
        unit/src/core/FileInfo/FileInfoSizeTests.cpp
)

set(NON_TDD_SOURCES ${NON_TDD_SOURCES}
    unit/src/non_tdd_unit_tests/algorithmTest.cpp
    unit/src/non_tdd_unit_tests/ArrayTest.cpp
    unit/src/non_tdd_unit_tests/BitvectorTest.cpp
    unit/src/non_tdd_unit_tests/CircleTest.cpp
    unit/src/non_tdd_unit_tests/DequeTest.cpp
    unit/src/non_tdd_unit_tests/functorTest.cpp
    unit/src/non_tdd_unit_tests/ReverseIteratorTest.cpp
    unit/src/non_tdd_unit_tests/SharedDataPointerTest.cpp
    unit/src/non_tdd_unit_tests/SharedDataTest.cpp
    unit/src/non_tdd_unit_tests/StringTest.cpp
    unit/src/non_tdd_unit_tests/TimeTest.cpp
    unit/src/non_tdd_unit_tests/UniquePointerArrayTest.cpp
    unit/src/non_tdd_unit_tests/UniquePointerTest.cpp
    unit/src/non_tdd_unit_tests/VersionTest.cpp
)

set(UNIT_SOURCES ${UNIT_SOURCES}
    # ${MAIN_SOURCE}
    ${CORE_SOURCES}
    ${FILE_INFO_SOURCES}
    ${NON_TDD_SOURCES}
)
