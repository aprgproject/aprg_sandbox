#include <Math/NumberTheory/ChineseRemainderTheorem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(ChineseRemainderTheoremTest, Example1Works)
{
    // x = 3 mod 5
    // x = 4 mod 7
    // x = 2 mod 3

    ChineseRemainderTheorem chineseRemainderTheorem({3U, 4U, 2U}, {5U, 7U, 3U});

    EXPECT_EQ(263U, chineseRemainderTheorem.getSolutionValue());
    EXPECT_EQ(263U, chineseRemainderTheorem.getAnotherSolutionValue(0U));
    EXPECT_EQ(368U, chineseRemainderTheorem.getAnotherSolutionValue(1U));
    EXPECT_EQ(473U, chineseRemainderTheorem.getAnotherSolutionValue(2U));
}

}

}
