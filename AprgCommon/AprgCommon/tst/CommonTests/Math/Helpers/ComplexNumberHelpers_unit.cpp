#include <Common/Math/Helpers/ComplexNumberHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace mathHelper {

TEST(ComplexNumberHelpersTest, CreateNumberFromComplexNumberWorks) {
    AlbaComplexNumber<double> complexNumberWithDouble(3.5, 4.5);

    AlbaNumber expectedNumber(AlbaNumber::createComplexNumber(3.5, 4.5));
    EXPECT_EQ(expectedNumber, createNumberFromComplexNumber(complexNumberWithDouble));
}

TEST(ComplexNumberHelpersTest, SaveToComplexNumberDataWorks) {
    AlbaComplexNumber<float> complexNumber(3.5, 4.5);
    AlbaNumber::ComplexNumberData complexData{};

    saveToComplexNumberData(complexData, complexNumber);

    AlbaNumber::ComplexNumberData expectedComplexData{3.5, 4.5};
    EXPECT_FLOAT_EQ(expectedComplexData.realPart, complexData.realPart);
    EXPECT_FLOAT_EQ(expectedComplexData.imaginaryPart, complexData.imaginaryPart);
}

}  // namespace mathHelper

}  // namespace alba
