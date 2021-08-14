#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Trigonometry/TrigonometricEquations.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;
using namespace alba::mathHelper;

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

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", 5);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetSineEquationOfRightTriangleWorks)
{
    Term x("x");
    Term o("o");
    Term h("h");

    Equation actualEquation(getSineEquationOfRightTriangle(x, o, h));

    Term leftHandSide(sin(x));
    Term rightHandSide(createExpressionIfPossible({o, Term("/"), h}));
    Equation expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    substitution.putVariableWithValue("o", 5);
    substitution.putVariableWithValue("h", 10);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetCosineEquationOfRightTriangleWorks)
{
    Term x("x");
    Term a("a");
    Term h("h");

    Equation actualEquation(getCosineEquationOfRightTriangle(x, a, h));

    Term leftHandSide(cos(x));
    Term rightHandSide(createExpressionIfPossible({a, Term("/"), h}));
    Equation expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    substitution.putVariableWithValue("a", 5*sqrt(3));
    substitution.putVariableWithValue("h", 10);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetTangentEquationOfRightTriangleWorks)
{
    Term x("x");
    Term o("o");
    Term a("a");

    Equation actualEquation(getTangentEquationOfRightTriangle(x, o, a));

    Term leftHandSide(tan(x));
    Term rightHandSide(createExpressionIfPossible({o, Term("/"), a}));
    Equation expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    substitution.putVariableWithValue("o", 5);
    substitution.putVariableWithValue("a", 5*sqrt(3));
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetLawOfSineEquationWorks)
{
    Term s1("s1");
    Term a1("a1");
    Term s2("s2");
    Term a2("a2");

    Equation actualEquation(getLawOfSineEquation(s1, a1, s2, a2));

    Term leftHandSide(createExpressionIfPossible({s1, Term("/"), Term(sin(a1))}));
    Term rightHandSide(createExpressionIfPossible({s2, Term("/"), Term(sin(a2))}));
    Equation expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("s1", 5);
    substitution.putVariableWithValue("a1", getPi()/6);
    substitution.putVariableWithValue("s2", 5*sqrt(3));
    substitution.putVariableWithValue("a2", getPi()/3);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetLawOfCosineEquationWorks)
{
    Term s1("s1");
    Term s2("s2");
    Term s3("s3");
    Term a1("a1");

    Equation actualEquation(getLawOfCosineEquation(s1, s2, s3, a1));

    Term side1Squared(createExpressionIfPossible({s1, Term("^"), Term(2)}));
    Term side2Squared(createExpressionIfPossible({s2, Term("^"), Term(2)}));
    Term side3Squared(createExpressionIfPossible({s3, Term("^"), Term(2)}));
    Term cosinePart(createExpressionIfPossible({Term(2), Term("*"), s2, Term("*"), s3, Term("*"), Term(cos(a1))}));
    Term leftHandSide(side1Squared);
    Term rightHandSide(createExpressionIfPossible({side2Squared, Term("+"), side3Squared, Term("-"), cosinePart}));
    Equation expectedEquation(leftHandSide, "=", rightHandSide);
    EXPECT_EQ(expectedEquation, actualEquation);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("s1", 5);
    substitution.putVariableWithValue("s2", 5*sqrt(3));
    substitution.putVariableWithValue("s3", 10);
    substitution.putVariableWithValue("a1", getPi()/6);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetSineSquaredWorks)
{
    Term x("x");

    Term actualTerm(getSineSquared(x));

    Term expectedTerm(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(2)}));
    EXPECT_EQ(expectedTerm, actualTerm);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetCosineSquaredWorks)
{
    Term x("x");

    Term actualTerm(getCosineSquared(x));

    Term expectedTerm(createExpressionIfPossible({Term(cos(x)), Term("^"), Term(2)}));
    EXPECT_EQ(expectedTerm, actualTerm);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetTangentSquaredWorks)
{
    Term x("x");

    Term actualTerm(getTangentSquared(x));

    Term expectedTerm(createExpressionIfPossible({Term(tan(x)), Term("^"), Term(2)}));
    EXPECT_EQ(expectedTerm, actualTerm);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/4);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetSineOfSumOrDifferenceOfTwoVariablesWorks)
{
    Term x("x");
    Term y("y");

    Term actualSineOfSumOfValues(getSineOfSumOrDifferenceOfTwoVariables(x, Operator("+"), y));
    Term actualSineOfDifferenceOfValues(getSineOfSumOrDifferenceOfTwoVariables(x, Operator("-"), y));

    Expression firstPart(createExpressionIfPossible({Term(sin(x)), Term("*"), Term(cos(y))}));
    Expression secondPart(createExpressionIfPossible({Term(cos(x)), Term("*"), Term(sin(y))}));
    Term expectedSineOfSumOfValues(createExpressionIfPossible({Term(firstPart), Term("+"), Term(secondPart)}));
    Term expectedSineOfDifferenceOfValues(createExpressionIfPossible({Term(firstPart), Term("-"), Term(secondPart)}));
    EXPECT_EQ(expectedSineOfSumOfValues, actualSineOfSumOfValues);
    EXPECT_EQ(expectedSineOfDifferenceOfValues, actualSineOfDifferenceOfValues);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/12);
    substitution.putVariableWithValue("y", getPi()/12);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualSineOfSumOfValues));
    EXPECT_EQ(Term(Constant(0)), substitution.performSubstitutionTo(actualSineOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetCosineOfSumOrDifferenceOfTwoVariablesWorks)
{
    Term x("x");
    Term y("y");

    Term actualCosineOfSumOfValues(getCosineOfSumOrDifferenceOfTwoVariables(x, Operator("+"), y));
    Term actualCosineOfDifferenceOfValues(getCosineOfSumOrDifferenceOfTwoVariables(x, Operator("-"), y));

    Expression firstPart(createExpressionIfPossible({Term(cos(x)), Term("*"), Term(cos(y))}));
    Expression secondPart(createExpressionIfPossible({Term(sin(x)), Term("*"), Term(sin(y))}));
    Term expectedCosineOfSumOfValues(createExpressionIfPossible({Term(firstPart), Term("-"), Term(secondPart)}));
    Term expectedCosineOfDifferenceOfValues(createExpressionIfPossible({Term(firstPart), Term("+"), Term(secondPart)}));
    EXPECT_EQ(expectedCosineOfSumOfValues, actualCosineOfSumOfValues);
    EXPECT_EQ(expectedCosineOfDifferenceOfValues, actualCosineOfDifferenceOfValues);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    substitution.putVariableWithValue("y", getPi()/6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualCosineOfSumOfValues));
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualCosineOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetTangentOfSumOrDifferenceOfTwoVariablesWorks)
{
    Term x("x");
    Term y("y");

    Term actualTangentOfSumOfValues(getTangentOfSumOrDifferenceOfTwoVariables(x, Operator("+"), y));
    Term actualTangentOfDifferenceOfValues(getTangentOfSumOrDifferenceOfTwoVariables(x, Operator("-"), y));

    Expression numeratorSum(createExpressionIfPossible({Term(tan(x)), Term("+"), Term(tan(y))}));
    Expression denominatorSum(createExpressionIfPossible(
    {Term(1), Term("-"), Term(createExpressionIfPossible({Term(tan(x)), Term("*"), Term(tan(y))}))}));
    Expression numeratorDifference(createExpressionIfPossible({Term(tan(x)), Term("-"), Term(tan(y))}));
    Expression denominatorDifference(createExpressionIfPossible(
    {Term(1), Term("+"), Term(createExpressionIfPossible({Term(tan(x)), Term("*"), Term(tan(y))}))}));
    Term expectedTangentOfSumOfValues(createExpressionIfPossible({Term(numeratorSum), Term("/"), Term(denominatorSum)}));
    Term expectedTangentOfDifferenceOfValues(createExpressionIfPossible({Term(numeratorDifference), Term("/"), Term(denominatorDifference)}));
    EXPECT_EQ(expectedTangentOfSumOfValues, actualTangentOfSumOfValues);
    EXPECT_EQ(expectedTangentOfDifferenceOfValues, actualTangentOfDifferenceOfValues);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/8);
    substitution.putVariableWithValue("y", getPi()/8);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualTangentOfSumOfValues));
    EXPECT_EQ(Term(Constant(0)), substitution.performSubstitutionTo(actualTangentOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetSineOfDoubledValueWorks)
{
    Term x("x");

    Term actualSineOfDoubledValue(getSineOfDoubledValue(x));

    Term expectedSineOfDoubledValue(createExpressionIfPossible({Term(2), Term("*"), Term(sin(x)), Term("*"), Term(cos(x))}));
    EXPECT_EQ(expectedSineOfDoubledValue, actualSineOfDoubledValue);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/12);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualSineOfDoubledValue));
}

