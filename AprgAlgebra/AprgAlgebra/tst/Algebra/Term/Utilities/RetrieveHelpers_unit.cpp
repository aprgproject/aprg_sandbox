#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;

namespace alba
{

namespace algebra
{

TEST(RetrieveHelpersTest, HasAnyFunctionsWorks)
{
    Term term1(5);
    Term term2(abs(Term(5)));

    EXPECT_FALSE(hasAnyFunctions(term1));
    EXPECT_TRUE(hasAnyFunctions(term2));
}

TEST(RetrieveHelpersTest, GetCoefficientOfMonomialWithNoVariablesWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})};
    Polynomial polynomial3{Monomial(587, {{"x", 9}}), Monomial(975, {})};

    EXPECT_EQ(AlbaNumber(0), getCoefficientOfMonomialWithNoVariables(polynomial1));
    EXPECT_EQ(AlbaNumber(0), getCoefficientOfMonomialWithNoVariables(polynomial2));
    EXPECT_EQ(AlbaNumber(975), getCoefficientOfMonomialWithNoVariables(polynomial3));
}

TEST(RetrieveHelpersTest, GetCoefficientOfMonomialWithVariableOnlyWorks)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(516, {{"a", 7}}), Monomial(643, {{"b", 8}})};
    Polynomial polynomial3{Monomial(587, {{"x", 9}}), Monomial(975, {{"y", 10}})};

    EXPECT_EQ(AlbaNumber(0), getCoefficientOfMonomialWithVariableOnly(polynomial1, "x"));
    EXPECT_EQ(AlbaNumber(516), getCoefficientOfMonomialWithVariableOnly(polynomial2, "a"));
    EXPECT_EQ(AlbaNumber(975), getCoefficientOfMonomialWithVariableOnly(polynomial3, "y"));
}

}

}
