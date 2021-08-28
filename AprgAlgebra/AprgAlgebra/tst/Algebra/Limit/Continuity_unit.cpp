#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

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

    EXPECT_TRUE(isContinuousAt(functionTermToTest, "x", 10));
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

    EXPECT_FALSE(isContinuousAt(functionTermToTest, "x", 1));
}

TEST(ContinuityTest, GetContinuityTypeAtWorksForRemovableDiscontinuityFunction)
{
    Function functionToTest(
                "functionToTest",
                getBaseTermConstReferenceFromTerm(Term("x")),
                [](AlbaNumber const& number)
    {
        AlbaNumber result;
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

}

}
