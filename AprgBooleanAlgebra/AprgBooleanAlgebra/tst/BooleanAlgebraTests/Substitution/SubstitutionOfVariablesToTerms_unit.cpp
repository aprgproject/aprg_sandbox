#include <BooleanAlgebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace booleanAlgebra {

TEST(SubstitutionOfVariablesToTermsTest, ConstructionWorks) {
    SubstitutionOfVariablesToTerms substitution1;
    SubstitutionOfVariablesToTerms substitution2{{"x", "y"}};
    VariablesToTermsMap variableWithExpressions{{"x", "y"}};
    SubstitutionOfVariablesToTerms substitution3{variableWithExpressions};

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_EQ(1, substitution2.getSize());
    EXPECT_EQ(Term("y"), substitution2.getTermForVariable("x"));
    EXPECT_EQ(1, substitution3.getSize());
    EXPECT_EQ(Term("y"), substitution3.getTermForVariable("x"));
}

TEST(SubstitutionOfVariablesToTermsTest, IsEmptyWorks) {
    SubstitutionOfVariablesToTerms substitution1;
    SubstitutionOfVariablesToTerms substitution2({{"x", "y"}});

    EXPECT_TRUE(substitution1.isEmpty());
    EXPECT_FALSE(substitution2.isEmpty());
}

TEST(SubstitutionOfVariablesToTermsTest, IsVariableFoundWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});

    EXPECT_TRUE(substitution.isVariableFound("x"));
    EXPECT_FALSE(substitution.isVariableFound("y"));
    EXPECT_FALSE(substitution.isVariableFound("a"));
    EXPECT_FALSE(substitution.isVariableFound("b"));
}

TEST(SubstitutionOfVariablesToTermsTest, GetSizeWorks) {
    SubstitutionOfVariablesToTerms substitution1;
    SubstitutionOfVariablesToTerms substitution2({{"x", "y"}});

    EXPECT_EQ(0, substitution1.getSize());
    EXPECT_EQ(1, substitution2.getSize());
}

TEST(SubstitutionOfVariablesToTermsTest, GetValueForVariableWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});

    Term termToExpect("y");
    EXPECT_EQ(termToExpect, substitution.getTermForVariable("x"));
    EXPECT_EQ(Term{}, substitution.getTermForVariable("y"));
    EXPECT_EQ(Term{}, substitution.getTermForVariable("a"));
    EXPECT_EQ(Term{}, substitution.getTermForVariable("b"));
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnVariableTerm) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("x");
    VariableTerm variableTerm3("y");

    Term verifyTerm1(substitution.performSubstitutionTo(variableTerm1));
    Term verifyTerm2(substitution.performSubstitutionTo(variableTerm2));
    Term verifyTerm3(substitution.performSubstitutionTo(variableTerm3));

    Term expectTerm1(VariableTerm{});
    Term expectTerm2("y");
    Term expectTerm3("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnExpression) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    Expression expression1;
    Expression expression2(createExpressionIfPossible({"x", "&", "y"}));

    Term verifyTerm1(substitution.performSubstitutionTo(expression1));
    Term verifyTerm2(substitution.performSubstitutionTo(expression2));

    Term expectTerm1;
    Term expectTerm2("y");
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
}

TEST(SubstitutionOfVariablesToTermsTest, PerformSubstitutionToWorksOnTerm) {
    SubstitutionOfVariablesToTerms substitution({{"x", "y"}});
    Term term1;
    Term term2("x");
    Term term3(createExpressionIfPossible({"x", "&", "y"}));
    Term term4(true);

    Term verifyTerm1(substitution.performSubstitutionTo(term1));
    Term verifyTerm2(substitution.performSubstitutionTo(term2));
    Term verifyTerm3(substitution.performSubstitutionTo(term3));
    Term verifyTerm4(substitution.performSubstitutionTo(term4));

    Term expectTerm1;
    Term expectTerm2("y");
    Term expectTerm3("y");
    Term expectTerm4(true);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
}

TEST(SubstitutionOfVariablesToTermsTest, VariableToExpressionSubstitutionWorks) {
    SubstitutionOfVariablesToTerms substitution({{"x", createExpressionIfPossible({"a", "&", "b"})}});
    Term term1;
    Term term2("x");
    Term term3(createExpressionIfPossible({"x", "&", "y"}));
    Term term4(true);

    Term verifyTerm1(substitution.performSubstitutionTo(term1));
    Term verifyTerm2(substitution.performSubstitutionTo(term2));
    Term verifyTerm3(substitution.performSubstitutionTo(term3));
    Term verifyTerm4(substitution.performSubstitutionTo(term4));

    Term expectTerm1;
    Term expectTerm2(createExpressionIfPossible({"a", "&", "b"}));
    Term expectTerm3(createExpressionIfPossible({"a", "&", "b", "&", "y"}));
    Term expectTerm4(true);
    EXPECT_EQ(expectTerm1, verifyTerm1);
    EXPECT_EQ(expectTerm2, verifyTerm2);
    EXPECT_EQ(expectTerm3, verifyTerm3);
    EXPECT_EQ(expectTerm4, verifyTerm4);
}

}  // namespace booleanAlgebra

}  // namespace alba
