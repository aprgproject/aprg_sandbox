#include <Algebra/Solution/DomainAndRange/Domain.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Domain
{

TEST(DomainTest, CalculateDomainWorksWithTerm)
{
    Polynomial polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})};
    Expression expression(createExpressionIfPossible({Term(polynomial), Term("^"), Term(AlbaNumber(1, 2))}));

    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(Term(expression));

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-2), createCloseEndpoint(2)), acceptedIntervals.at(0));
}

TEST(DomainTest, CalculateDomainWorksWithTermWithValues)
{
    AlbaNumbers value{1.3, 9.25};
    Polynomial polynomial{Monomial(4, {}), Monomial(-1, {{"x", 2}})};
    Expression expression(createExpressionIfPossible({Term(polynomial), Term("^"), Term(AlbaNumber(1, 2))}));

    SolutionSet actualDomain = calculateDomainForTermWithOneVariable(value, Term(expression));

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createCloseEndpoint(2)), acceptedIntervals.at(0));
}

TEST(DomainTest, CalculateDomainWorksWithFunction)
{
    AlbaNumbers value{5, 9.25};

    SolutionSet actualDomain = calculateDomain(value, [](AlbaNumber const& number)
    {
        return (number-6)^0.5;
    });

    AlbaNumberIntervals acceptedIntervals(actualDomain.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(6), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), acceptedIntervals.at(0));
}

TEST(DomainTest, GetTransitionValuesWorks)
{
    AlbaNumbers value{5, 9.25};

    AlbaNumbers actualTransitionValues = getTransitionValues(value, [](AlbaNumber const& number)
    {
        return (number-6)^0.5;
    });

    ASSERT_EQ(1u, actualTransitionValues.size());
    EXPECT_EQ(AlbaNumber(6), actualTransitionValues.at(0));
}

TEST(DomainTest, GetTransitionValueWorks)
{

    AlbaNumber actualTransitionValue = getTransitionValue(
                AlbaNumber(9.25),
                AlbaNumber(5),
                [](AlbaNumber const& number)
    {
        return (number-6)^0.5;
    });

    EXPECT_EQ(AlbaNumber(6), actualTransitionValue);
}

}

}

}
