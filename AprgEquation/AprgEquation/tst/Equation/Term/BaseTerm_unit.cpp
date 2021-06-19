#include <Equation/Term/BaseTerm.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace equation
{

TEST(BaseTermTest, ConstructionWorks)
{
    BaseTerm();
}

TEST(BaseTermTest, GetDisplayableStringWorks)
{
    BaseTerm baseTerm;

    EXPECT_EQ("[BaseTermDisplayableString]", baseTerm.getDisplayableString());
}

TEST(BaseTermTest, GetDebugStringWorks)
{
    BaseTerm baseTerm;

    EXPECT_EQ("[BaseTermDebugString]", baseTerm.getDebugString());
}

}

}
