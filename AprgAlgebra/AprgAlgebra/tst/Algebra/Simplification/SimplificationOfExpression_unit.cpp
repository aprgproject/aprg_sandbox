#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

TEST(SimplificationOfExpressionTest, SimplifyWorksOnSimplifyingInnerTerms)
{
    Expression monomialRaiseToMonomial(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}})), Term("^"), Term(Monomial(1, {{"y", 1}}))}));
    SimplificationOfExpression simplification(monomialRaiseToMonomial);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForAMultipleTermExpression)
{
    Term expressionTerm(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Term expressionInExpressionTerm(createExpressionInAnExpression(expressionTerm));
    Term expressionInExpressionInExpressionTerm(createExpressionInAnExpression(expressionInExpressionTerm));
    Expression expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentAdditionExpressionLevels)
{
    Term expressionTermLevel1(createExpressionIfPossible({Term("c"), Term("+"), Term("d")}));
    Term expressionTermLevel2(createExpressionIfPossible({Term("b"), Term("+"), expressionTermLevel1}));
    Term expressionTermLevel3(createExpressionIfPossible({Term("a"), Term("+"), expressionTermLevel2}));
    Expression expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createAndWrapExpressionFromATerm(
                    Term(Polynomial{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}}), Monomial(1, {{"c", 1}}), Monomial(1, {{"d", 1}})})));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentMultiplicationExpressionLevels)
{
    Term expressionTermLevel1(createExpressionIfPossible({Term("c"), Term("*"), Term("d")}));
    Term expressionTermLevel2(createExpressionIfPossible({Term("b"), Term("*"), expressionTermLevel1}));
    Term expressionTermLevel3(createExpressionIfPossible({Term("a"), Term("*"), expressionTermLevel2}));
    Expression expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm(Term(Monomial(1, {{"a", 1}, {"b", 1}, {"c", 1}, {"d", 1}}))));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentRaiseToPowerExpressionLevels)
{
    Term expressionTermLevel1(createExpressionIfPossible({Term("c"), Term("^"), Term("d")}));
    Term expressionTermLevel2(createExpressionIfPossible({Term("b"), Term("^"), expressionTermLevel1}));
    Term expressionTermLevel3(createExpressionIfPossible({Term("a"), Term("^"), expressionTermLevel2}));
    Expression expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(expressionToTest);
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForASingleTermExpression)
{
    Term expressionTerm(createAndWrapExpressionFromATerm(Term(967)));
    Term expressionInExpressionTerm(createExpressionInAnExpression(expressionTerm));
    Term expressionInExpressionInExpressionTerm(createExpressionInAnExpression(expressionInExpressionTerm));
    Expression expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(967)));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingNullExpressions)
{
    Expression nullExpression(createExpressionInAnExpression(Expression()));
    Expression expressionToTest(createExpressionIfPossible({nullExpression, Term("+"), nullExpression, Term("+"), nullExpression}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect;
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForAddingAndSubtracting)
{
    Expression expressionToTest(
                createExpressionIfPossible({Term(Constant(0)), Term("-"), Term(200), Term("-"), Term(50), Term("-"), Term(Constant(0))}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(-250)));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForMultiplying)
{
    Expression expressionToTest(createExpressionIfPossible({Term(Constant(0)), Term("*"), Term(200), Term("*"), Term(50)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(Constant(0))));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForMultiplyingWithRaiseToPowerExpression)
{
    Expression expressionToTest(createExpressionIfPossible({Term(Constant(0)), Term("*"), Term("z"), Term("^"), Term("z")}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(Constant(0))));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForDividing)
{
    Expression expressionToTest(createExpressionIfPossible({Term(Constant(0)), Term("/"), Term(1.17157287525381)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(Constant(0))));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForDividingWithRaiseToPowerExpression)
{
    Expression expressionToTest(createExpressionIfPossible({Term(Constant(0)), Term("/"), Term("z"), Term("^"), Term("z")}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(Constant(0))));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstants)
{
    Expression expressionToTest(createExpressionIfPossible({Term(100), Term("+"), Term(200), Term("-"), Term(50)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(250)));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsMonomialPolynomial)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term(Monomial(43, {{"x", 2}, {"y", 3}})),
                        Term("+"), Term(159),
                        Term("-"), Term(Polynomial{
                            Monomial(56, {{"x", 3}}),
                            Monomial(-251, {}),
                            Monomial(13, {{"x", 2}, {"y", 3}})
                        })
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {
                        Term(Polynomial{
                            Monomial(30, {{"x", 2}, {"y", 3}}),
                            Monomial(-56, {{"x", 3}}),
                            Monomial(410, {})
                        })}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsWithExpressionInBetween)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term(500),
                        Term("+"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(150)
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expressionToExpect(createExpressionIfPossible({Term(350), Term("+"), Term(subExpression)}));
    expressionToExpect.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingZerosWithExpressionInBetween)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term(Constant(0)),
                        Term("+"), Term("y"), Term("^"), Term("y"),
                        Term("-"),  Term(Constant(0))
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingRaiseToPowerExpressions)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term(5), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("+"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(3), Term("*"), Term("y"), Term("^"), Term("y")
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression expressionToExpect(createExpressionIfPossible({Term(3), Term("*"), Term(subExpression)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingMultipleRaiseToPowerExpressions)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term("x"), Term("^"), Term("y"),
                        Term("-"), Term(2), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(3), Term("*"), Term("x"), Term("^"), Term("y"),
                        Term("+"), Term("y"), Term("^"), Term("y"),
                        Term("+"), Term(4), Term("*"), Term("x"), Term("^"), Term("y"),
                        Term("+"), Term(5), Term("*"), Term("y"), Term("^"), Term("y")
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression subExpression3(createExpressionIfPossible({Term(2), Term("*"), Term(subExpression1)}));
    Expression subExpression4(createExpressionIfPossible({Term(4), Term("*"), Term(subExpression2)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression3), Term("+"), Term(subExpression4)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingNonSortedRaiseToPowerExpressions)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term(100), Term("*"), Term("y"), Term("^"), Term("y"), Term("*"), Term("x"), Term("^"), Term("x"),
                        Term("-"), Term(10), Term("*"), Term("x"), Term("^"), Term("x"), Term("*"), Term("y"), Term("^"), Term("y")
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression1(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    Expression subExpression2(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression subExpression3(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression2)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(90), Term("*"), Term(subExpression3)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingRaiseToPowerExpressionsThatCannotBeAdded)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term(10), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("+"), Term("x"), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(8), Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("-"), Term(6), Term("*"), Term("x"), Term("*"), Term("y"), Term("^"), Term("y")
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression1(createExpressionIfPossible({Term("y"), Term("^"), Term("y")}));
    Expression subExpression2(createExpressionIfPossible({Term(2), Term("*"), Term(subExpression1)}));
    Expression subExpression3(createExpressionIfPossible({Term(Monomial(-5, {{"x", 1}})), Term("*"), Term(subExpression1)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression2), Term("+"), Term(subExpression3)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingConstants)
{
    Expression expressionToTest(createExpressionIfPossible({Term(100), Term("*"), Term(200), Term("/"), Term(50)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term(400)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingPolynomials)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term(Polynomial{Monomial(1, {{"x", 1}, {"y", -1}}), Monomial(2, {{"x", -1}, {"y", 1}})}),
                        Term("/"),
                        Term(Polynomial{Monomial(3, {{"y", 1}}), Monomial(4, {{"z", -1}})})
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {
                        Term(Polynomial{Monomial(1, {{"x", 2}, {"z", 1}}), Monomial(2, {{"y", 2}, {"z", 1}})}),
                        Term("/"),
                        Term(Polynomial{Monomial(3, {{"x", 1}, {"y", 2}, {"z", 1}}), Monomial(4, {{"x", 1}, {"y", 1}})})
                    }));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingRaiseToPowerExpressionsCanBeCancelled)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        Term("x"), Term("^"), Term("x"),
                        Term("*"), Term("y"), Term("^"), Term("y"),
                        Term("*"), Term("z"), Term("^"), Term("z"),
                        Term("/"), Term("z"), Term("^"), Term("z"),
                        Term("/"), Term("y"), Term("^"), Term("y"),
                        Term("/"), Term("x"), Term("^"), Term("x")
                    }));

    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term(1)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerIfBaseIsOneOrZero)
{
    Expression expression1(createExpressionIfPossible({Term(1), Term("^"), Term("a"), Term("^"), Term("b")}));
    Expression expression2(createExpressionIfPossible({Term(Constant(0)), Term("^"), Term("c"), Term("^"), Term("d")}));
    SimplificationOfExpression simplification1(expression1);
    SimplificationOfExpression simplification2(expression2);

    simplification1.simplify();
    simplification2.simplify();

    Expression expressionToVerify1(simplification1.getExpression());
    Expression expressionToVerify2(simplification2.getExpression());
    Expression expressionToExpect1(createExpressionIfPossible({Term(1)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(Constant(0))}));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerIfExponentIsOne)
{
    Expression expression1(createExpressionIfPossible({Term("a"), Term("^"), Term(1)}));
    Expression expression2(createExpressionIfPossible({Term("b"), Term("^"), Term(1), Term("^"), Term(1), Term("^"), Term(1)}));
    SimplificationOfExpression simplification1(expression1);
    SimplificationOfExpression simplification2(expression2);

    simplification1.simplify();
    simplification2.simplify();

    Expression expressionToVerify1(simplification1.getExpression());
    Expression expressionToVerify2(simplification2.getExpression());
    Expression expressionToExpect1(createExpressionIfPossible({Term("a")}));
    Expression expressionToExpect2(createExpressionIfPossible({Term("b")}));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerIfExponentIsZero)
{
    Expression expression1(createExpressionIfPossible({Term("a"), Term("^"), Term(Constant(0))}));
    Expression expression2(createExpressionIfPossible({Term("b"), Term("^"), Term("a"), Term("^"), Term(Constant(0)), Term("^"), Term("b")}));
    SimplificationOfExpression simplification1(expression1);
    SimplificationOfExpression simplification2(expression2);

    simplification1.simplify();
    simplification2.simplify();

    Expression expressionToVerify1(simplification1.getExpression());
    Expression expressionToVerify2(simplification2.getExpression());
    Expression expressionToExpect1(createExpressionIfPossible({Term(1)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(1)}));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerWithMultipleTerms)
{
    Expression expression1(createExpressionIfPossible({Term("a"), Term("^"), Term("b"), Term("^"), Term("c"), Term("^"), Term("d")}));
    Expression expression2(createExpressionIfPossible({Term("x"), Term("^"), Term(2), Term("^"), Term(3), Term("^"), Term("y")}));
    SimplificationOfExpression simplification1(expression1);
    SimplificationOfExpression simplification2(expression2);

    simplification1.simplify();
    simplification2.simplify();

    Expression expressionToVerify1(simplification1.getExpression());
    Expression expressionToVerify2(simplification2.getExpression());
    Expression expressionToExpect1(
                createExpressionIfPossible(
    {Term("a"), Term("^"), Term(Monomial(1, {{"b", 1}, {"c", 1}, {"d", 1}}))}));
    Expression expressionToExpect2(
                createExpressionIfPossible(
    {Term("x"), Term("^"), Term(Monomial(6, {{"y", 1}}))}));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerAndItsNotAssociative)
{
    Expression aToTheB(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Expression xToTheY(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Expression expression(createExpressionIfPossible({Term(aToTheB), Term("^"), Term(xToTheY)}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {Term("a"), Term("^"), Term(createExpressionIfPossible({Term("b"), Term("*"), Term(xToTheY)}))
                    }));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksMultiplyingPolynomialOverPolynomials)
{
    Polynomial polynomial1{Monomial(3, {{"x", 2}}), Monomial(-12, {{"x", 1}}), Monomial(-2, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 2}}), Monomial(-6, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomial3{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(6, {})};
    Polynomial polynomial4{Monomial(1, {{"x", 2}}), Monomial(6, {{"x", 1}}), Monomial(9, {})};
    Polynomial polynomial5{Monomial(3, {{"x", 4}}), Monomial(-32, {{"x", 2}}), Monomial(-80, {{"x", 1}}), Monomial(-12, {})};
    Polynomial polynomial6{Monomial(1, {{"x", 4}}), Monomial(-18, {{"x", 2}}), Monomial(81, {})};
    Expression subExpression1(createExpressionIfPossible({Term(polynomial1), Term("/"), Term(polynomial2)}));
    Expression subExpression2(createExpressionIfPossible({Term(polynomial3), Term("/"), Term(polynomial4)}));
    Expression expressionToTest(createExpressionIfPossible({Term(subExpression1), Term("*"), Term(subExpression2)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {
                        Term(polynomial5),
                        Term("/"),
                        Term(polynomial6)
                    }));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksInsideAFunction)
{
    Function absoluteValueFunction(Functions::abs(createOrCopyExpressionFromATerm(Term(-100))));
    Expression expressionToTest(createOrCopyExpressionFromATerm(absoluteValueFunction));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(100)));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyToCommonDenominatorWorksOnConstants)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expressionToTest;
    expressionToTest.putTermWithMultiplicationIfNeeded(Term(-252));
    expressionToTest.putTermWithDivisionIfNeeded(Term(25));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    EXPECT_EQ(Expression(Term(AlbaNumber::createFraction(-252, 25))), expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyToACommonDenominatorWorks)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {
                        Term(Polynomial{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})}),
                        Term("/"),
                        Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}),
                    }));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyToACommonDenominatorWorksWithNegativeExponents)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("(x+1)^(1/2)*(y+1)^(-1/3)*(z+1)^(1/4)")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term xPolynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term yPolynomialTerm(Polynomial{Monomial(1, {{"y", 1}}), Monomial(1, {})});
    Term zPolynomialTerm(Polynomial{Monomial(1, {{"z", 1}}), Monomial(1, {})});
    Term xExpressionTerm(createExpressionIfPossible({xPolynomialTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term yExpressionTerm(createExpressionIfPossible({yPolynomialTerm, Term("^"), Term(AlbaNumber::createFraction(-1, 3))}));
    Term zExpressionTerm(createExpressionIfPossible({zPolynomialTerm, Term("^"), Term(AlbaNumber::createFraction(1, 4))}));
    Expression expressionToExpect(
                createExpressionIfPossible(
    {xExpressionTerm, Term("*"), yExpressionTerm, Term("*"), zExpressionTerm}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyToACommonDenominatorWorksOnExponentPlusPolynomialDenominator)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("2^x+((1)/(x+2))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Polynomial polynomialToExpect{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Expression subExpression1(createExpressionIfPossible({Term(2), Term("^"), Term("x")}));
    Expression subExpression2(createExpressionIfPossible({Term("x"), Term("*"), Term(subExpression1)}));
    Expression subExpression3(createExpressionIfPossible({Term(2), Term("*"), Term(subExpression1)}));
    Expression subExpression4(createExpressionIfPossible({Term(1), Term("+"), Term(subExpression2), Term("+"), Term(subExpression3)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression4), Term("/"), Term(polynomialToExpect)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyToACommonDenominatorWorksOnExponentWithFractionExpressions)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("2^(((1)/(x+2))+((1)/(x-2)))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Polynomial polynomialToExpect{Monomial(1, {{"x", 2}}), Monomial(-4, {})};
    Expression subExpression(createExpressionIfPossible({Term(Monomial(2, {{"x", 1}})), Term("/"), Term(polynomialToExpect)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(2), Term("^"), Term(subExpression)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyToACommonDenominatorWorksInsideAFunction)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("x^2*y^-abs(-3)*z^4")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Monomial monomialToExpect(1, {{"x", 2}, {"y", -3}, {"z", 4}});
    Expression expressionToExpect(createAndWrapExpressionFromATerm(Term(monomialToExpect)));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(ExpressionTest, SimplifyToACommonDenominatorMaintainsCorrectnessOfExpressions)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression subExpression1(createExpressionIfPossible({Term("a"), Term("^"), Term("b")}));
    Expression subExpression2(createExpressionIfPossible({Term(Monomial(1, {{"x", 1}})), Term("*"), Term(subExpression1)}));
    Expression subExpression3(createExpressionIfPossible({Term(Monomial(1, {{"y", 1}})), Term("*"), Term(subExpression1)}));
    Expression expressionToTest(createExpressionIfPossible({Term(subExpression2), Term("+"), Term(subExpression3)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {
                        Term(createExpressionIfPossible({Term(Variable("x")), Term("*"), Term(subExpression1)})),
                        Term("+"), Term(createExpressionIfPossible({Term(Variable("y")), Term("*"), Term(subExpression1)}))
                    }));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyToACommonDenominatorWorksOnRaiseToPowerIfBaseIsOneOrZero)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expression1(createExpressionIfPossible({Term(1), Term("^"), Term("a"), Term("^"), Term("b")}));
    Expression expression2(createExpressionIfPossible({Term(Constant(0)), Term("^"), Term("c"), Term("^"), Term("d")}));
    SimplificationOfExpression simplification1(expression1);
    SimplificationOfExpression simplification2(expression2);

    simplification1.simplify();
    simplification2.simplify();

    Expression expressionToVerify1(simplification1.getExpression());
    Expression expressionToVerify2(simplification2.getExpression());
    Expression expressionToExpect1(createExpressionIfPossible({Term(1)}));
    Expression expressionToExpect2(createExpressionIfPossible({Term(Constant(0))}));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(SimplificationOfExpressionTest, EvenExponentsCancellationWithAbsoluteValueWorks)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyEvenExponentsCancellationWithAbsoluteValue = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expression(createExpressionIfPossible(
    {Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}),
     Term("^"), Term(4),
     Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible(
    {Term(Functions::abs(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}))),
     Term("^"), Term(2)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivisionWorksWhenSetAsDefaultUsingMultiplication)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Expression expressionToTest(createExpressionIfPossible({Term("x"), Term("*"), Term(squareRootOfXPlusOne)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term("x"), Term("*"), Term(squareRootOfXPlusOne)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivisionWorksWhenSetToFalseUsingMultiplication)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivision = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Expression expressionToTest(createExpressionIfPossible({Term("x"), Term("*"), Term(squareRootOfXPlusOne)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term("x"), Term("*"), Term(squareRootOfXPlusOne)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivisionWorksWhenSetToTrueUsingMultiplication)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivision = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Expression expressionToTest(createExpressionIfPossible({Term("x"), Term("*"), Term(squareRootOfXPlusOne)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}})});
    Expression expressionToExpect(createExpressionIfPossible({insideSquareRootTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivisionWorksWhenSetAsDefaultUsingDivision)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Expression expressionToTest(createExpressionIfPossible({Term("x"), Term("/"), Term(squareRootOfXPlusOne)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term("x"), Term("/"), Term(squareRootOfXPlusOne)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivisionWorksWhenSetToFalseUsingDivision)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivision = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Expression expressionToTest(createExpressionIfPossible({Term("x"), Term("/"), Term(squareRootOfXPlusOne)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({Term("x"), Term("/"), Term(squareRootOfXPlusOne)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivisionWorksWhenSetToTrueUsingDivision)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivision = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Expression expressionToTest(createExpressionIfPossible({Term("x"), Term("/"), Term(squareRootOfXPlusOne)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression(createExpressionIfPossible({Term(Monomial(1, {{"x", 2}})), Term("/"), xPlusOneTerm}));
    Expression expressionToExpect(createExpressionIfPossible({Term(subExpression), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningRadicalsInMultiplicationAndDivisionWorksAndSquareRootExpressionAreAddedCorrectly)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    configurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    configurationDetails.shouldSimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivision = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Expression expressionToTest(createExpressionIfPossible({squareRootOfXPlusOneTerm, Term("+"), squareRootOfXPlusOneTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term polynomialTerm(Polynomial{Monomial(4, {{"x", 1}}), Monomial(4, {})});
    Expression expressionToExpect(createExpressionIfPossible({polynomialTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ZeroOverZeroResultsToNanAndDoesNotCrash)
{
    Expression expression(createExpressionIfPossible(
    {Term(Constant(0)), Term("/"), Term(Constant(0))}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    EXPECT_TRUE(isNotANumber(expressionToVerify));
}

}

}

}
