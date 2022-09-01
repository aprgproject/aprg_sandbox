#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/Math/Helpers/ConversionHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(AlbaMathHelperTest, ConvertRadiansToDegreesWorks)
{
    EXPECT_DOUBLE_EQ(180, convertRadiansToDegrees(getPi()));
    EXPECT_DOUBLE_EQ(572.95779513082323, convertRadiansToDegrees(10));
}

TEST(AlbaMathHelperTest, ConvertDegreesToRadiansWorks)
{
    EXPECT_DOUBLE_EQ(getPi(), convertDegreesToRadians(180));
    EXPECT_DOUBLE_EQ(17.191493132144146, convertDegreesToRadians(985));
}

}

}
