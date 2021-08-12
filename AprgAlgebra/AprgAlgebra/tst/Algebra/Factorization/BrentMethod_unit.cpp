#include <Algebra/Factorization/BrentMethod.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(BrentMethodTest, ConstructionWorks)
{
    BrentMethod(AlbaNumbers{});
    BrentMethod(AlbaNumbers{1, 2, 3});
}

TEST(BrentMethodTest, IsFinishedWorks)
{
    BrentMethod brentMethod1(AlbaNumbers{});
    BrentMethod brentMethod2(AlbaNumbers{1, 4, 4});
    brentMethod2.resetCalculation(-4, 4);
    brentMethod2.runMaxNumberOfIterationsOrUntilFinished(1000);

    EXPECT_FALSE(brentMethod1.isFinished());
    EXPECT_TRUE(brentMethod2.isFinished());
}

TEST(BrentMethodTest, GetNumberOfIterationsExecutedWorks)
{
    BrentMethod brentMethod1(AlbaNumbers{});
    BrentMethod brentMethod2(AlbaNumbers{1, 4, 4});
    brentMethod2.resetCalculation(-4, 4);
    brentMethod2.runMaxNumberOfIterationsOrUntilFinished(1000);

    EXPECT_EQ(0u, brentMethod1.getNumberOfIterationsExecuted());
    EXPECT_EQ(2u, brentMethod2.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, GetCalculationValuesWorks)
{
    BrentMethod brentMethod(AlbaNumbers{1, 4, 4});
    brentMethod.resetCalculation(-4, 4);

    BrentMethod::CalculationValues calculationValues(brentMethod.getCalculationValues());

    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(4), calculationValues.a);
    EXPECT_EQ(AlbaNumber(-4), calculationValues.b);
    EXPECT_EQ(AlbaNumber(4), calculationValues.c);
    EXPECT_EQ(AlbaNumber(0), calculationValues.d);
    EXPECT_EQ(AlbaNumber(0), calculationValues.s);
    EXPECT_EQ(AlbaNumber(36), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(4), calculationValues.fb);
    EXPECT_TRUE(calculationValues.mflag);
}

TEST(BrentMethodTest, GetSolutionWorks)
{
    BrentMethod brentMethod1(AlbaNumbers{});
    BrentMethod brentMethod2(AlbaNumbers{1, 4, 4});
    brentMethod2.resetCalculation(-4, 4);
    brentMethod2.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution1(brentMethod1.getSolution());
    ASSERT_FALSE(solution1.hasContent());
    AlbaNumberOptional solution2(brentMethod2.getSolution());
    ASSERT_TRUE(solution2.hasContent());
    EXPECT_EQ(AlbaNumber(-2), solution2.getConstReference());
}

TEST(BrentMethodTest, ResetCalculationWorksBeforeRunning)
{
    BrentMethod brentMethod(AlbaNumbers{1, 4, 4});

    brentMethod.resetCalculation(-4, 4);

    BrentMethod::CalculationValues calculationValues(brentMethod.getCalculationValues());
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(4), calculationValues.a);
    EXPECT_EQ(AlbaNumber(-4), calculationValues.b);
    EXPECT_EQ(AlbaNumber(4), calculationValues.c);
    EXPECT_EQ(AlbaNumber(0), calculationValues.d);
    EXPECT_EQ(AlbaNumber(0), calculationValues.s);
    EXPECT_EQ(AlbaNumber(36), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(4), calculationValues.fb);
    EXPECT_TRUE(calculationValues.mflag);
}

TEST(BrentMethodTest, ResetCalculationWorksAfterRunning)
{
    BrentMethod brentMethod(AlbaNumbers{1, 4, 4});
    brentMethod.resetCalculation(-4, 4);
    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    brentMethod.resetCalculation(-4, 4);

    BrentMethod::CalculationValues calculationValues(brentMethod.getCalculationValues());
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(4), calculationValues.a);
    EXPECT_EQ(AlbaNumber(-4), calculationValues.b);
    EXPECT_EQ(AlbaNumber(4), calculationValues.c);
    EXPECT_EQ(AlbaNumber(0), calculationValues.d);
    EXPECT_EQ(AlbaNumber(0), calculationValues.s);
    EXPECT_EQ(AlbaNumber(36), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(4), calculationValues.fb);
    EXPECT_TRUE(calculationValues.mflag);
}