TEST(TrigonometricEquationsTest, GetCosineOfDoubledValueWorks)
{
    Term x("x");

    Term actualCosineOfDoubledValue(getCosineOfDoubledValue(x));

    Term expectedCosineOfDoubledValue(createExpressionIfPossible({getCosineSquared(x), Term("-"), getSineSquared(x)}));
    EXPECT_EQ(expectedCosineOfDoubledValue, actualCosineOfDoubledValue);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualCosineOfDoubledValue));
}

TEST(TrigonometricEquationsTest, GetTangentOfDoubledValueWorks)
{
    Term x("x");

    Term actualTangentOfDoubledValue(getTangentOfDoubledValue(x));

    Term expectedNumerator(createExpressionIfPossible({Term(2), Term("*"), Term(tan(x))}));
    Term expectedDenominator(createExpressionIfPossible({Term(1), Term("-"), getTangentSquared(x)}));
    Term expectedTangentOfDoubledValue(createExpressionIfPossible({expectedNumerator, Term("/"), expectedDenominator}));
    EXPECT_EQ(expectedTangentOfDoubledValue, actualTangentOfDoubledValue);

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/8);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(expectedTangentOfDoubledValue));
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

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualPositiveRoot));
    EXPECT_EQ(Term(AlbaNumber::createFraction(-1, 2)), substitution.performSubstitutionTo(actualNegativeRoot));
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

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()*2/3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualPositiveRoot));
    EXPECT_EQ(Term(AlbaNumber::createFraction(-1, 2)), substitution.performSubstitutionTo(actualNegativeRoot));
}

}

}
