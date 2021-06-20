#include <Equation/Constructs/SubstitutionOfVariablesToValues.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba{

namespace equation
{

TEST(SubstitutionOfVariablesToValuesTest, ConstructionWorks)
{
    SubstitutionOfVariablesToValues substitution1({{"x", 1}, {"y", 2}});
    VariablesToValuesMap variableWithValues{{"x", 1}, {"y", 2}};
    SubstitutionOfVariablesToValues substitution2(variableWithValues);
}

TEST(SubstitutionOfVariablesToValuesTest, IsVariableFoundWorks)
{
    SubstitutionOfVariablesToValues substitution({{"x", 1}, {"y", 2}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_TRUE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, GetValueForVariableWorks)
{
    SubstitutionOfVariablesToValues substitution({{"x", 1}, {"y", 2}});

    EXPECT_EQ(AlbaNumber(1), substitution.getValueForVariable("x"));
    EXPECT_EQ(AlbaNumber(2), substitution.getValueForVariable("y"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("a"));
    EXPECT_EQ(AlbaNumber(0), substitution.getValueForVariable("b"));
}

}

}
