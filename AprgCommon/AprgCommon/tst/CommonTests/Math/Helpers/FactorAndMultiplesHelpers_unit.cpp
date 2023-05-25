#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::mathHelper {

TEST(FactorAndMulitplesHelpersTest, IsPrimeWorks) {
    EXPECT_FALSE(isPrime(0));
    EXPECT_FALSE(isPrime(1));
    EXPECT_TRUE(isPrime(2));
    EXPECT_TRUE(isPrime(3));
    EXPECT_FALSE(isPrime(4));
    EXPECT_TRUE(isPrime(5));
    EXPECT_FALSE(isPrime(24));
    EXPECT_TRUE(isPrime(67));
}

TEST(FactorAndMulitplesHelpersTest, IsPowerOfTwoWorks) {
    EXPECT_TRUE(isPowerOfTwo(0));
    EXPECT_TRUE(isPowerOfTwo(1));
    EXPECT_TRUE(isPowerOfTwo(2));
    EXPECT_FALSE(isPowerOfTwo(3));
    EXPECT_TRUE(isPowerOfTwo(4));
    EXPECT_FALSE(isPowerOfTwo(6));
}

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonPowerOf2FactorWorks) {
    EXPECT_EQ(0, getGreatestPowerOf2Factor(0));
    EXPECT_EQ(1, getGreatestPowerOf2Factor(1));
    EXPECT_EQ(2, getGreatestPowerOf2Factor(2));
    EXPECT_EQ(4, getGreatestPowerOf2Factor(4));
    EXPECT_EQ(8, getGreatestPowerOf2Factor(8));
    EXPECT_EQ(16, getGreatestPowerOf2Factor(16));
    EXPECT_EQ(1, getGreatestPowerOf2Factor(5));
    EXPECT_EQ(2, getGreatestPowerOf2Factor(10));
    EXPECT_EQ(4, getGreatestPowerOf2Factor(12));
}

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonFactorWorks) {
    // UnsignedInteger
    EXPECT_EQ(0, getGreatestCommonFactor(0, 0));
    EXPECT_EQ(8, getGreatestCommonFactor(0, 8));
    EXPECT_EQ(8, getGreatestCommonFactor(8, 0));
    EXPECT_EQ(1, getGreatestCommonFactor(1, 8));
    EXPECT_EQ(1, getGreatestCommonFactor(8, 1));
    EXPECT_EQ(1, getGreatestCommonFactor(1, 1));
    EXPECT_EQ(16, getGreatestCommonFactor(16, 32));
    EXPECT_EQ(14, getGreatestCommonFactor(98, 56));
    EXPECT_EQ(1, getGreatestCommonFactor(1234567891, 3));
    EXPECT_EQ(1, getGreatestCommonFactor(3, 1234567891));

    // SignedInteger
    EXPECT_EQ(0, getGreatestCommonFactor<int>(0, 0));    EXPECT_EQ(8, getGreatestCommonFactor(0, -8));
    EXPECT_EQ(8, getGreatestCommonFactor(-8, 0));
    EXPECT_EQ(1, getGreatestCommonFactor(1, -8));
    EXPECT_EQ(1, getGreatestCommonFactor(-8, 1));    EXPECT_EQ(1, getGreatestCommonFactor<int>(1, 1));
    EXPECT_EQ(16, getGreatestCommonFactor(16, -32));
    EXPECT_EQ(16, getGreatestCommonFactor(-16, 32));
    EXPECT_EQ(14, getGreatestCommonFactor(98, -56));
    EXPECT_EQ(14, getGreatestCommonFactor(-98, 56));
    EXPECT_EQ(1, getGreatestCommonFactor(-1234567891, 3));
    EXPECT_EQ(1, getGreatestCommonFactor(3, -1234567891));
}

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonFactorUsingEuclidAlgorithmWorks) {
    // UnsignedInteger
    EXPECT_EQ(0, getGreatestCommonFactorUsingEuclidAlgorithm(0, 0));
    EXPECT_EQ(8, getGreatestCommonFactorUsingEuclidAlgorithm(0, 8));
    EXPECT_EQ(8, getGreatestCommonFactorUsingEuclidAlgorithm(8, 0));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(1, 8));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(8, 1));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(1, 1));
    EXPECT_EQ(16, getGreatestCommonFactorUsingEuclidAlgorithm(16, 32));
    EXPECT_EQ(14, getGreatestCommonFactorUsingEuclidAlgorithm(98, 56));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(1234567891, 3));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(3, 1234567891));

    // SignedInteger
    EXPECT_EQ(0, getGreatestCommonFactorUsingEuclidAlgorithm<int>(0, 0));    EXPECT_EQ(8, getGreatestCommonFactorUsingEuclidAlgorithm(0, -8));
    EXPECT_EQ(8, getGreatestCommonFactorUsingEuclidAlgorithm(-8, 0));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(1, -8));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(-8, 1));    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm<int>(1, 1));
    EXPECT_EQ(16, getGreatestCommonFactorUsingEuclidAlgorithm(16, -32));
    EXPECT_EQ(16, getGreatestCommonFactorUsingEuclidAlgorithm(-16, 32));
    EXPECT_EQ(14, getGreatestCommonFactorUsingEuclidAlgorithm(98, -56));
    EXPECT_EQ(14, getGreatestCommonFactorUsingEuclidAlgorithm(-98, 56));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(-1234567891, 3));
    EXPECT_EQ(1, getGreatestCommonFactorUsingEuclidAlgorithm(3, -1234567891));
}

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonFactorWithLastValuesWorksForUnsignedInteger) {
    using LastValues = pair<int, int>;
    LastValues lastValues{};
    EXPECT_EQ(0, getGreatestCommonFactorWithLastValues(0, 0, lastValues.first, lastValues.second));
    EXPECT_EQ((LastValues{1, 0}), lastValues);
    EXPECT_EQ(1, getGreatestCommonFactorWithLastValues(1, 1, lastValues.first, lastValues.second));
    EXPECT_EQ((LastValues{0, 1}), lastValues);
    EXPECT_EQ(16, getGreatestCommonFactorWithLastValues(16, 32, lastValues.first, lastValues.second));
    EXPECT_EQ((LastValues{1, 0}), lastValues);
    EXPECT_EQ(14, getGreatestCommonFactorWithLastValues(98, 56, lastValues.first, lastValues.second));
    EXPECT_EQ((LastValues{4294967295, 2}), lastValues);
    EXPECT_EQ(1, getGreatestCommonFactorWithLastValues(1234567891, 3, lastValues.first, lastValues.second));
    EXPECT_EQ((LastValues{1, 3883444666}), lastValues);
    EXPECT_EQ(1, getGreatestCommonFactorWithLastValues(3, 1234567891, lastValues.first, lastValues.second));
    EXPECT_EQ((LastValues{3883444666, 1}), lastValues);
}

