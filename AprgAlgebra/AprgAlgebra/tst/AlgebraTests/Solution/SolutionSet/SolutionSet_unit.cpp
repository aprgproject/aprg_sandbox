#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SolutionSetTest, IsEmptyWorks)
{
    SolutionSet solutionSet1;
    SolutionSet solutionSet2;
    SolutionSet solutionSet3;
    SolutionSet solutionSet4;
    solutionSet2.addAcceptedValue(45);
    solutionSet3.addRejectedValue(67);
    AlbaNumbers addedValuesToCheck{1};
    solutionSet4.determineAndAddAcceptedIntervals(addedValuesToCheck, [&](AlbaNumber const& numberToCheck)
    {
        return find(addedValuesToCheck.cbegin(), addedValuesToCheck.cend(), numberToCheck) == addedValuesToCheck.cend();
    });

    EXPECT_TRUE(solutionSet1.isEmpty());
    EXPECT_FALSE(solutionSet2.isEmpty());
    EXPECT_FALSE(solutionSet3.isEmpty());
    EXPECT_FALSE(solutionSet4.isEmpty());
}

TEST(SolutionSetTest, AddAcceptedValueWorks)
{
    SolutionSet solutionSet;

    solutionSet.addAcceptedValue(5863);

    EXPECT_EQ(AlbaNumbers{5863}, solutionSet.getAcceptedValues());
    EXPECT_TRUE(solutionSet.getRejectedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, AddRejectedValueWorks)
{
    SolutionSet solutionSet;

    solutionSet.addRejectedValue(5863);

    EXPECT_EQ(AlbaNumbers{5863}, solutionSet.getRejectedValues());
    EXPECT_TRUE(solutionSet.getAcceptedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, AddAcceptedValuesWorks)
{
    SolutionSet solutionSet;

    solutionSet.addAcceptedValues(AlbaNumbers{5863, 8546});

    EXPECT_EQ((AlbaNumbers{5863, 8546}), solutionSet.getAcceptedValues());
    EXPECT_TRUE(solutionSet.getRejectedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, AddRejectedValuesWorks)
{
    SolutionSet solutionSet;

    solutionSet.addRejectedValues(AlbaNumbers{5863, 8546});

    EXPECT_EQ((AlbaNumbers{5863, 8546}), solutionSet.getRejectedValues());
    EXPECT_TRUE(solutionSet.getAcceptedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, AddAcceptedIntervalWorks)
{
    SolutionSet solutionSet;

    solutionSet.addAcceptedInterval(AlbaNumberInterval(createOpenEndpoint(87), createOpenEndpoint(99)));

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(87), createOpenEndpoint(99)), actualIntervals.at(0));
}

TEST(SolutionSetTest, AddValueForAcceptedValueWorks)
{
    SolutionSet solutionSet;

    solutionSet.addValue(5863, [](AlbaNumber const&){return true;});

    EXPECT_EQ(AlbaNumbers{5863}, solutionSet.getAcceptedValues());
    EXPECT_TRUE(solutionSet.getRejectedValues().empty());
    EXPECT_TRUE(solutionSet.getAcceptedIntervals().empty());
}

TEST(SolutionSetTest, AddValueForRejectedValueWorks)
{
    SolutionSet solutionSet;

    solutionSet.addValue(5863, [](AlbaNumber const&){return false;});

    EXPECT_EQ(AlbaNumbers{5863}, solutionSet.getRejectedValues());
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
    ASSERT_EQ(2U, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(1)), actualIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createPositiveInfinityOpenEndpoint()), actualIntervals.at(1));
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
    ASSERT_EQ(3U, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(1)), actualIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createOpenEndpoint(2)), actualIntervals.at(1));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(2), createPositiveInfinityOpenEndpoint()), actualIntervals.at(2));
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
    ASSERT_EQ(3U, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(1)), actualIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createOpenEndpoint(2)), actualIntervals.at(1));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(2), createPositiveInfinityOpenEndpoint()), actualIntervals.at(2));
}

TEST(SolutionSetTest, DetermineAndAddAcceptedIntervalsWorksWithRedundantInfinities)
{
    SolutionSet solutionSet;

    AlbaNumbers addedValuesToCheck{
        1,
        AlbaNumber::Value::PositiveInfinity,
                AlbaNumber::Value::NegativeInfinity,
                AlbaNumber::Value::PositiveInfinity,
                AlbaNumber::Value::NegativeInfinity};
    AlbaNumbers valuesThatAreNotAccepted{1};
    solutionSet.determineAndAddAcceptedIntervals(addedValuesToCheck, [&](AlbaNumber const& numberToCheck)
    {
        return find(valuesThatAreNotAccepted.cbegin(), valuesThatAreNotAccepted.cend(), numberToCheck) == valuesThatAreNotAccepted.cend();
    });

    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2U, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(1)), actualIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(1), createPositiveInfinityOpenEndpoint()), actualIntervals.at(1));
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
    ASSERT_EQ(3U, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(4)), actualIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(4), createOpenEndpoint(5)), actualIntervals.at(1));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(5), createPositiveInfinityOpenEndpoint()), actualIntervals.at(2));
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
    ASSERT_EQ(2U, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(2)), actualIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(2), createPositiveInfinityOpenEndpoint()), actualIntervals.at(1));
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
    ASSERT_EQ(2U, actualIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(1)), actualIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(2), createPositiveInfinityOpenEndpoint()), actualIntervals.at(1));
}

TEST(SolutionSetTest, GetDisplayableStringWorks)
{
    SolutionSet solutionSet;
    solutionSet.addAcceptedValue(3.7);
    solutionSet.addAcceptedValue(5.6);
    solutionSet.addRejectedValue(6.5);
    solutionSet.addAcceptedInterval(AlbaNumberInterval(createOpenEndpoint(87), createOpenEndpoint(99)));

    EXPECT_EQ("AcceptedValues: : [{size: 2 | 3.7, 5.6, }] RejectedValues: : [{size: 1 | 6.5, }] AcceptedIntervals: : [{size: 1 | (87, 99), }]",
              solutionSet.getDisplayableString());
}

}
}
