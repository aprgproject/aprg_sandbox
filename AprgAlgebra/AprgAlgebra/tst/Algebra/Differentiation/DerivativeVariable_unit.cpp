#include <Algebra/Differentiation/DerivativeVariable.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(DerivativeVariableTest, ConstructionUsingParameterWorks)
{
    DerivativeVariable derivativeVariable(2, "x", "y");

    EXPECT_TRUE(derivativeVariable.isValid());
    EXPECT_EQ(2U, derivativeVariable.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariable.getBaseVariable());
    EXPECT_EQ("y", derivativeVariable.getDependentVariable());
}

TEST(DerivativeVariableTest, ConstructionUsingLeibnizNotationWorks_WithOneCharacterVariables)
{
    DerivativeVariable derivativeVariable("d[y]/d[x]");

    EXPECT_TRUE(derivativeVariable.isValid());
    EXPECT_EQ(1U, derivativeVariable.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariable.getBaseVariable());
    EXPECT_EQ("y", derivativeVariable.getDependentVariable());
}

TEST(DerivativeVariableTest, ConstructionUsingLeibnizNotationWorks_WithMultipleCharacterVariables)
{
    DerivativeVariable derivativeVariable("d[distance]/d[time]");

    EXPECT_TRUE(derivativeVariable.isValid());
    EXPECT_EQ(1U, derivativeVariable.getDifferentiationLevel());
    EXPECT_EQ("time", derivativeVariable.getBaseVariable());
    EXPECT_EQ("distance", derivativeVariable.getDependentVariable());
}

TEST(DerivativeVariableTest, ConstructionUsingLeibnizNotationWorks_WithOneCharacterVariablesAndMultipleNumbers)
{
    DerivativeVariable derivativeVariable("d32[y]/d[x]32");

    EXPECT_TRUE(derivativeVariable.isValid());
    EXPECT_EQ(32U, derivativeVariable.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariable.getBaseVariable());
    EXPECT_EQ("y", derivativeVariable.getDependentVariable());
}

TEST(DerivativeVariableTest, ConstructionUsingLeibnizNotationWorks_WithMultipleCharacterVariablesAndMultipleNumbers)
{
    DerivativeVariable derivativeVariable("d175[distance]/d[time]175");

    EXPECT_TRUE(derivativeVariable.isValid());
    EXPECT_EQ(175U, derivativeVariable.getDifferentiationLevel());
    EXPECT_EQ("time", derivativeVariable.getBaseVariable());
    EXPECT_EQ("distance", derivativeVariable.getDependentVariable());
}

TEST(DerivativeVariableTest, ConstructionUsingLeibnizNotationWorks_WithInvalidFormatResultsToInvalid)
{
    DerivativeVariable derivativeVariable("oisuadhfh");

    EXPECT_FALSE(derivativeVariable.isValid());
}

TEST(DerivativeVariableTest, ConstructionUsingLeibnizNotationWorks_WithNotEqualNumbersResultsToInvalid)
{
    DerivativeVariable derivativeVariable("d175[distance]/d[time]471");

    EXPECT_FALSE(derivativeVariable.isValid());
}

TEST(DerivativeVariableTest, GetNameInLeibnizNotationWorksWhenDifferentiationLevelIsOne)
{
    DerivativeVariable derivativeVariable(1, "time", "volume");

    EXPECT_EQ("d[volume]/d[time]", derivativeVariable.getNameInLeibnizNotation());
}

TEST(DerivativeVariableTest, GetNameInLeibnizNotationWorksWhenDifferentiationLevelIsNotOne)
{
    DerivativeVariable derivativeVariable(46, "time", "volume");

    EXPECT_EQ("d46[volume]/d[time]46", derivativeVariable.getNameInLeibnizNotation());
}

}

}
