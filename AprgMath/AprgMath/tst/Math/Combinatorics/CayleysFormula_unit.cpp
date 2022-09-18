#include <Math/Combinatorics/CayleysFormula.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(CayleysFormulaTest, GetNumberOfLabeledTreesWorks)
{
    EXPECT_EQ(0U, getNumberOfLabeledTreesUsingCayleysFormula(0U));
    EXPECT_EQ(0U, getNumberOfLabeledTreesUsingCayleysFormula(1U));
    EXPECT_EQ(1U, getNumberOfLabeledTreesUsingCayleysFormula(2U));
    EXPECT_EQ(3U, getNumberOfLabeledTreesUsingCayleysFormula(3U));
    EXPECT_EQ(16U, getNumberOfLabeledTreesUsingCayleysFormula(4U));
    EXPECT_EQ(125U, getNumberOfLabeledTreesUsingCayleysFormula(5U));
    EXPECT_EQ(100000000U, getNumberOfLabeledTreesUsingCayleysFormula(10U));
    EXPECT_EQ(61917364224U, getNumberOfLabeledTreesUsingCayleysFormula(12U));
}

}

}
