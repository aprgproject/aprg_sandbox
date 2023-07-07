#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaBitValueUtilitiesTest, IsPowerOfTwoWorks) {
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(0U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(1U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(2U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(3U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(4U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(5U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(6U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(7U));
}

TEST(AlbaBitValueUtilitiesTest, IsEvenParityWorks) {
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isEvenParity(0U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isEvenParity(1U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isEvenParity(2U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isEvenParity(3U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isEvenParity(4U));
}

TEST(AlbaBitValueUtilitiesTest, AreAllOnesStartingFromTheFirstOneWorks) {
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::areAllOnesStartingFromTheFirstOne(0U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::areAllOnesStartingFromTheFirstOne(1U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::areAllOnesStartingFromTheFirstOne(2U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::areAllOnesStartingFromTheFirstOne(3U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::areAllOnesStartingFromTheFirstOne(4U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::areAllOnesStartingFromTheFirstOne(5U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::areAllOnesStartingFromTheFirstOne(6U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::areAllOnesStartingFromTheFirstOne(7U));
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfBitsWorks) {
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint8_t>::getNumberOfBits());
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint16_t>::getNumberOfBits());
    EXPECT_EQ(32U, AlbaBitValueUtilities<uint32_t>::getNumberOfBits());
    EXPECT_EQ(64U, AlbaBitValueUtilities<uint64_t>::getNumberOfBits());
    EXPECT_EQ(8U, AlbaBitValueUtilities<int8_t>::getNumberOfBits());
    EXPECT_EQ(16U, AlbaBitValueUtilities<int16_t>::getNumberOfBits());
    EXPECT_EQ(32U, AlbaBitValueUtilities<int32_t>::getNumberOfBits());
    EXPECT_EQ(64U, AlbaBitValueUtilities<int64_t>::getNumberOfBits());
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfOnesWorks) {
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getNumberOfOnes(0xA1U));
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint16_t>::getNumberOfOnes(0xA1BAU));
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint32_t>::getNumberOfOnes(0xA1BA'A1BAU));
    EXPECT_EQ(32U, AlbaBitValueUtilities<uint64_t>::getNumberOfOnes(0xA1BA'A1BA'A1BA'A1BAU));
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfConsecutiveZerosFromMsbWorks) {
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromMsb(0x80U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromMsb(0x10U));
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromMsb(0x01U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromMsb(0x8000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromMsb(0x1000U));
    EXPECT_EQ(15U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromMsb(0x0001U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromMsb(0x8000'0000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromMsb(0x1000'0000U));
    EXPECT_EQ(31U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromMsb(0x0000'0001U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromMsb(0x8000'0000'0000'0000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromMsb(0x1000'0000'0000'0000U));
    EXPECT_EQ(63U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromMsb(0x0000'0000'0000'0001U));
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfConsecutiveZerosFromLsbWorks) {
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromLsb(0x80U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromLsb(0x08U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromLsb(0x01U));
    EXPECT_EQ(15U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromLsb(0x8000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromLsb(0x0008U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromLsb(0x0001U));
    EXPECT_EQ(31U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromLsb(0x8000'0000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromLsb(0x0000'0008U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromLsb(0x0000'0001U));
    EXPECT_EQ(63U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromLsb(0x8000'0000'0000'0000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromLsb(0x0000'0000'0000'0008U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromLsb(0x0000'0000'0000'0001U));
}

TEST(AlbaBitValueUtilitiesTest, GetHammingDistanceWorks) {
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA1U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xBAU));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xBAU, 0xA1U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA0U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA1U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA3U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA7U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xAFU));
}

TEST(AlbaBitValueUtilitiesTest, GenerationOfOnesWorks) {
    const size_t input = 2;

    EXPECT_EQ(0x00000003U, AlbaBitValueUtilities<uint32_t>::generateOnesWithNumberOfBits(input));
}

TEST(AlbaBitValueUtilitiesTest, GetAllOnesWorks) {
    EXPECT_EQ(0xFFU, AlbaBitValueUtilities<uint8_t>::getAllOnes());
    EXPECT_EQ(0xFFFFU, AlbaBitValueUtilities<uint16_t>::getAllOnes());
    EXPECT_EQ(0xFFFFFFFFU, AlbaBitValueUtilities<uint32_t>::getAllOnes());
    EXPECT_EQ(0xFFFFFFFFFFFFFFFFU, AlbaBitValueUtilities<uint64_t>::getAllOnes());
}

TEST(AlbaBitValueUtilitiesTest, GetAbsoluteValueWorks) {
    // EXPECT_EQ(10, AlbaBitValueUtilities<uint8_t>::getAbsoluteValue(10)); // static assert should happen
    EXPECT_EQ(10, AlbaBitValueUtilities<int8_t>::getAbsoluteValue(10));
    EXPECT_EQ(0, AlbaBitValueUtilities<int8_t>::getAbsoluteValue(0));
    EXPECT_EQ(10, AlbaBitValueUtilities<int8_t>::getAbsoluteValue(-10));
}

TEST(AlbaBitValueUtilitiesTest, GetSignWorks) {
    // EXPECT_EQ(1, AlbaBitValueUtilities<uint8_t>::getSign(10)); // static assert should happen
    EXPECT_EQ(1, AlbaBitValueUtilities<int8_t>::getSign(10));
    EXPECT_EQ(0, AlbaBitValueUtilities<int8_t>::getSign(0));
    EXPECT_EQ(-1, AlbaBitValueUtilities<int8_t>::getSign(-10));
}

TEST(AlbaBitValueUtilitiesTest, Get2ToThePowerOfWorks) {
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint8_t>::get2ToThePowerOf(4U));
    EXPECT_EQ(1024U, AlbaBitValueUtilities<uint16_t>::get2ToThePowerOf(10U));
    EXPECT_EQ(4194304U, AlbaBitValueUtilities<uint32_t>::get2ToThePowerOf(22U));
}

TEST(AlbaBitValueUtilitiesTest, GetLogarithmWithBase2OfWorks) {
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getLogarithmWithBase2Of(4U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getLogarithmWithBase2Of(7U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint16_t>::getLogarithmWithBase2Of(8U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint16_t>::getLogarithmWithBase2Of(10U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint16_t>::getLogarithmWithBase2Of(16U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint32_t>::getLogarithmWithBase2Of(22U));
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint32_t>::getLogarithmWithBase2Of(123456U));
}

TEST(AlbaBitValueUtilitiesTest, GetCeilOfLogarithmWithBase2OfWorks) {
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getCeilOfLogarithmWithBase2Of(4U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getCeilOfLogarithmWithBase2Of(7U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint16_t>::getCeilOfLogarithmWithBase2Of(8U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint16_t>::getCeilOfLogarithmWithBase2Of(10U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint16_t>::getCeilOfLogarithmWithBase2Of(16U));
    EXPECT_EQ(5U, AlbaBitValueUtilities<uint32_t>::getCeilOfLogarithmWithBase2Of(22U));
    EXPECT_EQ(17U, AlbaBitValueUtilities<uint32_t>::getCeilOfLogarithmWithBase2Of(123456U));
}

TEST(AlbaBitValueUtilitiesTest, GetOnesComplementWorks) {
    EXPECT_EQ(0x5EU, AlbaBitValueUtilities<uint8_t>::getOnesComplement(0xA1U));
    EXPECT_EQ(0x5E45U, AlbaBitValueUtilities<uint16_t>::getOnesComplement(0xA1BAU));
    EXPECT_EQ(0x5E455E45U, AlbaBitValueUtilities<uint32_t>::getOnesComplement(0xA1BA'A1BAU));
    EXPECT_EQ(0x5E455E455E455E45U, AlbaBitValueUtilities<uint64_t>::getOnesComplement(0xA1BA'A1BA'A1BA'A1BAU));
}

TEST(AlbaBitValueUtilitiesTest, GetTwosComplementWorks) {
    EXPECT_EQ(0x5FU, AlbaBitValueUtilities<uint8_t>::getTwosComplement(0xA1U));
    EXPECT_EQ(0x5E46U, AlbaBitValueUtilities<uint16_t>::getTwosComplement(0xA1BAU));
    EXPECT_EQ(0x5E455E46U, AlbaBitValueUtilities<uint32_t>::getTwosComplement(0xA1BA'A1BAU));
    EXPECT_EQ(0x5E455E455E455E46U, AlbaBitValueUtilities<uint64_t>::getTwosComplement(0xA1BA'A1BA'A1BA'A1BAU));
}

TEST(AlbaBitValueUtilitiesTest, GetGreatestPowerOf2FactorWorks) {
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getGreatestPowerOf2Factor(12U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint16_t>::getGreatestPowerOf2Factor(1234U));
    EXPECT_EQ(64U, AlbaBitValueUtilities<uint32_t>::getGreatestPowerOf2Factor(123456U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint64_t>::getGreatestPowerOf2Factor(12345678901234U));
}

TEST(AlbaBitValueUtilitiesTest, GetValueWithLastBitOneAsZeroWorks) {
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(0U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(1U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(2U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(3U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(4U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(5U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(6U));
    EXPECT_EQ(6U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(7U));
    EXPECT_EQ(0xA8U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitOneAsZero(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetValueWithLastBitZeroAsOneWorks) {
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(0U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(1U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(2U));
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(3U));
    EXPECT_EQ(5U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(4U));
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(5U));
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(6U));
    EXPECT_EQ(15U, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(7U));
    EXPECT_EQ(0xABU, AlbaBitValueUtilities<uint8_t>::getValueWithLastBitZeroAsOne(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetValueWithTrailingOnesAsZerosWorks) {
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(0U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(1U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(2U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(3U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(4U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(5U));
    EXPECT_EQ(6U, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(6U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(7U));
    EXPECT_EQ(0xAAU, AlbaBitValueUtilities<uint8_t>::getValueWithTrailingOnesAsZeros(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetValueWithASingleBitOneBeforeTrailingOnesWorks) {
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(0U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(1U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(2U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(3U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(4U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(5U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(6U));
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(7U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitOneBeforeTrailingOnes(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetValueWithASingleBitZeroBeforeTrailingZerosWorks) {
    EXPECT_EQ(0xFFU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(0U));
    EXPECT_EQ(0xFEU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(1U));
    EXPECT_EQ(0xFDU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(2U));
    EXPECT_EQ(0xFEU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(3U));
    EXPECT_EQ(0xFBU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(4U));
    EXPECT_EQ(0xFEU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(5U));
    EXPECT_EQ(0xFDU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(6U));
    EXPECT_EQ(0xFEU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(7U));
    EXPECT_EQ(0xFDU, AlbaBitValueUtilities<uint8_t>::getValueWithASingleBitZeroBeforeTrailingZeros(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetOnlyTrailingOnesAtTrailingZerosWorks) {
    EXPECT_EQ(0xFFU, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(0U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(1U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(2U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(3U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(4U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(5U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(6U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(7U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtTrailingZeros(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetOnlyTrailingZerosAtTrailingOnesWorks) {
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(0U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(1U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(2U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(3U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(4U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(5U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(6U));
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(7U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingZerosAtTrailingOnes(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetLastBitOneOnlyWorks) {
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(0U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(1U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(2U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(3U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(4U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(5U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(6U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(7U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getLastBitOneOnly(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetOnlyTrailingOnesAtLastBitOneWorks) {
    EXPECT_EQ(0xFFU, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(0U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(1U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(2U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(3U));
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(4U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(5U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(6U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(7U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitOne(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetOnlyTrailingOnesAtLastBitZeroWorks) {
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(0U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(1U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(2U));
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(3U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(4U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(5U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(6U));
    EXPECT_EQ(15U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(7U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getOnlyTrailingOnesAtLastBitZero(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, RoundDownAtWorks) {
    EXPECT_EQ(0xA1U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 0U));
    EXPECT_EQ(0xA0U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 1U));
    EXPECT_EQ(0xA0U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 2U));
    EXPECT_EQ(0xA0U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 3U));
    EXPECT_EQ(0xA0U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 4U));
    EXPECT_EQ(0xA0U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 5U));
    EXPECT_EQ(0x80U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 6U));
    EXPECT_EQ(0x80U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 7U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::roundDownAt(0xA1U, 8U));
}

TEST(AlbaBitValueUtilitiesTest, RoundUpAtWorks) {
    EXPECT_EQ(0xA1U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 0U));
    EXPECT_EQ(0xA2U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 1U));
    EXPECT_EQ(0xA4U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 2U));
    EXPECT_EQ(0xA8U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 3U));
    EXPECT_EQ(0xB0U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 4U));
    EXPECT_EQ(0xC0U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 5U));
    EXPECT_EQ(0xC0U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 6U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 7U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::roundUpAt(0xA1U, 8U));
}

TEST(AlbaBitValueUtilitiesTest, RoundDownToAPowerOf2Works) {
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(0U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(1U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(2U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(3U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(4U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(5U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(6U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(7U));
    EXPECT_EQ(0x80U, AlbaBitValueUtilities<uint8_t>::roundDownToAPowerOf2(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, RoundUpToAPowerOf2Works) {
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(0U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(1U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(2U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(3U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(4U));
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(5U));
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(6U));
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(7U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::roundUpToAPowerOf2(0xAAU));
}

TEST(AlbaBitValueUtilitiesTest, GetTwoValuesInACycleWorks) {
    EXPECT_EQ(30U, AlbaBitValueUtilities<uint8_t>::getTwoValuesInACycle(5U, 5U, 30U));
    EXPECT_EQ(5U, AlbaBitValueUtilities<uint8_t>::getTwoValuesInACycle(30U, 5U, 30U));
}

TEST(AlbaBitValueUtilitiesTest, SwapWorks) {
    uint8_t value1 = 0xA1U;
    uint8_t value2 = 0xBAU;

    AlbaBitValueUtilities<uint8_t>::swap(value1, value2);

    EXPECT_EQ(0xBAU, value1);
    EXPECT_EQ(0xA1U, value2);
}

}  // namespace alba
