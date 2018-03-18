set(MAIN_SOURCE ${MAIN_SOURCE}
    src/main/main.cpp
)

set(CORE_SOURCES ${CORE_SOURCES}
    src/core/AlgorithmMoveTests.cpp
    src/core/IteratorTests.cpp
    src/core/ListTests.cpp
    src/core/ObjectTests.cpp
    src/core/PairTests.cpp
    src/core/PointTests.cpp
    src/core/PStringTests.cpp
    src/core/RectTests.cpp
    src/core/SizeTests.cpp
    src/core/StackTests.cpp
    src/core/StringBuilderTests.cpp
    src/core/TimeTests.cpp
    # src/core/VectorTests.cpp
    src/core/json/JsonArrayTests.cpp
    src/core/json/JsonDocTests.cpp
    src/core/json/JsonLexerTests.cpp
    src/core/json/JsonObjectIteratorTests.cpp
    src/core/json/JsonObjectTests.cpp
    src/core/json/JsonParserExceptionTests.cpp
    src/core/json/JsonStringBuilderTests.cpp
    src/core/json/JsonValueTests.cpp
    src/core/json/fakes/FakeJsonArray.cpp
    src/core/json/fakes/FakeJsonObject.cpp
    src/core/json/fakes/FakeJsonValue.cpp
)

set(NON_TDD_SOURCES ${NON_TDD_SOURCES}
    src/non_tdd_unit_tests/algorithmTest.cpp
    src/non_tdd_unit_tests/ArrayTest.cpp
    src/non_tdd_unit_tests/BitvectorTest.cpp
    src/non_tdd_unit_tests/CircleTest.cpp
    src/non_tdd_unit_tests/DequeTest.cpp
    src/non_tdd_unit_tests/functorTest.cpp
    src/non_tdd_unit_tests/ListTest.cpp
    src/non_tdd_unit_tests/ReverseIteratorTest.cpp
    src/non_tdd_unit_tests/SharedDataPointerTest.cpp
    src/non_tdd_unit_tests/SharedDataTest.cpp
    src/non_tdd_unit_tests/StringTest.cpp
    src/non_tdd_unit_tests/TimeTest.cpp
    src/non_tdd_unit_tests/type_traitsTest.cpp
    src/non_tdd_unit_tests/UniquePointerArrayTest.cpp
    src/non_tdd_unit_tests/UniquePointerTest.cpp
    src/non_tdd_unit_tests/VersionTest.cpp
)

set(EVENT_SOURCES ${EVENT_SOURCES}
    src/eventsystem/PostedEventQueueTest.cpp
    src/eventsystem/RunLoopTest.cpp
    src/eventsystem/Win32EventQueueTest.cpp
)

set(GUI_SOURCES ${GUI_SOURCES}
    src/gui/WidgetTests.cpp
)

set(SOURCES
    ${MAIN_SOURCE}
    ${CORE_SOURCES}
    # ${NON_TDD_SOURCES}
    # ${EVENT_SOURCES}
    # ${GUI_SOURCES}
)
