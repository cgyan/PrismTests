#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/StringBuilder>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(StringBuilderTests, WhenDefaultBuilderIsCreatedExpectItToBeEmpty) {
    StringBuilder sb;
    EXPECT_TRUE(sb.empty());
}

TEST(StringBuilderTests, WhenDefaultBuilderIsCreatedExpectSizeToBeZero) {
    StringBuilder sb;
    const int expectedSize = 0;
    EXPECT_EQ(expectedSize, sb.size());
}

TEST(StringBuilderTests, WhenEmptyBuilderIsConvertedToStringExpectStringToBeEmpty) {
    StringBuilder sb;
    const std::string expectedString = "";
    EXPECT_EQ(expectedString, sb.toString());
}

TEST(StringBuilderTests, WhenAppendedToExpectBuilderNotToBeEmpty) {
    StringBuilder sb;
    sb.append('c');
    EXPECT_FALSE(sb.empty());
}

TEST(StringBuilderTests, WhenAppendedToExpectBuilderSizeToBeOne) {
    StringBuilder sb;
    sb.append('c');
    const int expectedSize = 1;
    EXPECT_EQ(expectedSize, sb.size());
}

TEST(StringBuilderTests, WhenClearingBuilderExpectSizeToBeZero) {
    StringBuilder sb("nyc");
    sb.clear();
    EXPECT_EQ(0, sb.size());
}

TEST(StringBuilderTests, WhenClearingBuilderExpectItToBeEmpty) {
    StringBuilder sb("nyc");
    sb.clear();
    EXPECT_TRUE(sb.empty());
}

TEST(StringBuilderTests, WhenClearingBuilderExpectConversionStringToBeEmpty) {
    StringBuilder sb("nyc");
    sb.clear();
    const std::string expectedString = "";
    EXPECT_EQ(expectedString, sb.toString());
}

TEST(StringBuilderTests, WhenCharIsAppendedExpectConversionStringToContainSingleChar) {
    StringBuilder sb;
    sb.append('c');
    EXPECT_EQ("c", sb.toString());
}

TEST(StringBuilderTests, WhenLiteralStringIsAppendedExpectConversionStringToContainString) {
    StringBuilder sb;
    sb.append("nyc");
    EXPECT_EQ("nyc", sb.toString());
}

TEST(StringBuilderTests, WhenStdStringIsAppendedExpectConversionStringToContainString) {
    StringBuilder sb;
    sb.append(std::string("nyc"));
    EXPECT_EQ("nyc", sb.toString());
}

TEST(StringBuilderTests, WhenLiteralTrueIsAppendedExpectConversionStringToContainBool) {
    StringBuilder sb;
    sb.append(true);
    EXPECT_EQ("true", sb.toString());
}

TEST(StringBuilderTests, WhenLiteralFalseIsAppendedExpectConversionStringToContainBool) {
    StringBuilder sb;
    sb.append(false);
    EXPECT_EQ("false", sb.toString());
}

TEST(StringBuilderTests, WhenIntegerIsAppendedExpectConversionStringToContainInt) {
    StringBuilder sb;
    sb.append(1);
    EXPECT_EQ("1", sb.toString());
}

TEST(StringBuilderTests, WhenDoubleIsAppendedExpectConversionStringToContainNumber) {
    StringBuilder sb;
    sb.append(3.14);
    EXPECT_EQ("3.14", sb.toString());
}

TEST(StringBuilderTests, WhenCharIsPrependedExpectConversionStringToContainString) {
    StringBuilder sb("each");
    sb.prepend('p');
    EXPECT_EQ("peach", sb.toString());
}

TEST(StringBuilderTests, WhenLiteralStringIsPrependedExpectConversionStringToContainString) {
    StringBuilder sb(" york");
    sb.prepend("new");
    EXPECT_EQ("new york", sb.toString());
}

TEST(StringBuilderTests, WhenStdStringIsPrependedExpectConversionStringToContainString) {
    StringBuilder sb(" york");
    sb.prepend(std::string("new"));
    EXPECT_EQ("new york", sb.toString());
}

TEST(StringBuilderTests, WhenLiteralTrueIsPrependedExpectConversionStringToContainBool) {
    StringBuilder sb(" lies");
    sb.prepend(true);
    EXPECT_EQ("true lies", sb.toString());
}

TEST(StringBuilderTests, WhenLiteralFalseIsPrependedExpectConversionStringToContainBool) {
    StringBuilder sb(" accusations");
    sb.prepend(false);
    EXPECT_EQ("false accusations", sb.toString());
}

TEST(StringBuilderTests, WhenIntIsPrependedExpectConversionStringToContainNumber) {
    StringBuilder sb(" red balloons");
    sb.prepend(99);
    EXPECT_EQ("99 red balloons", sb.toString());
}

TEST(StringBuilderTests, WhenDoubleIsPrependedExpectConversionStringToContainNumber) {
    StringBuilder sb(" is the value of pi");
    sb.prepend(3.14);
    EXPECT_EQ("3.14 is the value of pi", sb.toString());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