TEST(FactorAndMulitplesHelpersTest, GetLeastCommonMultipleWorks) {
    EXPECT_EQ(0, getLeastCommonMultiple(0, 0));
    EXPECT_EQ(1, getLeastCommonMultiple(1, 1));
    EXPECT_EQ(256, getLeastCommonMultiple(8, 256));
    EXPECT_EQ(60, getLeastCommonMultiple(15, 20));
    EXPECT_EQ(262144, getLeastCommonMultiple(65536, 262144));
}

TEST(FactorAndMulitplesHelpersTest, GetLeastCommonMultipleUsingEuclidAlgorithmWorks) {
    EXPECT_EQ(0, getLeastCommonMultipleUsingEuclidAlgorithm(0, 0));
    EXPECT_EQ(1, getLeastCommonMultipleUsingEuclidAlgorithm(1, 1));
    EXPECT_EQ(256, getLeastCommonMultipleUsingEuclidAlgorithm(8, 256));
    EXPECT_EQ(60, getLeastCommonMultipleUsingEuclidAlgorithm(15, 20));
    EXPECT_EQ(262144, getLeastCommonMultipleUsingEuclidAlgorithm(65536, 262144));
}

TEST(FactorAndMulitplesHelpersTest, GetLeastCommonMultipleInDoubleWorks) {    EXPECT_DOUBLE_EQ(262144, getLeastCommonMultipleInDouble(65536, 262144));
}

TEST(FactorAndMulitplesHelpersTest, GetNumberOfMultiplesInclusiveWorks) {
    EXPECT_EQ(0, getNumberOfMultiplesInclusive(0, 0));
    EXPECT_EQ(1, getNumberOfMultiplesInclusive(10, 10));
    EXPECT_EQ(1, getNumberOfMultiplesInclusive(5, 9));
    EXPECT_EQ(2, getNumberOfMultiplesInclusive(5, 10));
    EXPECT_EQ(2, getNumberOfMultiplesInclusive(5, 11));
    EXPECT_EQ(0, getNumberOfMultiplesInclusive(10, 0));
    EXPECT_EQ(0, getNumberOfMultiplesInclusive(10, 5));
    EXPECT_EQ(41, getNumberOfMultiplesInclusive(57, 2346));
}

