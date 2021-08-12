#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Trigonometry/TrigonometricEquations.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(TrigonometricEquationsTest, GetSineSquaredPlusCosineSquaredEqualsOneWorks)
{
    Term x("x");
    Equation actualEquation(getSineSquaredPlusCosineSquaredEqualsOne(x));

    Term expectedSineSquaredTerm(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(2)}));
    Term expectedCosineSquaredTerm(createExpressionIfPossible({Term(cos(x)), Term("^"), Term(2)}));
    Term leftHandSide(createExpressionIfPossible({expectedSineSquaredTerm, Term("+"), expectedCosineSquaredTerm}));
    Equation expectedEquation(leftHandSide, "=", Term(1));
    EXPECT_EQ(expectedEquation, actualEquation);
}

TEST(TrigonometricEquationsTest, GetSineSquaredWorks)
{
    Term x("x");
    Term actualTerm(getSineSquared(x));

    Term expectedTerm(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(2)}));
    EXPECT_EQ(expectedTerm, actualTerm);
}

TEST(TrigonometricEquationsTest, GetCosineSquaredWorks)
{
    Term x("x");
    Term actualTerm(getCosineSquared(x));

    Term expectedTerm(createExpressionIfPossible({Term(cos(x)), Term("^"), Term(2)}));
    EXPECT_EQ(expectedTerm, actualTerm);
}

TEST(TrigonometricEquationsTest, GetTangentSquaredWorks)
{
    Term x("x");
    Term actualTerm(getTangentSquared(x));

    Term expectedTerm(createExpressionIfPossible({Term(tan(x)), Term("^"), Term(2)}));
    EXPECT_EQ(expectedTerm, actualTerm);
}

TEST(TrigonometricEquationsTest, GetSineOfSumOrDifferenceOfTwoVariablesWorks)
{
    Term x("x");
    Term y("y");
    Term actualSineOfSumOfAngles(getSineOfSumOrDifferenceOfTwoVariables(x, Operator("+"), y));
    Term actualSineOfDifferenceOfAngles(getSineOfSumOrDifferenceOfTwoVariables(x, Operator("-"), y));

    Expression firstPart(createExpressionIfPossible({Term(sin(x)), Term("*"), Term(cos(y))}));
    Expression secondPart(createExpressionIfPossible({Term(cos(x)), Term("*"), Term(sin(y))}));
    Term expectedSineOfSumOfAngles(createExpressionIfPossible({Term(firstPart), Term("+"), Term(secondPart)}));
    Term expectedSineOfDifferenceOfAngles(createExpressionIfPossible({Term(firstPart), Term("-"), Term(secondPart)}));
    EXPECT_EQ(expectedSineOfSumOfAngles, actualSineOfSumOfAngles);
    EXPECT_EQ(expectedSineOfDifferenceOfAngles, actualSineOfDifferenceOfAngles);
}

TEST(TrigonometricEquationsTest, GetCosineOfSumOrDifferenceOfTwoVariablesWorks)
{
    Term x("x");
    Term y("y");
    Term actualCosineOfSumOfAngles(getCosineOfSumOrDifferenceOfTwoVariables(x, Operator("+"), y));
    Term actualCosineOfDifferenceOfAngles(getCosineOfSumOrDifferenceOfTwoVariables(x, Operator("-"), y));

    Expression firstPart(createExpressionIfPossible({Term(cos(x)), Term("*"), Term(cos(y))}));
    Expression secondPart(createExpressionIfPossible({Term(sin(x)), Term("*"), Term(sin(y))}));
    Term expectedCosineOfSumOfAngles(createExpressionIfPossible({Term(firstPart), Term("-"), Term(secondPart)}));
    Term expectedCosineOfDifferenceOfAngles(createExpressionIfPossible({Term(firstPart), Term("+"), Term(secondPart)}));
    EXPECT_EQ(expectedCosineOfSumOfAngles, actualCosineOfSumOfAngles);
    EXPECT_EQ(expectedCosineOfDifferenceOfAngles, actualCosineOfDifferenceOfAngles);
}

