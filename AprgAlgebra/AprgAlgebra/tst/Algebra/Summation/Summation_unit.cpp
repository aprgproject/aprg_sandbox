#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(SummationTest, SummationWorksForConstant)
{
    Summation summation(Term(5), "x");

    Term expectSummationModelWithKnownConstant(Polynomial{Monomial(5, {{"x", 1}}), Monomial(-45, {})});
    EXPECT_EQ(expectSummationModelWithKnownConstant, summation.getSummationModelWithKnownConstant(10));
    Term expectSummationModelWithUnknownConstant(Polynomial{Monomial(1, {{C, 1}}), Monomial(5, {{"x", 1}}), Monomial(5, {})});
    EXPECT_EQ(expectSummationModelWithUnknownConstant, summation.getSummationModelWithUnknownConstant());
    EXPECT_EQ(Term(55), summation.getSum(Term(10), Term(20)));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), summation.getSum(Term(10), Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity))));
    Term expectSumWhenEndingIsAVariable(Polynomial{Monomial(5, {{"variable", 1}}), Monomial(-45, {})});
    EXPECT_EQ(expectSumWhenEndingIsAVariable, summation.getSum(Term(10), Term("variable")));
}

TEST(SummationTest, SummationWorksForVariable)
{
    Summation summation(Term("x"), "x");

    Term expectSummationModelWithKnownConstant(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"x", 1}}),
     Monomial(-45, {})});
    EXPECT_EQ(expectSummationModelWithKnownConstant, summation.getSummationModelWithKnownConstant(10));
    Term expectSummationModelWithUnknownConstant(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(1, {{C, 1}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"x", 1}})});
    EXPECT_EQ(expectSummationModelWithUnknownConstant, summation.getSummationModelWithUnknownConstant());
    EXPECT_EQ(Term(165), summation.getSum(Term(10), Term(20)));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), summation.getSum(Term(10), Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity))));
    Term expectSumWhenEndingIsAVariable(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"variable", 2}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"variable", 1}}),
     Monomial(-45, {})});
    EXPECT_EQ(expectSumWhenEndingIsAVariable, summation.getSum(Term(10), Term("variable")));
}

TEST(SummationTest, SummationWorksForVariableSquared)
{
    Summation summation(Term(Monomial(1, {{"x", 2}})), "x");

    Term expectSummationModelWithKnownConstant(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}}),
     Monomial(-285, {})});
    EXPECT_EQ(expectSummationModelWithKnownConstant, summation.getSummationModelWithKnownConstant(10));
    Term expectSummationModelWithUnknownConstant(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(1, {{C, 1}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    EXPECT_EQ(expectSummationModelWithUnknownConstant, summation.getSummationModelWithUnknownConstant());
    EXPECT_EQ(Term(2585), summation.getSum(Term(10), Term(20)));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), summation.getSum(Term(10), Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity))));
    Term expectSumWhenEndingIsAVariable(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"variable", 3}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"variable", 2}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"variable", 1}}),
     Monomial(-285, {})});
    EXPECT_EQ(expectSumWhenEndingIsAVariable, summation.getSum(Term(10), Term("variable")));
}

TEST(SummationTest, SummationWorksForVariableCube)
{
    Summation summation(Term(Monomial(1, {{"x", 3}})), "x");

    Term expectSummationModelWithKnownConstant(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 4), {{"x", 4}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(1, 4), {{"x", 2}}),
     Monomial(-2025, {})});
    EXPECT_EQ(expectSummationModelWithKnownConstant, summation.getSummationModelWithKnownConstant(10));
    Term expectSummationModelWithUnknownConstant(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 4), {{"x", 4}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(1, 4), {{"x", 2}}),
     Monomial(1, {{C, 1}})});
    EXPECT_EQ(expectSummationModelWithUnknownConstant, summation.getSummationModelWithUnknownConstant());
    EXPECT_EQ(Term(42075), summation.getSum(Term(10), Term(20)));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), summation.getSum(Term(10), Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity))));
    Term expectSumWhenEndingIsAVariable(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 4), {{"variable", 4}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"variable", 3}}),
     Monomial(AlbaNumber::createFraction(1, 4), {{"variable", 2}}),
     Monomial(-2025, {})});
    EXPECT_EQ(expectSumWhenEndingIsAVariable, summation.getSum(Term(10), Term("variable")));
}

TEST(SummationTest, SummationWorksForPolynomial)
{
    Polynomial polynomial{Monomial(3, {{"x", 2}}), Monomial(-2, {{"x", 1}})};
    Summation summation(Term(polynomial), "x");

    Term expectSummationModelWithKnownConstant(Polynomial
    {Monomial(1, {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}}),
     Monomial(-765, {})});
    EXPECT_EQ(expectSummationModelWithKnownConstant, summation.getSummationModelWithKnownConstant(10));
    Term expectSummationModelWithUnknownConstant(Polynomial
    {Monomial(1, {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(1, {{C, 1}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    EXPECT_EQ(expectSummationModelWithUnknownConstant, summation.getSummationModelWithUnknownConstant());
    EXPECT_EQ(Term(7425), summation.getSum(Term(10), Term(20)));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), summation.getSum(Term(10), Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity))));
    Term expectSumWhenEndingIsAVariable(Polynomial
    {Monomial(1, {{"variable", 3}}),
     Monomial(AlbaNumber::createFraction(1, 2), {{"variable", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"variable", 1}}),
     Monomial(-765, {})});
    EXPECT_EQ(expectSumWhenEndingIsAVariable, summation.getSum(Term(10), Term("variable")));
}

}

}
