#include <BooleanAlgebra/Functions/CommonFunctionLibrary.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace booleanAlgebra {

namespace {
Terms allFalseTerms{false, false, false};
Terms allTrueTerms{true, true, true};
Terms oneTrueTerm{false, true, "x"};
Terms twoTrueTerms{false, true, "x", true};

UnaryBooleanFunction isExactlyTrue = [](Term const& term) { return term == Term(true); };
}  // namespace

TEST(CommonFunctionLibraryTest, PredicateCanBeCreatedAndWorks) {
    EXPECT_FALSE(isExactlyTrue(Term(false)));
    EXPECT_TRUE(isExactlyTrue(Term(true)));
    EXPECT_FALSE(isExactlyTrue(Term("x")));
}

TEST(CommonFunctionLibraryTest, GetNegationWorks) {
    EXPECT_EQ(Term(true), getNegation(Term(false)));
    EXPECT_EQ(Term(false), getNegation(Term(true)));
    Term expectedTerm("x'");
    EXPECT_EQ(expectedTerm, getNegation(Term("x")));
}

TEST(CommonFunctionLibraryTest, GetConjunctionWorks) {
    EXPECT_EQ(Term(false), getConjunction(Term(false), Term(false)));
    EXPECT_EQ(Term(false), getConjunction(Term(false), Term(true)));
    EXPECT_EQ(Term(false), getConjunction(Term(true), Term(false)));
    EXPECT_EQ(Term(true), getConjunction(Term(true), Term(true)));
    Term expectedTerm(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(expectedTerm, getConjunction(Term("x"), Term("y")));
}

TEST(CommonFunctionLibraryTest, GetInclusiveDisjunctionWorks) {
    EXPECT_EQ(Term(false), getInclusiveDisjunction(Term(false), Term(false)));
    EXPECT_EQ(Term(true), getInclusiveDisjunction(Term(false), Term(true)));
    EXPECT_EQ(Term(true), getInclusiveDisjunction(Term(true), Term(false)));
    EXPECT_EQ(Term(true), getInclusiveDisjunction(Term(true), Term(true)));
    Term expectedTerm(createExpressionIfPossible({"x", "|", "y"}));
    EXPECT_EQ(expectedTerm, getInclusiveDisjunction(Term("x"), Term("y")));
}

TEST(CommonFunctionLibraryTest, GetExclusiveDisjunctionWorks) {
    EXPECT_EQ(Term(false), getExclusiveDisjunction(Term(false), Term(false)));
    EXPECT_EQ(Term(true), getExclusiveDisjunction(Term(false), Term(true)));
    EXPECT_EQ(Term(true), getExclusiveDisjunction(Term(true), Term(false)));
    EXPECT_EQ(Term(false), getExclusiveDisjunction(Term(true), Term(true)));
    Term expectedTerm(createExpressionIfPossible({"(", "x", "&", "y'", ")", "|", "(", "x'", "&", "y", ")"}));
    EXPECT_EQ(expectedTerm, getExclusiveDisjunction(Term("x"), Term("y")));
}

TEST(CommonFunctionLibraryTest, GetImplicationWorks) {
    EXPECT_EQ(Term(true), getImplication(Term(false), Term(false)));
    EXPECT_EQ(Term(true), getImplication(Term(false), Term(true)));
    EXPECT_EQ(Term(false), getImplication(Term(true), Term(false)));
    EXPECT_EQ(Term(true), getImplication(Term(true), Term(true)));
    Term expectedTerm(createExpressionIfPossible({"x'", "|", "y"}));
    EXPECT_EQ(expectedTerm, getImplication(Term("x"), Term("y")));
}

TEST(CommonFunctionLibraryTest, GetEquivalenceWorks) {
    EXPECT_EQ(Term(true), getEquivalence(Term(false), Term(false)));
    EXPECT_EQ(Term(false), getEquivalence(Term(false), Term(true)));
    EXPECT_EQ(Term(false), getEquivalence(Term(true), Term(false)));
    EXPECT_EQ(Term(true), getEquivalence(Term(true), Term(true)));
    Term expectedTerm(createExpressionIfPossible({"(", "x", "&", "y", ")", "|", "(", "x'", "&", "y'", ")"}));
    EXPECT_EQ(expectedTerm, getEquivalence(Term("x"), Term("y")));
}

TEST(CommonFunctionLibraryTest, GetUniversalQuantificationWorks) {
    EXPECT_EQ(Term(false), getUniversalQuantification(allFalseTerms, isExactlyTrue));
    EXPECT_EQ(Term(true), getUniversalQuantification(allTrueTerms, isExactlyTrue));
    EXPECT_EQ(Term(false), getUniversalQuantification(oneTrueTerm, isExactlyTrue));
    EXPECT_EQ(Term(false), getUniversalQuantification(twoTrueTerms, isExactlyTrue));
}

TEST(CommonFunctionLibraryTest, GetExistentialQuantificationWorks) {
    EXPECT_EQ(Term(false), getExistentialQuantification(allFalseTerms, isExactlyTrue));
    EXPECT_EQ(Term(true), getExistentialQuantification(allTrueTerms, isExactlyTrue));
    EXPECT_EQ(Term(true), getExistentialQuantification(oneTrueTerm, isExactlyTrue));
    EXPECT_EQ(Term(true), getExistentialQuantification(twoTrueTerms, isExactlyTrue));
}

TEST(CommonFunctionLibraryTest, GetUniquenessQuantificationWorks) {
    EXPECT_EQ(Term(false), getUniquenessQuantification(allFalseTerms, isExactlyTrue));
    EXPECT_EQ(Term(false), getUniquenessQuantification(allTrueTerms, isExactlyTrue));
    EXPECT_EQ(Term(true), getUniquenessQuantification(oneTrueTerm, isExactlyTrue));
    EXPECT_EQ(Term(false), getUniquenessQuantification(twoTrueTerms, isExactlyTrue));
}

TEST(CommonFunctionLibraryTest, GetTautologyWorks) {
    UnaryBooleanFunction tautologyToTest(getTautology());

    EXPECT_EQ(Term(true), tautologyToTest(Term(false)));
    EXPECT_EQ(Term(true), tautologyToTest(Term(true)));
    EXPECT_EQ(Term(true), tautologyToTest(Term("x")));
}

TEST(CommonFunctionLibraryTest, GetContradictionWorks) {
    UnaryBooleanFunction contradictionToTest(getContradiction());

    EXPECT_EQ(Term(false), contradictionToTest(Term(false)));
    EXPECT_EQ(Term(false), contradictionToTest(Term(true)));
    EXPECT_EQ(Term(false), contradictionToTest(Term("x")));
}

}  // namespace booleanAlgebra

}  // namespace alba
