#include <Algebra/Integration/NumericalIntegration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(NumericalIntegrationUtilitiesTest, GetAnApproximateOfDefiniteIntegralUsingTrapezoidalRuleWorks)
{
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));
    DetailsForDefiniteIntegralWithValues integralDetails{"x", 5, 10};

    EXPECT_EQ(Term(AlbaNumber::createFraction(75, 2)), getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(termToTest1, integralDetails, 200));
    EXPECT_EQ(Term(AlbaNumber::createFraction(186667, 640)), getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(termToTest2, integralDetails, 200));
    EXPECT_EQ(Term(2343.76171875), getAnApproximateOfDefiniteIntegralUsingTrapezoidalRule(termToTest3, integralDetails, 200));
}

TEST(NumericalIntegrationUtilitiesTest, GetAnApproximateOfDefiniteIntegralUsingSimpsonRuleWorks)
{
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));
    Term termToTest4(Monomial(1, {{"x", 4}}));
    DetailsForDefiniteIntegralWithValues integralDetails{"x", 5, 10};

    EXPECT_EQ(Term(AlbaNumber::createFraction(75, 2)), getAnApproximateOfDefiniteIntegralUsingSimpsonRule(termToTest1, integralDetails, 200));
    EXPECT_EQ(Term(AlbaNumber::createFraction(875, 3)), getAnApproximateOfDefiniteIntegralUsingSimpsonRule(termToTest2, integralDetails, 200));
    EXPECT_EQ(Term(2343.75), getAnApproximateOfDefiniteIntegralUsingSimpsonRule(termToTest3, integralDetails, 200));
    EXPECT_EQ(Term(19375.000000260424713), getAnApproximateOfDefiniteIntegralUsingSimpsonRule(termToTest4, integralDetails, 200));
}

TEST(NumericalIntegrationUtilitiesTest, GetActualTruncationErrorInTrapezoidalRuleWorks){
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));    DetailsForDefiniteIntegralWithValues integralDetails{"x", 5, 10};

    EXPECT_EQ(Term(0), getActualTruncationErrorInTrapezoidalRule(termToTest1, integralDetails, 200));
    EXPECT_EQ(Term(AlbaNumber::createFraction(-1, 1920)), getActualTruncationErrorInTrapezoidalRule(termToTest2, integralDetails, 200));
    EXPECT_EQ(Term(-0.01171875), getActualTruncationErrorInTrapezoidalRule(termToTest3, integralDetails, 200));
}

TEST(NumericalIntegrationUtilitiesTest, GetActualTruncationErrorInSimpsonRuleWorks)
{
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));
    Term termToTest4(Monomial(1, {{"x", 4}}));
    DetailsForDefiniteIntegralWithValues integralDetails{"x", 5, 10};

    EXPECT_EQ(Term(0), getActualTruncationErrorInSimpsonRule(termToTest1, integralDetails, 200));
    EXPECT_EQ(Term(0), getActualTruncationErrorInSimpsonRule(termToTest2, integralDetails, 200));
    EXPECT_EQ(Term(0), getActualTruncationErrorInSimpsonRule(termToTest3, integralDetails, 200));
    EXPECT_EQ(Term(-2.6042471290566027164e-07), getActualTruncationErrorInSimpsonRule(termToTest4, integralDetails, 200));
}

TEST(NumericalIntegrationUtilitiesTest, GetAnApproximateOfTruncationErrorInTrapezoidalRuleAtWorks){
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));    DetailsForDefiniteIntegralWithValues integralDetails{"x", 5, 10};

    EXPECT_EQ(Term(0), getAnApproximateOfTruncationErrorInTrapezoidalRuleAt(termToTest1, integralDetails, 7.5, 0.025));
    EXPECT_EQ(Term(-0.0005208333333333334), getAnApproximateOfTruncationErrorInTrapezoidalRuleAt(termToTest2, integralDetails, 7.5, 0.025));
    EXPECT_EQ(Term(-0.01171875), getAnApproximateOfTruncationErrorInTrapezoidalRuleAt(termToTest3, integralDetails, 7.5, 0.025));
}

TEST(NumericalIntegrationUtilitiesTest, GetAnApproximateOfTruncationErrorInSimpsonRuleAtWorks)
{
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));
    Term termToTest4(Monomial(1, {{"x", 4}}));
    DetailsForDefiniteIntegralWithValues integralDetails{"x", 5, 10};

    EXPECT_EQ(Term(0), getAnApproximateOfTruncationErrorInSimpsonRuleAt(termToTest1, integralDetails, 7.5, 0.025));
    EXPECT_EQ(Term(0), getAnApproximateOfTruncationErrorInSimpsonRuleAt(termToTest2, integralDetails, 7.5, 0.025));
    EXPECT_EQ(Term(0), getAnApproximateOfTruncationErrorInSimpsonRuleAt(termToTest3, integralDetails, 7.5, 0.025));
    EXPECT_EQ(Term(-0.0004166666666666667), getAnApproximateOfTruncationErrorInSimpsonRuleAt(termToTest4, integralDetails, 7.5, 0.025));
}

TEST(NumericalIntegrationUtilitiesTest, GetAnApproximateOfNaturalLogarithmUsingTrapezoidalRuleWorks)
{
    EXPECT_EQ(AlbaNumber(2.302752121358471), getAnApproximateOfNaturalLogarithmUsingTrapezoidRule(10, 200));
    EXPECT_EQ(AlbaNumber(0), getAnApproximateOfNaturalLogarithmUsingTrapezoidRule(1, 200));
    EXPECT_EQ(AlbaNumber(-2.302752121358471), getAnApproximateOfNaturalLogarithmUsingTrapezoidRule(0.1, 200));
    EXPECT_EQ(AlbaNumber(-8.085601984755872), getAnApproximateOfNaturalLogarithmUsingTrapezoidRule(0.001, 200));
}

TEST(NumericalIntegrationUtilitiesTest, GetAnApproximateOfNaturalLogarithmUsingSimpsonRuleWorks)
{
    EXPECT_EQ(AlbaNumber(2.30258522901465), getAnApproximateOfNaturalLogarithmUsingSimpsonRule(10, 200));
    EXPECT_EQ(AlbaNumber(0), getAnApproximateOfNaturalLogarithmUsingSimpsonRule(1, 200));
    EXPECT_EQ(AlbaNumber(-2.30258522901465), getAnApproximateOfNaturalLogarithmUsingSimpsonRule(0.1, 200));
    EXPECT_EQ(AlbaNumber(-7.439211364315156), getAnApproximateOfNaturalLogarithmUsingSimpsonRule(0.001, 200));
}

}

}
