#include "gtest/gtest.h"
#include <prism/global>
#include <prism/Size>
#include <prism/DivideByZeroException>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class SizeTests : public Test {

};

TEST_F(SizeTests, DefaultWidthAndHeightIsZero) {
    Size size;
    ASSERT_EQ(0, size.width());
    ASSERT_EQ(0, size.height());
}

TEST_F(SizeTests, CanUpdateWidth) {
    int newWidth = 10;
    Size size;
    size.setWidth(newWidth);
    ASSERT_EQ(newWidth, size.width());
}

TEST_F(SizeTests, CanUpdateHeight) {
    int newHeight = 10;
    Size size;
    size.setHeight(newHeight);
    ASSERT_EQ(newHeight, size.height());
}

TEST_F(SizeTests, CanUpdateWidthAndHeightSimultaneously) {
    int newWidth = 10;
    int newHeight = 20;
    Size size;
    size.set(newWidth, newHeight);
    ASSERT_EQ(newWidth, size.width());
    ASSERT_EQ(newHeight, size.height());
}

TEST_F(SizeTests, CanSetWidthAndHeightAtConstruction) {
    int newWidth = 10;
    int newHeight = 20;
    Size size(newWidth, newHeight);
    ASSERT_EQ(newWidth, size.width());
    ASSERT_EQ(newHeight, size.height());
}

TEST_F(SizeTests, CanMakeCopyOfSize) {
    Size size(10,20);
    Size copy1(size);
    Size copy2 = size;
    ASSERT_TRUE(copy1 == size);
    ASSERT_TRUE(copy2 == size);
}

TEST_F(SizeTests, CanResetToZero) {
    Size size(10,12);
    size.reset();
    ASSERT_EQ(Size(), size);
}

TEST_F(SizeTests, CanCheckIfSizeIsReset) {
    Size size(10,12);
    ASSERT_FALSE(size.isReset());
    size.reset();
    ASSERT_TRUE(size.isReset());
}

TEST_F(SizeTests, FlipWidthAndHeight) {
    Size size(10,20);
    size.transpose();
    ASSERT_EQ(Size(20,10), size);
}

TEST_F(SizeTests, ReturnTransposedCopy) {
    Size original(10,20);
    Size transposed = original.transposed();
    ASSERT_EQ(Size(10,20), original);
    ASSERT_EQ(Size(20,10), transposed);
}

TEST_F(SizeTests, IsValidIfBothWidthAndHeightNotNegative) {
    ASSERT_TRUE(Size(0,0).isValid());
    ASSERT_TRUE(Size(10,10).isValid());
    ASSERT_FALSE(Size(-3,0).isValid());
    ASSERT_FALSE(Size(0,-3).isValid());
}

TEST_F(SizeTests, CanScaleThisSizeByFactors) {
    int widthFactor = 2;
    int heightFactor = 3;
    Size original(5,6);
    original.scale(widthFactor, heightFactor);
    ASSERT_EQ(Size(10,18), original);
}

TEST_F(SizeTests, CanReturnNewSizeScaledByFactors) {
    int widthFactor = 2;
    int heightFactor = 3;
    Size original(5,6);
    Size scaled = original.scaled(widthFactor, heightFactor);
    ASSERT_EQ(Size(10,18), scaled);
    ASSERT_EQ(Size(5,6), original);
}

TEST_F(SizeTests, CanScaleThisSizeByOtherSize) {
    Size scaler(2,3);
    Size original(10,11);
    original.scale(scaler);
    ASSERT_EQ(Size(20,33), original);
}

TEST_F(SizeTests, CanReturnNewSizeScaledByOtherSize) {
    Size scaler(2,3);
    Size original(5,6);
    Size scaled = original.scaled(scaler);
    ASSERT_EQ(Size(10,18), scaled);
    ASSERT_EQ(Size(5,6), original);
}

TEST_F(SizeTests, CanCompareTwoSizesForEquality) {
    ASSERT_TRUE(Size(5,10) == Size(5,10));
    ASSERT_FALSE(Size(1,2) == Size(2,1));
}

TEST_F(SizeTests, CanCompareTwoSizesForInequality) {
    ASSERT_FALSE(Size(5,10) != Size(5,10));
    ASSERT_TRUE(Size(1,2) != Size(2,1));
}

TEST_F(SizeTests, CanAppendOtherSizeToThisSize) {
    Size original(1,2);
    original += Size(5,6);
    ASSERT_EQ(Size(6,8), original);
}

TEST_F(SizeTests, CanSubtractOtherSizeFromThisSize) {
    Size original(5,6);
    original -= Size(1,2);
    ASSERT_EQ(Size(4,4), original);
}

TEST_F(SizeTests, CanMultiplyThisSizeByFactor) {
    Size original(5,6);
    original *= 2;
    ASSERT_EQ(Size(10,12), original);
}

TEST_F(SizeTests, CanDivideThisSizeByFactor) {
    Size original(5,6);
    original /= 2;
    ASSERT_EQ(Size(2,3), original);
}

TEST_F(SizeTests, ThrowsWhenDividingByZero) {
    Size original(5,6);
    ASSERT_THROW(original /= 0, DivideByZeroException);
}

TEST_F(SizeTests, CanAddTwoSizesTogetherReturningNewSize) {
    Size lhs(5,6);
    Size rhs(1,2);
    Size result = lhs + rhs;
    ASSERT_EQ(Size(6,8), result);
    ASSERT_EQ(Size(5,6), lhs);
    ASSERT_EQ(Size(1,2), rhs);
}

TEST_F(SizeTests, CanSubtractTwoSizesReturningNewSize) {
    Size lhs(5,6);
    Size rhs(1,2);
    Size result = lhs - rhs;
    ASSERT_EQ(Size(4,4), result);
    ASSERT_EQ(Size(5,6), lhs);
    ASSERT_EQ(Size(1,2), rhs);
}

TEST_F(SizeTests, CanMultiplySizeByFactorReturningNewSize) {
    Size original(5,6);
    ASSERT_EQ(Size(50,60), original * 10);
    ASSERT_EQ(Size(50,60), 10 * original);
    ASSERT_EQ(Size(5,6), original);
}

TEST_F(SizeTests, CanDivideSizeByFactorReturningNewSize) {
    Size original(5,6);
    ASSERT_EQ(Size(2,3), original / 2);
    ASSERT_EQ(Size(5,6), original);
}

TEST_F(SizeTests, ThrowsWhenDividingSizeByOtherZeroFactor) {
    ASSERT_THROW(Size(5,6) / 0, DivideByZeroException);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
