#include <Common/Math/Helpers/ComputationHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::mathHelper {

TEST(ComputationHelpersTest, GetAverageOfTwoNumbersWorksForPrimitiveTypes) {
    EXPECT_EQ(0, getAverage(-10, 10));
    EXPECT_EQ(55, getAverage(10, 100));
}

TEST(ComputationHelpersTest, GetAverageOfThreeNumbersWorks) {
    EXPECT_EQ(0, getAverage(-10, 10, 0));
    EXPECT_EQ(370, getAverage(10, 100, 1000));
}

TEST(ComputationHelpersTest, GetXSquaredPlusYSquaredWorks) {
    EXPECT_EQ(25, getXSquaredPlusYSquared(3, 4));
    EXPECT_EQ(169, getXSquaredPlusYSquared(5, -12));
    EXPECT_EQ(625, getXSquaredPlusYSquared(-7, 24));
    EXPECT_EQ(289, getXSquaredPlusYSquared(-8, -15));
}

TEST(ComputationHelpersTest, GetSquareRootOfXSquaredPlusYSquaredWorks) {
    EXPECT_EQ(5, getSquareRootOfXSquaredPlusYSquared(3, 4));
    EXPECT_EQ(13, getSquareRootOfXSquaredPlusYSquared(5, -12));
    EXPECT_EQ(25, getSquareRootOfXSquaredPlusYSquared(-7, 24));
    EXPECT_EQ(17, getSquareRootOfXSquaredPlusYSquared(-8, -15));
}

TEST(ComputationHelpersTest, GetSquareRootOfXSquaredPlusYSquaredPlusZSquaredWorks) {
    EXPECT_EQ(3, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(1, 2, 2));
    EXPECT_EQ(15, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(-2, 10, 11));
    EXPECT_EQ(21, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(4, -13, 16));
    EXPECT_EQ(27, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(2, 10, -25));
    EXPECT_EQ(7, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(-2, -3, -6));
}

TEST(ComputationHelpersTest, ClampLowerBoundWorks) {
    EXPECT_EQ(3, clampLowerBound(1, 3));
    EXPECT_EQ(3, clampLowerBound(2, 3));
    EXPECT_EQ(3, clampLowerBound(3, 3));
    EXPECT_EQ(4, clampLowerBound(4, 3));
    EXPECT_EQ(5, clampLowerBound(5, 3));
}

TEST(ComputationHelpersTest, ClampHigherBoundWorks) {
    EXPECT_EQ(1, clampHigherBound(1, 3));
    EXPECT_EQ(2, clampHigherBound(2, 3));
    EXPECT_EQ(3, clampHigherBound(3, 3));
    EXPECT_EQ(3, clampHigherBound(4, 3));
    EXPECT_EQ(3, clampHigherBound(5, 3));
}

TEST(ComputationHelpersTest, ClampWithinWorks) {
    EXPECT_EQ(2, clampWithin(1, 2, 4));
    EXPECT_EQ(2, clampWithin(2, 2, 4));
    EXPECT_EQ(3, clampWithin(3, 2, 4));
    EXPECT_EQ(4, clampWithin(4, 2, 4));
    EXPECT_EQ(4, clampWithin(5, 2, 4));
}

TEST(ComputationHelpersTest, GetAverageOfTwoNumbersForAlbaNumberWorks) {
    EXPECT_EQ(AlbaNumber(0), getAverage(AlbaNumber::createFraction(1, 3), AlbaNumber::createFraction(-1, 3)));
    EXPECT_EQ(
        AlbaNumber::createFraction(1, 3),
        getAverage(AlbaNumber::createFraction(1, 3), AlbaNumber::createFraction(1, 3)));
}

TEST(ComputationHelpersTest, GetQuadraticWorksWithRealRootsOnlyWithInputHavingRealRoots) {
    AlbaNumbers quadraticRoots(getQuadraticRoots(RootType::RealRootsOnly, 8, 22, 15));

    ASSERT_EQ(2U, quadraticRoots.size());
    EXPECT_EQ(AlbaNumber(-1.25), quadraticRoots.at(0));
    EXPECT_EQ(AlbaNumber(-1.5), quadraticRoots.at(1));
}

TEST(ComputationHelpersTest, GetQuadraticWorksWithRealRootsOnlyWithInputHavingImaginaryRoots) {
    AlbaNumbers quadraticRoots(getQuadraticRoots(RootType::RealRootsOnly, 1, 0, 4));

    EXPECT_TRUE(quadraticRoots.empty());
}

TEST(ComputationHelpersTest, GetQuadraticWorksWithRealAndImaginaryRootsWithInputHavingRealRoots) {
    AlbaNumbers quadraticRoots(getQuadraticRoots(RootType::RealAndImaginaryRoots, 8, 22, 15));

    ASSERT_EQ(2U, quadraticRoots.size());
    EXPECT_EQ(AlbaNumber(-1.25), quadraticRoots.at(0));
    EXPECT_EQ(AlbaNumber(-1.5), quadraticRoots.at(1));
}

TEST(ComputationHelpersTest, GetQuadraticWorksWithRealAndImaginaryRootsWithInputHavingImaginaryRoots) {
    AlbaNumbers quadraticRoots(getQuadraticRoots(RootType::RealAndImaginaryRoots, 1, 0, 4));

    ASSERT_EQ(2U, quadraticRoots.size());
    EXPECT_EQ(AlbaNumber::createComplexNumber(0, 2), quadraticRoots.at(0));
    EXPECT_EQ(AlbaNumber::createComplexNumber(0, -2), quadraticRoots.at(1));
}

}  // namespace alba::mathHelper