TEST(BrentMethodTest, ResetCalculationWorksWhenContinuouslyCalledBetweenRunning)
{
    BrentMethod brentMethod(AlbaNumbers{192, 200, -298, -315});

    brentMethod.resetCalculation(-315, -1.14592390790722);
    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);
    AlbaNumberOptional solution1(brentMethod.getSolution());
    ASSERT_TRUE(solution1.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(-7, 6), solution1.getConstReference());
    EXPECT_EQ(51u, brentMethod.getNumberOfIterationsExecuted());

    brentMethod.resetCalculation(-1.14592390790722, 0.451479463462771);
    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);
    AlbaNumberOptional solution2(brentMethod.getSolution());
    ASSERT_TRUE(solution2.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(-9, 8), solution2.getConstReference());
    EXPECT_EQ(42u, brentMethod.getNumberOfIterationsExecuted());

    brentMethod.resetCalculation(0.451479463462771, 315);
    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);
    AlbaNumberOptional solution3(brentMethod.getSolution());
    ASSERT_TRUE(solution3.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(5, 4), solution3.getConstReference());
    EXPECT_EQ(56u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunOneIterationWorks)
{
    BrentMethod brentMethod(AlbaNumbers{1, 1, -5, +3});
    brentMethod.resetCalculation(-4, AlbaNumber::createFraction(4, 3));

    cout.precision(20);

    brentMethod.runOneIteration(); //iteration 1: linear interpolation
    BrentMethod::CalculationValues calculationValues = brentMethod.getCalculationValues();
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(-4), calculationValues.a);
    EXPECT_EQ(AlbaNumber::createFraction(53, 43), calculationValues.b);
    EXPECT_EQ(AlbaNumber::createFraction(4, 3), calculationValues.c);
    EXPECT_EQ(AlbaNumber(-4), calculationValues.d);
    EXPECT_EQ(AlbaNumber::createFraction(53, 43), calculationValues.s);
    EXPECT_EQ(AlbaNumber(-25), calculationValues.fa);
    EXPECT_EQ(AlbaNumber::createFraction(18200, 79507), calculationValues.fb);
    EXPECT_FALSE(calculationValues.mflag);

    brentMethod.runOneIteration(); //iteration 2: inverse quadratic interpolation
    calculationValues = brentMethod.getCalculationValues();
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(-4), calculationValues.a);
    EXPECT_EQ(AlbaNumber(1.1420520085835), calculationValues.b);
    EXPECT_EQ(AlbaNumber::createFraction(53, 43), calculationValues.c);
    EXPECT_EQ(AlbaNumber::createFraction(4, 3), calculationValues.d);
    EXPECT_EQ(AlbaNumber(1.1420520085835), calculationValues.s);
    EXPECT_EQ(AlbaNumber(-25), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(0.0835815278260823), calculationValues.fb);
    EXPECT_FALSE(calculationValues.mflag);

    brentMethod.runOneIteration(); //iteration 3: inverse quadratic interpolation
    calculationValues = brentMethod.getCalculationValues();
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(-4), calculationValues.a);
    EXPECT_EQ(AlbaNumber(-1.42897399570825), calculationValues.b);
    EXPECT_EQ(AlbaNumber(1.1420520085835), calculationValues.c);
    EXPECT_EQ(AlbaNumber::createFraction(53, 43), calculationValues.d);
    EXPECT_EQ(AlbaNumber(-1.42897399570825), calculationValues.s);
    EXPECT_EQ(AlbaNumber(-25), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(9.26891937254249), calculationValues.fb);
    EXPECT_TRUE(calculationValues.mflag);

    brentMethod.runOneIteration(); //iteration 4: inverse quadratic interpolation
    calculationValues = brentMethod.getCalculationValues();
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(-4), calculationValues.a);
    EXPECT_EQ(AlbaNumber(-2.71448699785413), calculationValues.b);
    EXPECT_EQ(AlbaNumber(-1.42897399570825), calculationValues.c);
    EXPECT_EQ(AlbaNumber(1.1420520085835), calculationValues.d);
    EXPECT_EQ(AlbaNumber(-2.71448699785413), calculationValues.s);
    EXPECT_EQ(AlbaNumber(-25), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(3.93934099512347), calculationValues.fb);
    EXPECT_TRUE(calculationValues.mflag);

    brentMethod.runOneIteration(); //iteration 5: linear interpolation
    calculationValues = brentMethod.getCalculationValues();
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(-3.35724349892706), calculationValues.a);
    EXPECT_EQ(AlbaNumber(-2.71448699785413), calculationValues.b);
    EXPECT_EQ(AlbaNumber(-2.71448699785413), calculationValues.c);
    EXPECT_EQ(AlbaNumber(-1.42897399570825), calculationValues.d);
    EXPECT_EQ(AlbaNumber(-3.35724349892706), calculationValues.s);
    EXPECT_EQ(AlbaNumber(-6.78247178063835), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(3.93934099512347), calculationValues.fb);
    EXPECT_TRUE(calculationValues.mflag);

    brentMethod.runOneIteration(); //iteration 6: linear interpolation
    calculationValues = brentMethod.getCalculationValues();
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(-2.71448699785413), calculationValues.a);
    EXPECT_EQ(AlbaNumber(-3.03586524839059), calculationValues.b);
    EXPECT_EQ(AlbaNumber(-2.71448699785413), calculationValues.c);
    EXPECT_EQ(AlbaNumber(-2.71448699785413), calculationValues.d);
    EXPECT_EQ(AlbaNumber(-3.03586524839059), calculationValues.s);
    EXPECT_EQ(AlbaNumber(3.93934099512347), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(-0.584180636630816), calculationValues.fb);
    EXPECT_TRUE(calculationValues.mflag);

    //What happens is linear interpolation (secant), but inverse quadratic interpolation is expected
    brentMethod.runOneIteration(); //iteration 7:
    calculationValues = brentMethod.getCalculationValues();
    EXPECT_FALSE(calculationValues.solutionOptional);
    EXPECT_EQ(AlbaNumber(-2.87517612312236), calculationValues.a);
    EXPECT_EQ(AlbaNumber(-3.03586524839059), calculationValues.b);
    EXPECT_EQ(AlbaNumber(-3.03586524839059), calculationValues.c);
    EXPECT_EQ(AlbaNumber(-2.71448699785413), calculationValues.d);
    EXPECT_EQ(AlbaNumber(-2.87517612312236), calculationValues.s);
    EXPECT_EQ(AlbaNumber(1.87447890898756), calculationValues.fa);
    EXPECT_EQ(AlbaNumber(-0.584180636630816), calculationValues.fb);
    EXPECT_TRUE(calculationValues.mflag);
}


