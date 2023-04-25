#include <Algebra/Differentiation/DerivativeVariableName.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

TEST(DerivativeVariableNameTest, ConstructionUsingParameterWorks) {
    DerivativeVariableName derivativeVariableName(2, "x", "y");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(2U, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("y", derivativeVariableName.getDependentVariable());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationWorks_WithOneCharacterVariables) {
    DerivativeVariableName derivativeVariableName("d[y]/d[x]");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(1U, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("y", derivativeVariableName.getDependentVariable());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationWorks_WithMultipleCharacterVariables) {
    DerivativeVariableName derivativeVariableName("d[distance]/d[time]");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(1U, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("time", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("distance", derivativeVariableName.getDependentVariable());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationWorks_WithOneCharacterVariablesAndMultipleNumbers) {
    DerivativeVariableName derivativeVariableName("d32[y]/d[x]32");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(32U, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("x", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("y", derivativeVariableName.getDependentVariable());
}

TEST(
    DerivativeVariableNameTest,
    ConstructionUsingLeibnizNotationWorks_WithMultipleCharacterVariablesAndMultipleNumbers) {
    DerivativeVariableName derivativeVariableName("d175[distance]/d[time]175");

    EXPECT_TRUE(derivativeVariableName.isValid());
    EXPECT_EQ(175U, derivativeVariableName.getDifferentiationLevel());
    EXPECT_EQ("time", derivativeVariableName.getBaseVariable());
    EXPECT_EQ("distance", derivativeVariableName.getDependentVariable());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationWorks_WithInvalidFormatResultsToInvalid) {
    DerivativeVariableName derivativeVariableName("oisuadhfh");

    EXPECT_FALSE(derivativeVariableName.isValid());
}

TEST(DerivativeVariableNameTest, ConstructionUsingLeibnizNotationWorks_WithNotEqualNumbersResultsToInvalid) {
    DerivativeVariableName derivativeVariableName("d175[distance]/d[time]471");

    EXPECT_FALSE(derivativeVariableName.isValid());
}

TEST(DerivativeVariableNameTest, GetNameInLeibnizNotationWorksWhenDifferentiationLevelIsOne) {
    DerivativeVariableName derivativeVariableName(1, "time", "volume");

    EXPECT_EQ("d[volume]/d[time]", derivativeVariableName.getNameInLeibnizNotation());
}

TEST(DerivativeVariableNameTest, GetNameInLeibnizNotationWorksWhenDifferentiationLevelIsNotOne) {
    DerivativeVariableName derivativeVariableName(46, "time", "volume");

    EXPECT_EQ("d46[volume]/d[time]46", derivativeVariableName.getNameInLeibnizNotation());
}

}  // namespace algebra

}  // namespace alba
