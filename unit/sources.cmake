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
    unit/src/core/json/fakes/FakeJsonArray.cpp
    unit/src/core/json/fakes/FakeJsonObject.cpp
    unit/src/core/json/fakes/FakeJsonValue.cpp
    unit/src/core/ListTests.cpp
    unit/src/core/ObjectTests.cpp
    unit/src/core/PairTests.cpp
    unit/src/core/PointTests.cpp
    unit/src/core/PStringTests.cpp
    unit/src/core/RectTests.cpp
    unit/src/core/SizeTests.cpp
    unit/src/core/StackTests.cpp
    unit/src/core/StringBuilderTests.cpp
    unit/src/core/TimeTests.cpp
    unit/src/core/VectorTests.cpp
)

set(NON_TDD_SOURCES ${NON_TDD_SOURCES}
    unit/src/non_tdd_unit_tests/algorithmTest.cpp
    unit/src/non_tdd_unit_tests/ArrayTest.cpp
    unit/src/non_tdd_unit_tests/BitvectorTest.cpp
    unit/src/non_tdd_unit_tests/CircleTest.cpp
    unit/src/non_tdd_unit_tests/DequeTest.cpp
    unit/src/non_tdd_unit_tests/functorTest.cpp
    unit/src/non_tdd_unit_tests/ListTest.cpp
    unit/src/non_tdd_unit_tests/ReverseIteratorTest.cpp
    unit/src/non_tdd_unit_tests/SharedDataPointerTest.cpp
    unit/src/non_tdd_unit_tests/SharedDataTest.cpp
    unit/src/non_tdd_unit_tests/StringTest.cpp
    unit/src/non_tdd_unit_tests/TimeTest.cpp
    unit/src/non_tdd_unit_tests/UniquePointerArrayTest.cpp
    unit/src/non_tdd_unit_tests/UniquePointerTest.cpp
    unit/src/non_tdd_unit_tests/VersionTest.cpp
)

set(EVENT_SOURCES ${EVENT_SOURCES}
    unit/src/eventsystem/PostedEventQueueTest.cpp
    unit/src/eventsystem/RunLoopTest.cpp
    unit/src/eventsystem/Win32EventQueueTest.cpp
)

set(GUI_SOURCES ${GUI_SOURCES}
    unit/src/gui/WidgetTests.cpp
)

set(UNIT_SOURCES
    ${CORE_SOURCES}
    ${NON_TDD_SOURCES}
    # ${EVENT_SOURCES}
    # ${GUI_SOURCES}
)
