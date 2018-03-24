set(MAIN_SOURCE ${MAIN_SOURCE}
    src/main.cpp
)

set(CORE_SOURCES ${CORE_SOURCES}
    src/core/AlgorithmMoveTests.cpp
    src/core/FileInfoUnitTests.cpp
    src/core/IteratorTests.cpp
    src/core/json/JsonArrayTests.cpp
    src/core/json/JsonDocTests.cpp
    src/core/json/JsonLexerTests.cpp
    src/core/json/JsonObjectIteratorTests.cpp
    src/core/json/JsonObjectTests.cpp
    src/core/json/JsonParserExceptionTests.cpp
    src/core/json/JsonStringBuilderTests.cpp
    src/core/json/JsonValueTests.cpp
    src/core/ObjectTests.cpp
    src/core/PairTests.cpp
    src/core/PointTests.cpp
    src/core/PStringTests.cpp
    src/core/RectTests.cpp
    src/core/SizeTests.cpp
    src/core/StackTests.cpp
    src/core/StringBuilderTests.cpp
    src/core/VectorTests.cpp
)

set(NON_TDD_SOURCES ${NON_TDD_SOURCES}
    src/non_tdd_unit_tests/algorithmTest.cpp
    src/non_tdd_unit_tests/ArrayTest.cpp
    src/non_tdd_unit_tests/BitvectorTest.cpp
    src/non_tdd_unit_tests/CircleTest.cpp
    src/non_tdd_unit_tests/DequeTest.cpp
    src/non_tdd_unit_tests/functorTest.cpp
    src/non_tdd_unit_tests/ReverseIteratorTest.cpp
    src/non_tdd_unit_tests/SharedDataPointerTest.cpp
    src/non_tdd_unit_tests/SharedDataTest.cpp
    src/non_tdd_unit_tests/StringTest.cpp
    src/non_tdd_unit_tests/TimeTest.cpp
    src/non_tdd_unit_tests/UniquePointerArrayTest.cpp
    src/non_tdd_unit_tests/UniquePointerTest.cpp
    src/non_tdd_unit_tests/VersionTest.cpp
)

set(SOURCES
    ${MAIN_SOURCE}
    ${CORE_SOURCES}
    ${NON_TDD_SOURCES}
)