TEST(FactorAndMulitplesHelpersTest, GetMultipleThatIsLessOrEqualWorks) {
    EXPECT_EQ(0, getMultipleThatIsLesserOrEqual(0, 0));
    EXPECT_EQ(10, getMultipleThatIsLesserOrEqual(10, 10));
    EXPECT_EQ(5, getMultipleThatIsLesserOrEqual(5, 9));
    EXPECT_EQ(10, getMultipleThatIsLesserOrEqual(5, 10));
    EXPECT_EQ(10, getMultipleThatIsLesserOrEqual(5, 11));
    EXPECT_EQ(0, getMultipleThatIsLesserOrEqual(0, 10));
    EXPECT_EQ(0, getMultipleThatIsLesserOrEqual(10, 0));
    EXPECT_EQ(0, getMultipleThatIsLesserOrEqual(10, 5));
    EXPECT_EQ(2337, getMultipleThatIsLesserOrEqual(57, 2346));
}

TEST(FactorAndMulitplesHelpersTest, GetMultipleThatIsGreaterOrEqualWorks) {
    EXPECT_EQ(0, getMultipleThatIsGreaterOrEqual(0, 0));
    EXPECT_EQ(10, getMultipleThatIsGreaterOrEqual(10, 10));
    EXPECT_EQ(10, getMultipleThatIsGreaterOrEqual(5, 9));
    EXPECT_EQ(10, getMultipleThatIsGreaterOrEqual(5, 10));
    EXPECT_EQ(15, getMultipleThatIsGreaterOrEqual(5, 11));
    EXPECT_EQ(0, getMultipleThatIsGreaterOrEqual(0, 10));
    EXPECT_EQ(0, getMultipleThatIsGreaterOrEqual(10, 0));
    EXPECT_EQ(10, getMultipleThatIsGreaterOrEqual(10, 5));
    EXPECT_EQ(2394, getMultipleThatIsGreaterOrEqual(57, 2346));
}

TEST(FactorAndMulitplesHelpersTest, GetDifferenceFromGreaterMultipleWorks) {
    EXPECT_EQ(0, getDifferenceFromGreaterMultiple(0, 0));
    EXPECT_EQ(0, getDifferenceFromGreaterMultiple(10, 10));
    EXPECT_EQ(1, getDifferenceFromGreaterMultiple(5, 9));
    EXPECT_EQ(0, getDifferenceFromGreaterMultiple(5, 10));
    EXPECT_EQ(4, getDifferenceFromGreaterMultiple(5, 11));
    EXPECT_EQ(0, getDifferenceFromGreaterMultiple(0, 10));
    EXPECT_EQ(0, getDifferenceFromGreaterMultiple(10, 0));
    EXPECT_EQ(5, getDifferenceFromGreaterMultiple(10, 5));
    EXPECT_EQ(48, getDifferenceFromGreaterMultiple(57, 2346));
}

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonFactorForAlbaNumberWorks) {    EXPECT_EQ(AlbaNumber(0), getGreatestCommonFactor(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_EQ(AlbaNumber(1), getGreatestCommonFactor(AlbaNumber(1), AlbaNumber(1)));
    EXPECT_EQ(
        AlbaNumber::createFraction(1, 12),        getGreatestCommonFactor(AlbaNumber::createFraction(1, 6), AlbaNumber::createFraction(1, 4)));
    EXPECT_EQ(AlbaNumber(1), getGreatestCommonFactor(AlbaNumber(0.33), AlbaNumber::createFraction(1, 4)));
    EXPECT_EQ(
        AlbaNumber::createFraction(1, 4), getGreatestCommonFactor(AlbaNumber(5), AlbaNumber::createFraction(1, 4)));
    EXPECT_EQ(AlbaNumber(3), getGreatestCommonFactor(AlbaNumber(6), AlbaNumber(9)));
    EXPECT_EQ(AlbaNumber(9), getGreatestCommonFactor(AlbaNumber(-36), AlbaNumber(27)));
}

TEST(FactorAndMulitplesHelpersTest, GetLeastCommonMultipleForAlbaNumberWorks) {
    EXPECT_EQ(
        AlbaNumber(3), getLeastCommonMultiple(AlbaNumber::createFraction(3, 2), AlbaNumber::createFraction(1, 3)));
}

}  // namespace alba::mathHelper
