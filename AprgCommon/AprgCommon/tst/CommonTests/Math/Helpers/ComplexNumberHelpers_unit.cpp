#include <Common/Math/Helpers/ComplexNumberHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(AlbaMathHelperTest, CreateComplexNumberFromDataWorks)
{
    AlbaNumber::ComplexNumberData complexData{3.5, 4.5};

    AlbaComplexNumber<float> expectedComplexNumber(3.5, 4.5);
    EXPECT_EQ(expectedComplexNumber, createComplexNumberFromData(complexData));
}

}

}
