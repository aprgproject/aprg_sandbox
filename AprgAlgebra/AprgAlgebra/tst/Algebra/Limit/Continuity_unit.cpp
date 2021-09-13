#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>
using namespace alba::mathHelper;
using namespace std;
namespace alba
{

namespace algebra
{

TEST(ContinuityTest, IsContinuousAtWorksForContinuousPieceWiseFunction)
{
    Function functionToTest(
                "functionToTest",
                getBaseTermConstReferenceFromTerm(Term("x")),
                [](AlbaNumber const& number)
    {
        AlbaNumber result;
        if(number <= 10)
        {
            result = number;
        }
        else
        {
            result = number*0.7 + 3;
        }
        return result;
    });
    Term functionTermToTest(functionToTest);

    EXPECT_TRUE(isContinuousAt(functionTermToTest, "x", 10, LimitAtAValueApproachType::BothSides));
}

TEST(ContinuityTest, IsContinuousAtWorksForDiscontinuousPieceWiseFunction)
{
    Function functionToTest(
                "functionToTest",
                getBaseTermConstReferenceFromTerm(Term("x")),
                [](AlbaNumber const& number)
    {
        AlbaNumber result;
        if(number == 1)
        {
            result = 2;
        }
        else
        {
            result = number*2 + 3;
        }
        return result;
    });
    Term functionTermToTest(functionToTest);

    EXPECT_FALSE(isContinuousAt(functionTermToTest, "x", 1, LimitAtAValueApproachType::BothSides));
}

TEST(ContinuityTest, IsContinuousAtWorksOnTheEdgesOfSquareRootOfPolynomial)
{
    Term polynomialTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {})});
    Term termToTest(createExpressionIfPossible({polynomialTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    EXPECT_FALSE(isContinuousAt(termToTest, "x", -2, LimitAtAValueApproachType::BothSides));
    EXPECT_TRUE(isContinuousAt(termToTest, "x", -2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_FALSE(isContinuousAt(termToTest, "x", -2, LimitAtAValueApproachType::NegativeSide));
    EXPECT_FALSE(isContinuousAt(termToTest, "x", 2, LimitAtAValueApproachType::BothSides));
    EXPECT_FALSE(isContinuousAt(termToTest, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_TRUE(isContinuousAt(termToTest, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(ContinuityTest, IsIntermediateValueTheoremSatisfiedWorks)
{
    Polynomial numerator{Monomial(2, {})};
    Polynomial denominator{Monomial(1, {{"x", 1}}), Monomial(-4, {})};
    Term termToTest(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));

    EXPECT_FALSE(isIntermediateValueTheoremSatisfied(termToTest, "x", 2, 5, 4));
    EXPECT_TRUE(isIntermediateValueTheoremSatisfied(termToTest, "x", 5, 7, 6));
}

TEST(ContinuityTest, GetContinuityTypeAtWorksForRemovableDiscontinuityFunction)
{
    Function functionToTest(                "functionToTest",
                getBaseTermConstReferenceFromTerm(Term("x")),
                [](AlbaNumber const& number)
    {        AlbaNumber result;
        if(number == 3)
        {
            result = 2;
        }
        else
        {
            result = getAbsoluteValueForAlbaNumber(number - 3);
        }
        return result;
    });
    Term functionTermToTest(functionToTest);

    EXPECT_EQ(ContinuityType::DiscontinuousWithRemovableDiscontinuity,
              getContinuityTypeAt(functionTermToTest, "x", 3));
}

TEST(ContinuityTest, GetContinuityTypeAtWorksForEssentialDiscontinuityFunction)
{
    Function functionToTest(
                "functionToTest",
                getBaseTermConstReferenceFromTerm(Term("x")),
                [](AlbaNumber const& number)
    {
        AlbaNumber result;
        if(number <= 1)
        {
            result = number + 3;
        }
        else
        {
            result = number - 3;
        }
        return result;
    });
    Term functionTermToTest(functionToTest);

    EXPECT_EQ(ContinuityType::DiscontinuousWithEssentialDiscontinuity,
              getContinuityTypeAt(functionTermToTest, "x", 1));
}

TEST(ContinuityTest, GetContinuityTypeAtWorksForPolynomialOverPolynomial)
{
    Polynomial numerator{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})};
    Polynomial denominator{Monomial(1, {{"x", 1}}), Monomial(-4, {})};
    Term termToTest(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));

    EXPECT_EQ(ContinuityType::DiscontinuousWithRemovableDiscontinuity,
              getContinuityTypeAt(termToTest, "x", 4));
}

TEST(ContinuityTest, GetContinuityDomainWorksOnPolynomial)
{
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(1, {})});

    SolutionSet continuityDomain(getContinuityDomain(polynomialTerm));

    AlbaNumberIntervals const& intervalToVerify(continuityDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify.size());
    EXPECT_EQ(createAllRealValuesInterval(), intervalToVerify.front());
}

TEST(ContinuityTest, GetContinuityDomainWorksOnPolynomialOverPolynomial)
{
    Polynomial numerator{Monomial(1, {{"x", 3}}), Monomial(1, {})};
    Polynomial denominator{Monomial(1, {{"x", 2}}), Monomial(-9, {})};
    Term termToTest(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));

    SolutionSet continuityDomain(getContinuityDomain(termToTest));

    AlbaNumberIntervals const& intervalToVerify(continuityDomain.getAcceptedIntervals());
    ASSERT_EQ(3U, intervalToVerify.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(-3)),
              intervalToVerify.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-3), createOpenEndpoint(3)),
              intervalToVerify.at(1));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(3), createPositiveInfinityOpenEndpoint()),
              intervalToVerify.at(2));
}
TEST(ContinuityTest, GetContinuityDomainWorksOnSquareRootOfPolynomial)
{
    Term polynomialTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {})});    Term termToTest(createExpressionIfPossible({polynomialTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    SolutionSet continuityDomain(getContinuityDomain(termToTest));

    AlbaNumberIntervals const& intervalToVerify(continuityDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify.size());
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-2), createCloseEndpoint(2)), intervalToVerify.at(0));
}

}

}
