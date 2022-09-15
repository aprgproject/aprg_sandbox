#include <Math/Combinatorics/CatalanNumbers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(CatalanNumbersTest, GetCatalanNumberWorks)
{
    EXPECT_EQ(1U, getCatalanNumber(0U));
    EXPECT_EQ(1U, getCatalanNumber(1U));
    EXPECT_EQ(2U, getCatalanNumber(2U));
    EXPECT_EQ(5U, getCatalanNumber(3U));
    EXPECT_EQ(14U, getCatalanNumber(4U));
    EXPECT_EQ(42U, getCatalanNumber(5U));
    EXPECT_EQ(16796U, getCatalanNumber(10U));
    EXPECT_EQ(9694845U, getCatalanNumber(15U));
    EXPECT_EQ(129644790U, getCatalanNumber(17U));
}

}

}