TEST(BrentMethodTest, RunWorksWithNoRealRoots)
{
    BrentMethod brentMethod(AlbaNumbers{1, 1, 1});
    brentMethod.resetCalculation(-1, 1);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_FALSE(solution.hasContent());
    EXPECT_EQ(1000u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnPerfectSquare)
{
    BrentMethod brentMethod(AlbaNumbers{1, 4, 4});
    brentMethod.resetCalculation(-4, 4);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_EQ(AlbaNumber(-2), solution.getConstReference());
    EXPECT_EQ(2u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnPerfectSquareWithACoefficient)
{
    BrentMethod brentMethod(AlbaNumbers{9, 6, 1});
    brentMethod.resetCalculation(-9, 9);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(-1, 3), solution.getConstReference());
    EXPECT_EQ(24u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnQuadraticExample)
{
    BrentMethod brentMethod(AlbaNumbers{24, -2, -35});
    brentMethod.resetCalculation(-35, 35);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(-7, 6), solution.getConstReference());
    EXPECT_EQ(44u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnDifferenceOfSquares)
{
    BrentMethod brentMethod(AlbaNumbers{1, 0, -256});
    brentMethod.resetCalculation(-256, 256);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_EQ(AlbaNumber(-16), solution.getConstReference());
    EXPECT_EQ(43u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnDifferenceOfCubes)
{
    BrentMethod brentMethod(AlbaNumbers{8, 0, 0, -27});
    brentMethod.resetCalculation(-27, 27);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(3, 2), solution.getConstReference());
    EXPECT_EQ(42u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnSumOfCubes)
{
    BrentMethod brentMethod(AlbaNumbers{8, 0, 0, 27});
    brentMethod.resetCalculation(-27, 27);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(-3, 2), solution.getConstReference());
    EXPECT_EQ(42u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnCubicExample)
{
    BrentMethod brentMethod(AlbaNumbers{192, 200, -298, -315});
    brentMethod.resetCalculation(-315, 315);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(5, 4), solution.getConstReference());
    EXPECT_EQ(57u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnQuarticExample_FailedExampleBasedOnInitialValues)
{
    BrentMethod brentMethod(AlbaNumbers{2112, -296, -5878, 409, 4095});
    brentMethod.resetCalculation(-4095, 4095);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_FALSE(solution.hasContent());
    EXPECT_EQ(1000u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnQuarticExample_SuccessfulExampleBasedOnInitialValues)
{
    BrentMethod brentMethod(AlbaNumbers{8448, -888, -11756, 409});
    brentMethod.resetCalculation(-8448, -0.646933510774966);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_DOUBLE_EQ(-1.1460171174121716, solution.getConstReference().getDouble());
    EXPECT_EQ(67u, brentMethod.getNumberOfIterationsExecuted());
}

TEST(BrentMethodTest, RunWorksOnQuarticExample)
{
    BrentMethod brentMethod(AlbaNumbers{1, 8, 24, 32, 16});
    brentMethod.resetCalculation(-16, 16);

    brentMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    AlbaNumberOptional solution(brentMethod.getSolution());
    ASSERT_TRUE(solution.hasContent());
    EXPECT_EQ(AlbaNumber(-2), solution.getConstReference());
    EXPECT_EQ(4u, brentMethod.getNumberOfIterationsExecuted());
}

}

}
