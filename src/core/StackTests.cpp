#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/Stack>
#include <prism/algorithm>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(StackTests, WhenDefaultStackIsCreatedExpectItToBeEmpty) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
}

TEST(StackTests, WhenDefaultStackIsCreatedExpectSizeToBeZero) {
    Stack<int> s;
    EXPECT_EQ(0, s.size());
}

TEST(StackTests, WhenElementIsPushedOntoEmptyStackExpectItNotToBeEmpty){
    Stack<int> s;
    s.push(1);
    EXPECT_FALSE(s.empty());
}

TEST(StackTests, WhenElementIsPushedOntoEmptyStackExpectItToHaveSizeOne) {
    Stack<int> s;
    s.push(1);
    EXPECT_EQ(1, s.size());
}

TEST(StackTests, WhenPushing1000ElementsOntoStackExpectSizeToBe1000) {
    const int numElements = 1000;
    Stack<int> s;
    for (int i = 0; i < numElements; ++i)
        s.push(i);
    EXPECT_EQ(numElements, s.size());
}

TEST(StackTests, WhenPushingElementOntoStackExpectItToBeTheTopElement) {
    Stack<int> s;
    const int value = 1;
    s.push(value);
    EXPECT_EQ(value, s.top());
}

TEST(StackTests, WhenAccessingTopElementInStackExpectToBeAbleToModifyItDirectly) {
    Stack<int> s;
    s.push(1);

    s.top() = 2;

    EXPECT_EQ(2, s.top());
}

TEST(StackTests, WhenPoppingLastElementInStackExpectStackToBeEmpty) {
    Stack<int> stack;
    stack.push(1);

    stack.pop();

    EXPECT_TRUE(stack.empty());
}

TEST(StackTests, WhenPoppingLastElementInStackExpectStackSizeToBeZero) {
    Stack<int> stack;
    stack.push(1);

    stack.pop();

    EXPECT_EQ(0, stack.size());
}

TEST(StackTests, WhenClearingPopulatedStackExpectItToBeEmpty) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    stack.clear();

    EXPECT_TRUE(stack.empty());
}

TEST(StackTests, WhenClearingPopulatedStackExpectItToHaveSizeZero) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    stack.clear();

    EXPECT_EQ(0, stack.size());
}

TEST(StackTests, WhenSwappingTwoStacksExpectTheContentOfEachStackToSwitchToTheOtherStack) {
    Stack<int> stackOdd;
    stackOdd.push(1);
    stackOdd.push(3);

    Stack<int> stackEven;
    stackEven.push(2);
    stackEven.push(4);

    Stack<int> copyStackOdd = stackOdd;
    Stack<int> copyStackEven = stackEven;

    stackOdd.swap(stackEven);

    EXPECT_EQ(copyStackOdd, stackEven);
    EXPECT_EQ(copyStackEven, stackOdd);
    EXPECT_NE(copyStackOdd, stackOdd);
    EXPECT_NE(copyStackEven, stackEven);
}

TEST(StackTests, WhenSwappingStacksWithPrismSwapExpectTheContentOfEachStackToSwapWithEachOther) {
    Stack<int> stackOdd;
    stackOdd.push(1);
    stackOdd.push(3);

    Stack<int> stackEven;
    stackEven.push(2);
    stackEven.push(4);

    Stack<int> copyStackOdd = stackOdd;
    Stack<int> copyStackEven = stackEven;

    prism::swap(stackOdd, stackEven);

    EXPECT_EQ(copyStackOdd, stackEven);
    EXPECT_EQ(copyStackEven, stackOdd);
    EXPECT_NE(copyStackOdd, stackOdd);
    EXPECT_NE(copyStackEven, stackEven);
}

TEST(StackTests, WhenMakingCopyOfStackExpectNewCopyToContainSameDataAsOriginalStack) {
    Stack<int> stack;
    stack << 7 << 8 << 9;

    Stack<int> copy = stack;

    EXPECT_EQ(copy, stack);
}

TEST(StackTests, WhenCreatingStackFromVectorExpectStackToContainSameDataAsVector) {
    prism::Vector<int> vector;
    vector << 1 << 3 << 5;

    Stack<int> expected;
    expected << 1 << 3 << 5;

    Stack<int> stack(vector);

    EXPECT_EQ(expected, stack);
}

TEST(StackTests, WhenStaticallyCreatingStackFromVectorExpectStackToContainSameDataAsVector) {
    prism::Vector<int> vector;
    vector << 1 << 3 << 5;

    Stack<int> expected;
    expected << 1 << 3 << 5;

    Stack<int> stack = Stack<int>::fromVector(vector);

    EXPECT_EQ(expected, stack);
}

TEST(StackTests, WhenAssigningOtherStackToThisStackExpectTheContentsOfOtherStackCopiedToThisStack) {
    Stack<int> otherStack;
    otherStack += 1;
    otherStack += 2;

    Stack<int> originalStack;
    originalStack = otherStack;

    EXPECT_EQ(otherStack, originalStack);
}

TEST(StackTests, WhenMovingElementsFromOtherStackExpectThisStackToContainThoseElements) {
    Stack<int> otherStack(Vector<int>({1,2,3}));
    Stack<int> thisStack = std::move(otherStack);
    Stack<int> expected = Stack<int>(Vector<int>({1,2,3}));
    EXPECT_EQ(expected, thisStack);
}

TEST(StackTests, WhenMovingElementsFromOtherStackExpectOtherStackToBeEmptyAfterwards) {
    Stack<int> otherStack(Vector<int>({1,2,3}));
    Stack<int> thisStack = std::move(otherStack);
    EXPECT_TRUE(otherStack.empty());
}

TEST(StackTests, WhenMovingElementsFromOtherStackExpectOtherStackToHaveSizeZeroAfterwards) {
    Stack<int> otherStack(Vector<int>({1,2,3}));
    Stack<int> thisStack = std::move(otherStack);
    EXPECT_EQ(0, otherStack.size());
}

TEST(StackTests, WhenMoveAssigningElementsFromOtherStackExpectThisStackToContainThoseElements) {
    Stack<int> otherStack(Vector<int>({1,2,3}));

    Stack<int> thisStack;
    thisStack = std::move(otherStack);

    Stack<int> expected = Stack<int>(Vector<int>({1,2,3}));
    EXPECT_EQ(expected, thisStack);
}

TEST(StackTests, WhenMoveAssigningElementsFromOtherStackExpectOtherStackToBeEmptyAfterwards) {
    Stack<int> otherStack(Vector<int>({1,2,3}));

    Stack<int> thisStack;
    thisStack = std::move(otherStack);

    EXPECT_TRUE(otherStack.empty());
}

TEST(StackTests, WhenMoveAssigningElementsFromOtherStackExpectOtherStackToHaveSizeZeroAfterwards) {
    Stack<int> otherStack(Vector<int>({1,2,3}));

    Stack<int> thisStack;
    thisStack = std::move(otherStack);

    EXPECT_EQ(0, otherStack.size());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
