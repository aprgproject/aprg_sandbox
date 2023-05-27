#include <BooleanAlgebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace booleanAlgebra {

TEST(SubstitutionOfVariablesToValuesTest, ConstructionWorks) {
    SubstitutionOfVariablesToValues substitution1;
    SubstitutionOfVariablesToValues substitution2{{"x", false}, {"y", true}};
    VariablesToValuesMap variableWithValues{{"x", false}, {"y", true}};
    SubstitutionOfVariablesToValues substitution3{variableWithValues};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(2, substitution2.getSize());
    EXPECT_FALSE(substitution2.getValueForVariable("x"));
    EXPECT_TRUE(substitution2.getValueForVariable("y"));
    EXPECT_EQ(2, substitution3.getSize());
    EXPECT_FALSE(substitution3.getValueForVariable("x"));
    EXPECT_TRUE(substitution2.getValueForVariable("y"));
}
TEST(SubstitutionOfVariablesToValuesTest, IsEmptyWorks) {
    SubstitutionOfVariablesToValues substitution1;
    SubstitutionOfVariablesToValues substitution2({{"x", false}, {"y", true}});
    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfVariablesToValuesTest, IsVariableFoundWorks) {
    SubstitutionOfVariablesToValues substitution({{"x", false}, {"y", true}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_TRUE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, GetSizeWorks) {
    SubstitutionOfVariablesToValues substitution1;
    SubstitutionOfVariablesToValues substitution2({{"x", false}, {"y", true}});

    EXPECT_EQ(0, substitution1.getSize());
    EXPECT_EQ(2, substitution2.getSize());
}

TEST(SubstitutionOfVariablesToValuesTest, GetValueForVariableWorks) {    SubstitutionOfVariablesToValues substitution({{"x", false}, {"y", true}});

    EXPECT_FALSE(substitution.getValueForVariable("x"));
    EXPECT_TRUE(substitution.getValueForVariable("y"));    EXPECT_FALSE(substitution.getValueForVariable("a"));
    EXPECT_FALSE(substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnVariableTerm) {
    SubstitutionOfVariablesToValues substitution({{"x", true}});
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("x");
    VariableTerm variableTerm3("y");

    Term verifyTerm1(substitution.performSubstitutionTo(variableTerm1));
    Term verifyTerm2(substitution.performSubstitutionTo(variableTerm2));
    Term verifyTerm3(substitution.performSubstitutionTo(variableTerm3));

    Term expectTerm1(VariableTerm{});
    Term expectTerm2(true);
    Term expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfVariablesToValues substitution({{"x", false}, {"y", true}});
    Expression expression1;
    Expression expression2(createExpressionIfPossible({"x", "&", "y"}));

    Term verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term expectTerm1;
    Term expectTerm2(false);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToValuesTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfVariablesToValues substitution({{"x", false}, {"y", true}});
    Term term1;
    Term term2("x");
    Term term5(createExpressionIfPossible({"x", "&", "y"}));
    Term term6(true);

    Term verifyTerm1(substitution.performSubstitutionTo(term1));
    Term verifyTerm2(substitution.performSubstitutionTo(term2));
    Term verifyTerm5(substitution.performSubstitutionTo(term5));
    Term verifyTerm6(substitution.performSubstitutionTo(term6));

    Term expectTerm1;
    Term expectTerm2(false);
    Term expectTerm5(false);
    Term expectTerm6(true);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm5, verifyTerm5);
    EXPECT_EQ(expectTerm6, verifyTerm6);
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValuesWorksUsingInitializerList) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariablesWithValues({{"x", false}, {"y", true}});

    EXPECT_FALSE(substitution.getValueForVariable("x"));
    EXPECT_TRUE(substitution.getValueForVariable("y"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
    EXPECT_FALSE(substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValuesWorksUsingMap) {
    SubstitutionOfVariablesToValues substitution;
    VariablesToValuesMap variablesWithValues;
    variablesWithValues.emplace("x", false);
    variablesWithValues.emplace("y", true);

    substitution.putVariablesWithValues(variablesWithValues);

    EXPECT_FALSE(substitution.getValueForVariable("x"));
    EXPECT_TRUE(substitution.getValueForVariable("y"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
    EXPECT_FALSE(substitution.getValueForVariable("b"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValueWorks) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariableWithValue("x", true);

    EXPECT_TRUE(substitution.getValueForVariable("x"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
}

TEST(SubstitutionOfVariablesToValuesTest, PutVariablesWithValueWorksWithSavingTheLastValue) {
    SubstitutionOfVariablesToValues substitution;

    substitution.putVariableWithValue("x", true);
    substitution.putVariableWithValue("x", false);

    EXPECT_FALSE(substitution.getValueForVariable("x"));
    EXPECT_FALSE(substitution.getValueForVariable("a"));
}

}  // namespace booleanAlgebra

}  // namespace alba
