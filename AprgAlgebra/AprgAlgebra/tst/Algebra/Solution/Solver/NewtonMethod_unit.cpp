#include <Algebra/Solution/Solver/NewtonMethod.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(NewtonMethodTest, ConstructionWorks)
{
    NewtonMethod(16, [](AlbaNumber const& number)
    {
        return (number^2)-16;
    });
}

TEST(NewtonMethodTest, IsSolvedWorks)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod1(4, functionToIterate);
    NewtonMethod newtonMethod2(16, functionToIterate);

    EXPECT_TRUE(newtonMethod1.isSolved());
    EXPECT_FALSE(newtonMethod2.isSolved());
}

TEST(NewtonMethodTest, IsFinishedWorks)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod1(4, functionToIterate);
    NewtonMethod newtonMethod2(16, functionToIterate);
    NewtonMethod newtonMethod3(AlbaNumber::Value::PositiveInfinity, functionToIterate);

    EXPECT_TRUE(newtonMethod1.isFinished());
    EXPECT_FALSE(newtonMethod2.isFinished());    EXPECT_TRUE(newtonMethod3.isFinished());
}

TEST(NewtonMethodTest, GetNumberOfIterationsExecutedWorksWhenNoIterationsAreExecuted){
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod(5, functionToIterate);

    EXPECT_EQ(0u, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, GetNumberOfIterationsExecutedWorksWhenOneIterationIsExecuted)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod(5, functionToIterate);
    newtonMethod.runOneIteration();

    EXPECT_EQ(1u, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, GetCurrentComputedValueWorks)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod(5, functionToIterate);

    EXPECT_EQ(AlbaNumber(5), newtonMethod.getCurrentComputedValue());
}

TEST(NewtonMethodTest, RunOneIterationWorks)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runOneIteration();

    EXPECT_EQ(AlbaNumber(8.5000000043790038262), newtonMethod.getCurrentComputedValue());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedWorksWhenMaxIterationIsReached)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(4);

    EXPECT_EQ(AlbaNumber(4.0022575248056222463), newtonMethod.getCurrentComputedValue());
    EXPECT_EQ(4u, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedWorksWhenMaxIterationIsNotReached)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(100);

    EXPECT_EQ(AlbaNumber(4), newtonMethod.getCurrentComputedValue());
    EXPECT_EQ(6u, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedWorks)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^2)-16;
    };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runUntilFinished();

    EXPECT_EQ(AlbaNumber(4), newtonMethod.getCurrentComputedValue());
    EXPECT_EQ(6u, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedWorksForXToXForm)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^number)-256;
    };
    NewtonMethod newtonMethod(16, functionToIterate);

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(100);

    EXPECT_EQ(AlbaNumber(4), newtonMethod.getCurrentComputedValue());
    EXPECT_EQ(44u, newtonMethod.getNumberOfIterationsExecuted());
}

TEST(NewtonMethodTest, RunMaxNumberOfIterationsOrUntilFinishedFailsToGetSolutionWithXToXForm)
{
    NewtonMethod::Function functionToIterate = [](AlbaNumber const& number)
    {
        return (number^number) + 823543;
    };
    NewtonMethod newtonMethod(-16, functionToIterate);

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(100);

    EXPECT_TRUE(newtonMethod.getCurrentComputedValue().isNegativeInfinity());
    EXPECT_EQ(1u, newtonMethod.getNumberOfIterationsExecuted());
}

}

}
