#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/KnownExpressionsAndEquations/TrigonometricEquations.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>
#include <cmath>

using namespace alba::algebra::Functions;using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(TrigonometricEquationsTest, GetTrigonometricPythagoreanIdentityWorks)
{
    Equation actualEquation(getTrigonometricPythagoreanIdentity("x"));

    Term expectedSineSquaredTerm(createExpressionIfPossible({sin("x"), "^", 2}));
    Term expectedCosineSquaredTerm(createExpressionIfPossible({cos("x"), "^", 2}));
    Term leftHandSide(createExpressionIfPossible({expectedSineSquaredTerm, "+", expectedCosineSquaredTerm}));
    Equation expectedEquation(leftHandSide, "=", 1);
    EXPECT_EQ(expectedEquation, actualEquation);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", 5);
    EXPECT_TRUE(substitution.performSubstitutionTo(actualEquation).isEquationSatisfied());
}

TEST(TrigonometricEquationsTest, GetSineEquationOfRightTriangleWorks)
{
    Equation actualEquation(getSineEquationOfRightTriangle("x", "o", "h"));

    Term leftHandSide(sin("x"));
    Term rightHandSide(createExpressionIfPossible({"o", "/", "h"}));
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
    Equation actualEquation(getCosineEquationOfRightTriangle("x", "a", "h"));

    Term leftHandSide(cos("x"));
    Term rightHandSide(createExpressionIfPossible({"a", "/", "h"}));
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
    Equation actualEquation(getTangentEquationOfRightTriangle("x", "o", "a"));

    Term leftHandSide(tan("x"));
    Term rightHandSide(createExpressionIfPossible({"o", "/", "a"}));
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
    Equation actualEquation(getLawOfSineEquation("s1", "a1", "s2", "a2"));

    Term leftHandSide(createExpressionIfPossible({"s1", "/", sin("a1")}));
    Term rightHandSide(createExpressionIfPossible({"s2", "/", sin("a2")}));
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
    Equation actualEquation(getLawOfCosineEquation("s1", "s2", "s3", "a1"));

    Term side1Squared(createExpressionIfPossible({"s1", "^", 2}));
    Term side2Squared(createExpressionIfPossible({"s2", "^", 2}));
    Term side3Squared(createExpressionIfPossible({"s3", "^", 2}));
    Term cosinePart(createExpressionIfPossible({2, "*", "s2", "*", "s3", "*", cos("a1")}));
    Term const& leftHandSide(side1Squared);
    Term rightHandSide(createExpressionIfPossible({side2Squared, "+", side3Squared, "-", cosinePart}));
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
    Term actualTerm(getSineSquared("x"));

    Term expectedTerm(createExpressionIfPossible({sin("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetSineSquaredInCosineWorks)
{
    Term actualTerm(getSineSquaredInCosine("x"));

    Term expectedTerm(createExpressionIfPossible({1, "-", cos("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetCosineSquaredWorks)
{
    Term actualTerm(getCosineSquared("x"));

    Term expectedTerm(createExpressionIfPossible({cos("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetCosineSquaredInSineWorks)
{
    Term actualTerm(getCosineSquaredInSine("x"));

    Term expectedTerm(createExpressionIfPossible({1, "-", sin("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetTangentSquaredWorks)
{
    Term actualTerm(getTangentSquared("x"));

    Term expectedTerm(createExpressionIfPossible({tan("x"), "^", 2}));
    EXPECT_EQ(expectedTerm, actualTerm);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/4);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualTerm));
}

TEST(TrigonometricEquationsTest, GetSineOfSumOrDifferenceOfTwoTermsWorks)
{
    Term actualSineOfSumOfValues(getSineOfSumOrDifferenceOfTwoTerms("x", Operator("+"), "y"));
    Term actualSineOfDifferenceOfValues(getSineOfSumOrDifferenceOfTwoTerms("x", Operator("-"), "y"));

    Term firstPart(createExpressionIfPossible({sin("x"), "*", cos("y")}));
    Term secondPart(createExpressionIfPossible({cos("x"), "*", sin("y")}));
    Term expectedSineOfSumOfValues(createExpressionIfPossible({firstPart, "+", secondPart}));
    Term expectedSineOfDifferenceOfValues(createExpressionIfPossible({firstPart, "-", secondPart}));
    EXPECT_EQ(expectedSineOfSumOfValues, actualSineOfSumOfValues);
    EXPECT_EQ(expectedSineOfDifferenceOfValues, actualSineOfDifferenceOfValues);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/12);
    substitution.putVariableWithValue("y", getPi()/12);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualSineOfSumOfValues));
    EXPECT_EQ(Term(0), substitution.performSubstitutionTo(actualSineOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetCosineOfSumOrDifferenceOfTwoTermsWorks)
{
    Term actualCosineOfSumOfValues(getCosineOfSumOrDifferenceOfTwoTerms("x", Operator("+"), "y"));
    Term actualCosineOfDifferenceOfValues(getCosineOfSumOrDifferenceOfTwoTerms("x", Operator("-"), "y"));

    Term firstPart(createExpressionIfPossible({cos("x"), "*", cos("y")}));
    Term secondPart(createExpressionIfPossible({sin("x"), "*", sin("y")}));
    Term expectedCosineOfSumOfValues(createExpressionIfPossible({firstPart, "-", secondPart}));
    Term expectedCosineOfDifferenceOfValues(createExpressionIfPossible({firstPart, "+", secondPart}));
    EXPECT_EQ(expectedCosineOfSumOfValues, actualCosineOfSumOfValues);
    EXPECT_EQ(expectedCosineOfDifferenceOfValues, actualCosineOfDifferenceOfValues);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    substitution.putVariableWithValue("y", getPi()/6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualCosineOfSumOfValues));
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualCosineOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetTangentOfSumOrDifferenceOfTwoTermsWorks)
{
    Term actualTangentOfSumOfValues(getTangentOfSumOrDifferenceOfTwoTerms("x", Operator("+"), "y"));
    Term actualTangentOfDifferenceOfValues(getTangentOfSumOrDifferenceOfTwoTerms("x", Operator("-"), "y"));

    Term numeratorSum(createExpressionIfPossible({tan("x"), "+", tan("y")}));
    Term denominatorSum(createExpressionIfPossible(
    {1, "-", createExpressionIfPossible({tan("x"), "*", tan("y")})}));
    Term numeratorDifference(createExpressionIfPossible({tan("x"), "-", tan("y")}));
    Term denominatorDifference(createExpressionIfPossible(
    {1, "+", createExpressionIfPossible({tan("x"), "*", tan("y")})}));
    Term expectedTangentOfSumOfValues(createExpressionIfPossible({numeratorSum, "/", denominatorSum}));
    Term expectedTangentOfDifferenceOfValues(createExpressionIfPossible({numeratorDifference, "/", denominatorDifference}));
    EXPECT_EQ(expectedTangentOfSumOfValues, actualTangentOfSumOfValues);
    EXPECT_EQ(expectedTangentOfDifferenceOfValues, actualTangentOfDifferenceOfValues);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/8);
    substitution.putVariableWithValue("y", getPi()/8);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(actualTangentOfSumOfValues));
    EXPECT_EQ(Term(0), substitution.performSubstitutionTo(actualTangentOfDifferenceOfValues));
}

TEST(TrigonometricEquationsTest, GetSineOfDoubledValueWorks)
{
    Term actualSineOfDoubledValue(getSineOfDoubledValue("x"));

    Term expectedSineOfDoubledValue(createExpressionIfPossible({2, "*", sin("x"), "*", cos("x")}));
    EXPECT_EQ(expectedSineOfDoubledValue, actualSineOfDoubledValue);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/12);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualSineOfDoubledValue));
}

TEST(TrigonometricEquationsTest, GetCosineOfDoubledValueWorks)
{
    Term actualCosineOfDoubledValue(getCosineOfDoubledValue("x"));

    Term expectedCosineOfDoubledValue(createExpressionIfPossible({getCosineSquared("x"), "-", getSineSquared("x")}));
    EXPECT_EQ(expectedCosineOfDoubledValue, actualCosineOfDoubledValue);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/6);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualCosineOfDoubledValue));
}

TEST(TrigonometricEquationsTest, GetTangentOfDoubledValueWorks)
{
    Term actualTangentOfDoubledValue(getTangentOfDoubledValue("x"));

    Term expectedNumerator(createExpressionIfPossible({2, "*", tan("x")}));
    Term expectedDenominator(createExpressionIfPossible({1, "-", getTangentSquared("x")}));
    Term expectedTangentOfDoubledValue(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expectedTangentOfDoubledValue, actualTangentOfDoubledValue);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/8);
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(expectedTangentOfDoubledValue));
}

TEST(TrigonometricEquationsTest, GetSineOfHalvedValueWorks)
{
    Term actualPositiveRoot(getSineOfHalvedValue("x", true));
    Term actualNegativeRoot(getSineOfHalvedValue("x", false));

    Term numerator(createExpressionIfPossible({1, "-", cos("x")}));
    Term squaredValue(createExpressionIfPossible({numerator, "/", 2}));
    Term expectedPositiveRoot(createExpressionIfPossible({squaredValue, "^", AlbaNumber::createFraction(1, 2)}));
    Term expectedNegativeRoot(createExpressionIfPossible({-1, "*", expectedPositiveRoot}));
    EXPECT_EQ(expectedPositiveRoot, actualPositiveRoot);
    EXPECT_EQ(expectedNegativeRoot, actualNegativeRoot);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()/3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualPositiveRoot));
    EXPECT_EQ(Term(AlbaNumber::createFraction(-1, 2)), substitution.performSubstitutionTo(actualNegativeRoot));
}

TEST(TrigonometricEquationsTest, GetCosineOfHalvedValueWorks)
{
    Term actualPositiveRoot(getCosineOfHalvedValue("x", true));
    Term actualNegativeRoot(getCosineOfHalvedValue("x", false));

    Term numerator(createExpressionIfPossible({1, "+", cos("x")}));
    Term squaredValue(createExpressionIfPossible({numerator, "/", 2}));
    Term expectedPositiveRoot(createExpressionIfPossible({squaredValue, "^", AlbaNumber::createFraction(1, 2)}));
    Term expectedNegativeRoot(createExpressionIfPossible({-1, "*", expectedPositiveRoot}));
    EXPECT_EQ(expectedPositiveRoot, actualPositiveRoot);
    EXPECT_EQ(expectedNegativeRoot, actualNegativeRoot);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi()*2/3);
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), substitution.performSubstitutionTo(actualPositiveRoot));
    EXPECT_EQ(Term(AlbaNumber::createFraction(-1, 2)), substitution.performSubstitutionTo(actualNegativeRoot));
}

TEST(TrigonometricEquationsTest, GetSineSquaredOfHalvedValueWorks)
{
    Term termToVerify(getSineSquaredOfHalvedValue("x"));

    Term numerator(createExpressionIfPossible({1, "-", cos("x")}));
    Term termToExpect(createExpressionIfPossible({numerator, "/", 2}));
    EXPECT_EQ(termToExpect, termToVerify);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi());
    EXPECT_EQ(Term(1), substitution.performSubstitutionTo(termToVerify));
}

TEST(TrigonometricEquationsTest, GetCosineSquaredOfHalvedValueWorks)
{
    Term termToVerify(getCosineSquaredOfHalvedValue("x"));

    Term numerator(createExpressionIfPossible({1, "+", cos("x")}));
    Term termToExpect(createExpressionIfPossible({numerator, "/", 2}));
    EXPECT_EQ(termToExpect, termToVerify);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue("x", getPi());
    EXPECT_EQ(Term(0), substitution.performSubstitutionTo(termToVerify));
}

}

}
