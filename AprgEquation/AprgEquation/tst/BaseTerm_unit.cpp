#include <BaseTerm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(BaseTermTest, ConstructionWorks)
{
    BaseTerm();
}

TEST(BaseTermTest, GetDisplayableStringWorks)
{
    BaseTerm baseTerm;

    EXPECT_EQ("[BaseTerm]", baseTerm.getDisplayableString());
}

}

}
