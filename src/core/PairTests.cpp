#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/Pair>
#include <string>
#include <prism/Vector>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(PairTests, WhenCreatingDefaultPairExpectValuesToBeDefaultInitialized) {
    const int defaultInitializedInt{};
    const std::string defaultInitializedString{};

    Pair<int, std::string> pair;

    EXPECT_EQ(defaultInitializedInt, pair.first);
    EXPECT_EQ(defaultInitializedString, pair.second);
}

TEST(PairTests, WhenSwappingTwoPairsExpectTheContentsOfEachPairToSwapToTheOther) {
    Pair<int, double> pair1(1, 3.14);
    Pair<int, double> pair2(2, 6.28);

    pair1.swap(pair2);

    EXPECT_EQ(make_pair(1, 3.14), pair2);
    EXPECT_EQ(make_pair(2, 6.28), pair1);
}

TEST(PairTests, WhenMoveConstructingPairExpectOriginalPairToBeResetAfterwards) {
    Pair<int,double> original = make_pair(1, 3.14);
    Pair<int,double> otherPair(std::move(original));
    Pair<int,double> expected = make_pair<int,double>();
    EXPECT_EQ(expected, original);
}

TEST(PairTests, WhenMoveConstructingPairExpectOriginalPairStateToMoveToOtherPair) {
    Pair<int,double> original = make_pair(1, 3.14);
    Pair<int,double> otherPair(std::move(original));
    EXPECT_EQ(make_pair(1, 3.14), otherPair);
}

TEST(PairTests, WhenMoveAssigningPairExpectOriginalPairToBeResetAfterwards) {
    Pair<int,double> original = make_pair(1, 3.14);
    Pair<int,double> otherPair;
    otherPair = std::move(original);
    Pair<int,double> expected = make_pair<int,double>();
    EXPECT_EQ(expected, original);
}

TEST(PairTests, WhenMoveAssigningPairExpectOriginalPairStateToMoveToOtherPair) {
    Pair<int,double> original = make_pair(1, 3.14);
    Pair<int,double> otherPair;
    otherPair = std::move(original);
    EXPECT_EQ(make_pair(1, 3.14), otherPair);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