TEST(TrigonometricEquationsTest, GetTangentOfSumOrDifferenceOfTwoVariablesWorks)
{
    Term x("x");
    Term y("y");
    Term actualTangentOfSumOfAngles(getTangentOfSumOrDifferenceOfTwoVariables(x, Operator("+"), y));
    Term actualTangentOfDifferenceOfAngles(getTangentOfSumOrDifferenceOfTwoVariables(x, Operator("-"), y));

    Expression numeratorSum(createExpressionIfPossible({Term(tan(x)), Term("+"), Term(tan(y))}));
    Expression denominatorSum(createExpressionIfPossible(
    {Term(1), Term("-"), Term(createExpressionIfPossible({Term(tan(x)), Term("*"), Term(tan(y))}))}));
    Expression numeratorDifference(createExpressionIfPossible({Term(tan(x)), Term("-"), Term(tan(y))}));
    Expression denominatorDifference(createExpressionIfPossible(
    {Term(1), Term("+"), Term(createExpressionIfPossible({Term(tan(x)), Term("*"), Term(tan(y))}))}));
    Term expectedTangentOfSumOfAngles(createExpressionIfPossible({Term(numeratorSum), Term("/"), Term(denominatorSum)}));
    Term expectedTangentOfDifferenceOfAngles(createExpressionIfPossible({Term(numeratorDifference), Term("/"), Term(denominatorDifference)}));
    EXPECT_EQ(expectedTangentOfSumOfAngles, actualTangentOfSumOfAngles);
    EXPECT_EQ(expectedTangentOfDifferenceOfAngles, actualTangentOfDifferenceOfAngles);
}

TEST(TrigonometricEquationsTest, GetSineOfDoubledValueWorks)
{
    Term x("x");
    Term actualSineOfDoubledAngle(getSineOfDoubledValue(x));

    Term expectedSineOfDoubledAngle(createExpressionIfPossible({Term(2), Term("*"), Term(sin(x)), Term("*"), Term(cos(x))}));
    EXPECT_EQ(expectedSineOfDoubledAngle, actualSineOfDoubledAngle);
}

TEST(TrigonometricEquationsTest, GetCosineOfDoubledValueWorks)
{
    Term x("x");
    Term actualCosineOfDoubledAngle(getCosineOfDoubledValue(x));

    Term expectedCosineOfDoubledAngle(createExpressionIfPossible({getCosineSquared(x), Term("-"), getSineSquared(x)}));
    EXPECT_EQ(expectedCosineOfDoubledAngle, actualCosineOfDoubledAngle);
}

TEST(TrigonometricEquationsTest, GetTangentOfDoubledValueWorks)
{
    Term x("x");
    Term actualTangentOfDoubledAngle(getTangentOfDoubledValue(x));

    Term expectedNumerator(createExpressionIfPossible({Term(2), Term("*"), Term(tan(x))}));
    Term expectedDenominator(createExpressionIfPossible({Term(1), Term("-"), getTangentSquared(x)}));
    Term expectedTangentOfDoubledAngle(createExpressionIfPossible({expectedNumerator, Term("/"), expectedDenominator}));
    EXPECT_EQ(expectedTangentOfDoubledAngle, actualTangentOfDoubledAngle);
}

TEST(TrigonometricEquationsTest, GetSineOfHalvedValueWorks)
{
    Term x("x");
    Term actualPositiveRoot(getSineOfHalvedValue(x, true));
    Term actualNegativeRoot(getSineOfHalvedValue(x, false));

    Term numerator(createExpressionIfPossible({Term(1), Term("-"), Term(cos(x))}));
    Term squaredValue(createExpressionIfPossible({numerator, Term("/"), Term(2)}));
    Term expectedPositiveRoot(createExpressionIfPossible({squaredValue, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term expectedNegativeRoot(createExpressionIfPossible({Term(-1), Term("*"), Term(expectedPositiveRoot)}));
    EXPECT_EQ(expectedPositiveRoot, actualPositiveRoot);
    EXPECT_EQ(expectedNegativeRoot, actualNegativeRoot);
}

TEST(TrigonometricEquationsTest, GetCosineOfHalvedValueWorks)
{
    Term x("x");
    Term actualPositiveRoot(getCosineOfHalvedValue(x, true));
    Term actualNegativeRoot(getCosineOfHalvedValue(x, false));

    Term numerator(createExpressionIfPossible({Term(1), Term("+"), Term(cos(x))}));
    Term squaredValue(createExpressionIfPossible({numerator, Term("/"), Term(2)}));
    Term expectedPositiveRoot(createExpressionIfPossible({squaredValue, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term expectedNegativeRoot(createExpressionIfPossible({Term(-1), Term("*"), Term(expectedPositiveRoot)}));
    EXPECT_EQ(expectedPositiveRoot, actualPositiveRoot);
    EXPECT_EQ(expectedNegativeRoot, actualNegativeRoot);
}

}

}
