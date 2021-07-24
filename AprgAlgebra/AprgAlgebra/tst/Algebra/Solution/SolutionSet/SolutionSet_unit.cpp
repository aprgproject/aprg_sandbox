#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>

#include <gtest/gtest.h>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SolutionSetTest, AddAcceptedValueWorksAsExpected)
{
    SolutionSet solutionSet;

    solutionSet.addAcceptedValue(5863);

    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    ASSERT_EQ(1u, acceptedValues.size());
    EXPECT_EQ(5863, acceptedValues.back().getInteger());
    EXPECT_TRUE(solutionSet.getRejectedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, AddRejectedValueWorksAsExpected)
{
    SolutionSet solutionSet;

    solutionSet.addRejectedValue(5863);

    AlbaNumbers const& rejectedValues(solutionSet.getRejectedValues());
    ASSERT_EQ(1u, rejectedValues.size());
    EXPECT_EQ(5863, rejectedValues.back().getInteger());
    EXPECT_TRUE(solutionSet.getAcceptedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, AddValueForAcceptedValueWorksAsExpected)
{
    SolutionSet solutionSet;

    solutionSet.addValue(5863, [](AlbaNumber const&){return true;});

    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    ASSERT_EQ(1u, acceptedValues.size());
    EXPECT_EQ(5863, acceptedValues.back().getInteger());
    EXPECT_TRUE(solutionSet.getRejectedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, AddValueForRejectedValueWorksAsExpected)
{
    SolutionSet solutionSet;

    solutionSet.addValue(5863, [](AlbaNumber const&){return false;});

    AlbaNumbers const& rejectedValues(solutionSet.getRejectedValues());
    ASSERT_EQ(1u, rejectedValues.size());
    EXPECT_EQ(5863, rejectedValues.back().getInteger());
    EXPECT_TRUE(solutionSet.getAcceptedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, DetermineAndAddAcceptedIntervalsWorksWithOnePoint)
{
    SolutionSet solutionSet;

    AlbaNumbers addedValuesToCheck{1};
    solutionSet.determineAndAddAcceptedIntervals(addedValuesToCheck, [&](AlbaNumber const& numberToCheck)
    {
        return find(addedValuesToCheck.cbegin(), addedValuesToCheck.cend(), numberToCheck) == addedValuesToCheck.cend();
    });

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2u, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(1)), actualIntervals[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), actualIntervals[1]);
}

TEST(SolutionSetTest, DetermineAndAddAcceptedIntervalsWorksWithAcceptedValue)
{
    SolutionSet solutionSet;
    solutionSet.addAcceptedValue(2);

    AlbaNumbers addedValuesToCheck{1};
    AlbaNumbers valuesThatAreNotAccepted{1,2};
    solutionSet.determineAndAddAcceptedIntervals(addedValuesToCheck, [&](AlbaNumber const& numberToCheck)
    {
        return find(valuesThatAreNotAccepted.cbegin(), valuesThatAreNotAccepted.cend(), numberToCheck) == valuesThatAreNotAccepted.cend();
    });

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(3u, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(1)), actualIntervals[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createOpenEndpoint(2)), actualIntervals[1]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(2), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), actualIntervals[2]);
}

TEST(SolutionSetTest, DetermineAndAddAcceptedIntervalsWorksWithRejectedValue)
{
    SolutionSet solutionSet;
    solutionSet.addRejectedValue(2);

    AlbaNumbers addedValuesToCheck{1};
    AlbaNumbers valuesThatAreNotAccepted{1,2};
    solutionSet.determineAndAddAcceptedIntervals(addedValuesToCheck, [&](AlbaNumber const& numberToCheck)
    {
        return find(valuesThatAreNotAccepted.cbegin(), valuesThatAreNotAccepted.cend(), numberToCheck) == valuesThatAreNotAccepted.cend();
    });

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(3u, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(1)), actualIntervals[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createOpenEndpoint(2)), actualIntervals[1]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(2), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), actualIntervals[2]);
}

TEST(SolutionSetTest, DetermineAndAddAcceptedIntervalsWorksWithRedundantInfinities)
{
    SolutionSet solutionSet;

    AlbaNumbers addedValuesToCheck{1, INFINITY, -INFINITY, INFINITY, -INFINITY};
    AlbaNumbers valuesThatAreNotAccepted{1};
    solutionSet.determineAndAddAcceptedIntervals(addedValuesToCheck, [&](AlbaNumber const& numberToCheck)
    {
        return find(valuesThatAreNotAccepted.cbegin(), valuesThatAreNotAccepted.cend(), numberToCheck) == valuesThatAreNotAccepted.cend();
    });

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2u, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(1)), actualIntervals[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), actualIntervals[1]);
}

TEST(SolutionSetTest, DetermineAndAddAcceptedIntervalsWorksWithAllKindOfIntervalsIncluded)
{
    SolutionSet solutionSet;

    AlbaNumbers valuesThatAreNotAccepted{4,5};
    solutionSet.determineAndAddAcceptedIntervals(valuesThatAreNotAccepted, [&](AlbaNumber const& numberToCheck)
    {
        return find(valuesThatAreNotAccepted.cbegin(), valuesThatAreNotAccepted.cend(), numberToCheck) == valuesThatAreNotAccepted.cend();
    });

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(3u, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(4)), actualIntervals[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(4), createOpenEndpoint(5)), actualIntervals[1]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(5), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), actualIntervals[2]);
}

TEST(SolutionSetTest, DetermineAndAddAcceptedIntervalsWorksWithAllConnectedIntervalsCombined)
{
    SolutionSet solutionSet;

    AlbaNumbers addedValuesToCheck{1,2,3};
    AlbaNumbers valuesThatAreNotAccepted{2};
    solutionSet.determineAndAddAcceptedIntervals(addedValuesToCheck, [&](AlbaNumber const& numberToCheck)
    {
        return find(valuesThatAreNotAccepted.cbegin(), valuesThatAreNotAccepted.cend(), numberToCheck) == valuesThatAreNotAccepted.cend();
    });

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2u, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(2)), actualIntervals[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(2), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), actualIntervals[1]);
}

TEST(SolutionSetTest, DetermineAndAddAcceptedIntervalsWorksAndNotAcceptedIntervalsNotIncluded)
{
    SolutionSet solutionSet;

    AlbaNumbers addedValuesToCheck{1,2};
    AlbaNumbers valuesThatAreNotAccepted{1, 1.5, 2};
    solutionSet.determineAndAddAcceptedIntervals(addedValuesToCheck, [&](AlbaNumber const& numberToCheck)
    {
        return find(valuesThatAreNotAccepted.cbegin(), valuesThatAreNotAccepted.cend(), numberToCheck) == valuesThatAreNotAccepted.cend();
    });

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2u, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(1)), actualIntervals[0]);
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(2), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), actualIntervals[1]);
}

}

}
