#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

TEST(SimplificationOfExpressionTest, SimplifyWorksOnSimplifyingInnerTerms)
{
    Expression monomialRaiseToMonomial(createExpressionIfPossible({Monomial(1, {{"x", 1}}), "^", Monomial(1, {{"y", 1}})}));
    SimplificationOfExpression simplification(monomialRaiseToMonomial);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"x", "^", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForAMultipleTermExpression)
{
    Term expressionTerm(createExpressionIfPossible({"x", "^", "x"}));
    Term expressionInExpressionTerm(createExpressionInAnExpression(expressionTerm));
    Term expressionInExpressionInExpressionTerm(createExpressionInAnExpression(expressionInExpressionTerm));
    Expression expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"x", "^", "x"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentAdditionExpressionLevels)
{
    Term expressionTermLevel1(createExpressionIfPossible({"c", "+", "d"}));
    Term expressionTermLevel2(createExpressionIfPossible({"b", "+", expressionTermLevel1}));
    Term expressionTermLevel3(createExpressionIfPossible({"a", "+", expressionTermLevel2}));
    Expression expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createAndWrapExpressionFromATerm(
                    Polynomial{Monomial(1, {{"a", 1}}), Monomial(1, {{"b", 1}}), Monomial(1, {{"c", 1}}), Monomial(1, {{"d", 1}})}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentMultiplicationExpressionLevels)
{
    Term expressionTermLevel1(createExpressionIfPossible({"c", "*", "d"}));
    Term expressionTermLevel2(createExpressionIfPossible({"b", "*", expressionTermLevel1}));
    Term expressionTermLevel3(createExpressionIfPossible({"a", "*", expressionTermLevel2}));
    Expression expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createAndWrapExpressionFromATerm(Monomial(1, {{"a", 1}, {"b", 1}, {"c", 1}, {"d", 1}})));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnDifferentRaiseToPowerExpressionLevels)
{
    Term expressionTermLevel1(createExpressionIfPossible({"c", "^", "d"}));
    Term expressionTermLevel2(createExpressionIfPossible({"b", "^", expressionTermLevel1}));
    Term expressionTermLevel3(createExpressionIfPossible({"a", "^", expressionTermLevel2}));
    Expression expressionToTest(createExpressionIfPossible({expressionTermLevel3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(expressionToTest);
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnExpressionInExpressionForASingleTermExpression)
{
    Term expressionTerm(createAndWrapExpressionFromATerm(967));
    Term expressionInExpressionTerm(createExpressionInAnExpression(expressionTerm));
    Term expressionInExpressionInExpressionTerm(createExpressionInAnExpression(expressionInExpressionTerm));
    Expression expressionToTest(createExpressionIfPossible({expressionInExpressionInExpressionTerm}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(967));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingNullExpressions)
{
    Expression nullExpression(createExpressionInAnExpression(Expression()));
    Expression expressionToTest(createExpressionIfPossible({nullExpression, "+", nullExpression, "+", nullExpression}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect;
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForAddingAndSubtracting)
{
    Expression expressionToTest(
                createExpressionIfPossible({0, "-", 200, "-", 50, "-", 0}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(-250));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForMultiplying)
{
    Expression expressionToTest(createExpressionIfPossible({0, "*", 200, "*", 50}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(0));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForMultiplyingWithRaiseToPowerExpression)
{
    Expression expressionToTest(createExpressionIfPossible({0, "*", "z", "^", "z"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(0));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForDividing)
{
    Expression expressionToTest(createExpressionIfPossible({0, "/", 1.17157287525381}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(0));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnZeroForDividingWithRaiseToPowerExpression)
{
    Expression expressionToTest(createExpressionIfPossible({0, "/", "z", "^", "z"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(0));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstants)
{
    Expression expressionToTest(createExpressionIfPossible({100, "+", 200, "-", 50}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(250));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsMonomialPolynomial)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {Monomial(43, {{"x", 2}, {"y", 3}}), "+", 159, "-",
     Polynomial{
         Monomial(56, {{"x", 3}}),
         Monomial(-251, {}),
         Monomial(13, {{"x", 2}, {"y", 3}})
     }}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {Polynomial{
         Monomial(30, {{"x", 2}, {"y", 3}}),
         Monomial(-56, {{"x", 3}}),
         Monomial(410, {})
     }}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingConstantsWithExpressionInBetween)
{
    Expression expressionToTest(createExpressionIfPossible(
    {500, "+", "y", "^", "y", "-", 150 }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression(createExpressionIfPossible({"y", "^", "y"}));
    Expression expressionToExpect(createExpressionIfPossible({350, "+", subExpression}));
    expressionToExpect.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingZerosWithExpressionInBetween)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {
                        0,
                        "+", "y", "^", "y",
                        "-",  0
                    }));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"y", "^", "y"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingRaiseToPowerExpressions)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {5, "*", "y", "^", "y",
     "+","y", "^", "y",
     "-", 3, "*", "y", "^", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression(createExpressionIfPossible({"y", "^", "y"}));
    Expression expressionToExpect(createExpressionIfPossible({3, "*", subExpression}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingMultipleRaiseToPowerExpressions)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {"x", "^", "y",
     "-", 2, "*", "y", "^", "y",
     "-", 3, "*", "x", "^", "y",
     "+", "y", "^", "y",
     "+", 4, "*", "x", "^", "y",
     "+", 5, "*", "y", "^", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression1(createExpressionIfPossible({"x", "^", "y"}));
    Expression subExpression2(createExpressionIfPossible({"y", "^", "y"}));
    Expression subExpression3(createExpressionIfPossible({2, "*", subExpression1}));
    Expression subExpression4(createExpressionIfPossible({4, "*", subExpression2}));
    Expression expressionToExpect(createExpressionIfPossible({subExpression3, "+", subExpression4}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingNonSortedRaiseToPowerExpressions)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {100, "*", "y", "^", "y", "*", "x", "^", "x",
     "-", 10, "*", "x", "^", "x", "*", "y", "^", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression1(createExpressionIfPossible({"x", "^", "x"}));
    Expression subExpression2(createExpressionIfPossible({"y", "^", "y"}));
    Expression subExpression3(createExpressionIfPossible({subExpression1, "*", subExpression2}));
    Expression expressionToExpect(createExpressionIfPossible({90, "*", subExpression3}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnAddingAndSubtractingRaiseToPowerExpressionsThatCannotBeAdded)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {10, "*", "y", "^", "y",
     "+", "x", "*", "y", "^", "y",
     "-", 8, "*", "y", "^", "y",
     "-", 6, "*", "x", "*", "y", "^", "y"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression subExpression1(createExpressionIfPossible({"y", "^", "y"}));
    Expression subExpression2(createExpressionIfPossible({2, "*", subExpression1}));
    Expression subExpression3(createExpressionIfPossible({Monomial(5, {{"x", 1}}), "*", subExpression1}));
    Expression expressionToExpect(createExpressionIfPossible({subExpression2, "-", subExpression3}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingConstants)
{
    Expression expressionToTest(createExpressionIfPossible({100, "*", 200, "/", 50}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({400}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingPolynomials)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {Polynomial{Monomial(1, {{"x", 1}, {"y", -1}}), Monomial(2, {{"x", -1}, {"y", 1}})}, "/",
     Polynomial{Monomial(3, {{"y", 1}}), Monomial(4, {{"z", -1}})}}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {Polynomial{Monomial(1, {{"x", 2}, {"z", 1}}), Monomial(2, {{"y", 2}, {"z", 1}})},
     "/",
     Polynomial{Monomial(3, {{"x", 1}, {"y", 2}, {"z", 1}}), Monomial(4, {{"x", 1}, {"y", 1}})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnMultiplyingAndDividingRaiseToPowerExpressionsCanBeCancelled)
{
    Expression expressionToTest(
                createExpressionIfPossible(
    {"x", "^", "x",
     "*", "y", "^", "y",
     "*", "z", "^", "z",
     "/", "z", "^", "z",
     "/", "y", "^", "y",
     "/", "x", "^", "x"}));

    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({1}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerWithMultipleTerms)
{
    Expression expression1(createExpressionIfPossible({"a", "^", "b", "^", "c", "^", "d"}));
    Expression expression2(createExpressionIfPossible({"x", "^", 2, "^", 3, "^", "y"}));
    SimplificationOfExpression simplification1(expression1);
    SimplificationOfExpression simplification2(expression2);

    simplification1.simplify();
    simplification2.simplify();

    Expression expressionToVerify1(simplification1.getExpression());
    Expression expressionToVerify2(simplification2.getExpression());
    Expression expressionToExpect1(
                createExpressionIfPossible(
    {"a", "^", Monomial(1, {{"b", 1}, {"c", 1}, {"d", 1}})}));
    Expression expressionToExpect2(
                createExpressionIfPossible(
    {"x", "^", Monomial(6, {{"y", 1}})}));
    EXPECT_EQ(expressionToExpect1, expressionToVerify1);
    EXPECT_EQ(expressionToExpect2, expressionToVerify2);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnRaiseToPowerAndItsNotAssociative)
{
    Term aToTheB(createExpressionIfPossible({"a", "^", "b"}));
    Term xToTheY(createExpressionIfPossible({"x", "^", "y"}));
    Expression expression(createExpressionIfPossible({aToTheB, "^", xToTheY}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {"a", "^", createExpressionIfPossible({"b", "*", xToTheY})}));
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
    Expression subExpression1(createExpressionIfPossible({polynomial1, "/", polynomial2}));
    Expression subExpression2(createExpressionIfPossible({polynomial3, "/", polynomial4}));
    Expression expressionToTest(createExpressionIfPossible({subExpression1, "*", subExpression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible({polynomial5, "/", polynomial6}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksInsideAFunction)
{
    Function absoluteValueFunction(abs(createOrCopyExpressionFromATerm(-100)));
    Expression expressionToTest(createOrCopyExpressionFromATerm(absoluteValueFunction));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(100));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnConstantOverConstant)
{
    Expression expressionToTest;
    expressionToTest.putTermWithMultiplicationIfNeeded(Term(-252));
    expressionToTest.putTermWithDivisionIfNeeded(Term(25));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    EXPECT_EQ(Expression(Term(AlbaNumber::createFraction(-252, 25))), expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksOnPolynomialsToFractionalExponents)
{
    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("(x+1)^(1/2)*(y+1)^(-1/3)*(z+1)^(1/4)")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term xPolynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term yPolynomialTerm(Polynomial{Monomial(1, {{"y", 1}}), Monomial(1, {})});
    Term zPolynomialTerm(Polynomial{Monomial(1, {{"z", 1}}), Monomial(1, {})});
    Term xExpressionTerm(createExpressionIfPossible({xPolynomialTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Term yExpressionTerm(createExpressionIfPossible({yPolynomialTerm, "^", AlbaNumber::createFraction(1, 3)}));
    Term zExpressionTerm(createExpressionIfPossible({zPolynomialTerm, "^", AlbaNumber::createFraction(1, 4)}));
    Expression expressionToExpect(
                createExpressionIfPossible(
    {xExpressionTerm, "*", zExpressionTerm, "/", yExpressionTerm}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWorksWithEvaluatingFunctions)
{
    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("x^2*y^-abs(-3)*z^4")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Monomial monomialToExpect(1, {{"x", 2}, {"y", -3}, {"z", 4}});
    Expression expressionToExpect(createAndWrapExpressionFromATerm(monomialToExpect));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(ExpressionTest, SimplifyWorksOnAddingMonomialAndExponentialTerms)
{
    Expression subExpression1(createExpressionIfPossible({"a", "^", "b"}));
    Expression subExpression2(createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", subExpression1}));
    Expression subExpression3(createExpressionIfPossible({Monomial(1, {{"y", 1}}), "*", subExpression1}));
    Expression expressionToTest(createExpressionIfPossible({subExpression2, "+", subExpression3}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {createExpressionIfPossible({"x", "*", subExpression1}),
     "+", createExpressionIfPossible({"y", "*", subExpression1})}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ZeroOverZeroResultsToNanAndDoesNotCrash)
{
    Expression expression(createExpressionIfPossible(
    {0, "/", 0}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    EXPECT_TRUE(isNotANumber(expressionToVerify));
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorksAsDefault)
{
    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term firstPart(createExpressionIfPossible({4, "/", Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}}));
    Term secondPart(createExpressionIfPossible({Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}, "/", Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}}));
    Term thirdPart(createExpressionIfPossible({Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}, "/", Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}}));
    Expression expressionToExpect(createExpressionIfPossible({firstPart, "+", secondPart, "+", thirdPart}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorksIfItsNotSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToACommonDenominator = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term firstPart(createExpressionIfPossible({4, "/", Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}}));
    Term secondPart(createExpressionIfPossible({Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}, "/", Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}}));
    Term thirdPart(createExpressionIfPossible({Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}, "/", Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}}));
    Expression expressionToExpect(createExpressionIfPossible({firstPart, "+", secondPart, "+", thirdPart}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorksIfItsSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expressionToTest(createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(
                createExpressionIfPossible(
    {Polynomial{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})},
     "/", Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorWorksWithExponentialAndTrigonometricFunction)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term x("x");
    Term eToTheX(createExpressionIfPossible({getEAsTerm(), "^", x}));
    Term eToTheXTimesSinX(createExpressionIfPossible({eToTheX, "*", sin(x)}));
    Term eToTheXTimesCosX(createExpressionIfPossible({eToTheX, "*", cos(x)}));
    Term expression1(createExpressionIfPossible({eToTheXTimesSinX, "-", eToTheXTimesCosX}));
    Term expression2(createExpressionIfPossible({expression1, "/", 2}));
    Term expressionToTest(createExpressionIfPossible({eToTheXTimesSinX, "-", eToTheXTimesCosX, "-", expression2}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    EXPECT_EQ("(((((e)^x)*sin(x))-(((e)^x)*cos(x)))/2)",
              expressionToVerify.getDisplayableString());
}

TEST(SimplificationOfExpressionTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorksAsDefault)
{
    Expression expression(createExpressionIfPossible(
    {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})},
     "^", 4,
     "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(
    {Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorksIfItsNotSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expression(createExpressionIfPossible(
    {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})},
     "^", 4,
     "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createOrCopyExpressionFromATerm(
    {Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseWorksIfItsSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression expression(createExpressionIfPossible(
    {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})},
     "^", 4,
     "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfExpression simplification(expression);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible(
    {abs(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}),
     "^", 2}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningRadicalsInMultiplicationAndDivisionWorksAsDefault)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Expression expressionToTest(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningRadicalsInMultiplicationAndDivisionWorksIfItsNotSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Expression expressionToTest(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCombiningRadicalsInMultiplicationAndDivisionWorksIfItsSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression squareRootOfXPlusOne(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Expression expressionToTest(createExpressionIfPossible({"x", "*", squareRootOfXPlusOne}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}})});
    Expression expressionToExpect(createExpressionIfPossible({insideSquareRootTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorksAsDefault)
{
    Term xPlusOneSquaredExpandedTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression expressionToTest(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorksIfItsNotSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneSquaredExpandedTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression expressionToTest(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByCheckingPolynomialRaiseToAnUnsignedIntWorksIfItsSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xPlusOneSquaredExpandedTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression expressionToTest(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", "x"}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible(
    {Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}, "^", Monomial(2, {{"x", 1}})}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingNumeratorWorksAsDefault)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term expectedNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingNumeratorWorksIfItsNotSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByRationalizingNumerator = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term expectedNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingNumeratorWorksIfItsSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByRationalizingNumerator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    Expression expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingDenominatorWorksAsDefault)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term expectedNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingDenominatorWorksIfItsNotSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByRationalizingDenominator = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term expectedNumerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyByRationalizingDenominatorWorksIfItsSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyByRationalizingDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(3, {})});
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Term expectedNumerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-6, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-9, {})});
    Expression expressionToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySubstitutingExpressionAndFunctionsToVariablesWorksAsDefault)
{
    Term tanX(tan("x"));
    Term numerator(createExpressionIfPossible({1, "+", tanX, "^", 2, "+", 2, "*", tanX}));
    Term denominator(createExpressionIfPossible({tanX, "+", 1}));
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({numerator, "/", denominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySubstitutingExpressionAndFunctionsToVariablesWorksIfItsNotSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables = false;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term tanX(tan("x"));
    Term numerator(createExpressionIfPossible({1, "+", tanX, "^", 2, "+", 2, "*", tanX}));
    Term denominator(createExpressionIfPossible({tanX, "+", 1}));
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({numerator, "/", denominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySubstitutingExpressionAndFunctionsToVariablesWorksIfItsSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term tanX(tan("x"));
    Term numerator(createExpressionIfPossible({1, "+", tanX, "^", 2, "+", 2, "*", tanX}));
    Term denominator(createExpressionIfPossible({tanX, "+", 1}));
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({tanX, "+", 1}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySubstitutingExpressionAndFunctionsToVariablesDoesNotCauseInfiniteLoopIfItsSet)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term xToTheX(createExpressionIfPossible({"x", "^", "x"}));
    Term yToTheY(createExpressionIfPossible({"y", "^", "y"}));
    Expression expressionToTest(createExpressionIfPossible({xToTheX, "-", yToTheY}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({xToTheX, "-", yToTheY}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(SimplificationOfExpressionTest, SimplifyBySimplifyingToFactorsWorks)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToFactors = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term polynomialTerm(Polynomial{Monomial(7, {{"x", 3}}), Monomial(-1, {})});
    Term numerator(createExpressionIfPossible({polynomialTerm, "^", 2}));
    Term denominator(createExpressionIfPossible({polynomialTerm, "^", 8}));
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    string stringToExpect("(1/117649/((1[x] + -0.5227579585747166)^6)/((1[x^2] + 0.5227579585747166[x] + 0.2732758832532051)^6))");
    EXPECT_EQ(stringToExpect, expressionToVerify.getDisplayableString());
}

TEST(SimplificationOfExpressionTest, ShouldSimplifyToACommonDenominatorAndShouldSimplifyToFactorsWorksToConvertPolynomialOverPolynomial)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToFactors = true;
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Polynomial polynomial{Monomial(1, {}), Monomial(1, {{"x", -2}})};
    Expression expressionToTest(createExpressionIfPossible({polynomial, "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Polynomial polynomialToExpect{Monomial(1, {{"x", 2}}), Monomial(1, {})};
    Expression expressionToExpect(createExpressionIfPossible(
    {polynomialToExpect,
     "^",
     AlbaNumber::createFraction(1, 2),
     "/",
     "x"}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(TermsOverTermsTest, SimplifyBySimplifyingToFactorsWithoutDoubleValueWorks)
{
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToFactors = true;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-5, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-7, {})});
    Expression expressionToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SimplificationOfExpression simplification(expressionToTest);

    simplification.simplify();

    Expression expressionToVerify(simplification.getExpression());
    Expression expressionToExpect(createExpressionIfPossible({numerator, "/", denominator}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

}

}

}
