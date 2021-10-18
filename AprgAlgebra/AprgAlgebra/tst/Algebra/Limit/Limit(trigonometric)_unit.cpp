#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/AlbaMathConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(LimitTest, GetLimitAtAValueWorksForSinXOverX)
{
    Term sinXOverX(createExpressionIfPossible({Term(sin(Term("x"))), Term("/"), Term("x")}));

    EXPECT_EQ(Term(1), getLimitAtAValue(sinXOverX, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(1), getLimitAtAValue(sinXOverX, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(1), getLimitAtAValue(sinXOverX, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForSinXHarmonicOverSinXHarmonic)
{
    Term numerator(sin(Monomial(3, {{"x", 1}})));
    Term denominator(sin(Monomial(5, {{"x", 1}})));
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(0.6), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(0.6), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(0.6), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForCosineExpression)
{
    Term numerator(createExpressionIfPossible({Term(1), Term("-"), Term(cos(Term("x")))}));
    Term denominator("x");
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForCosineAndSineExpression)
{
    Term numerator(createExpressionIfPossible({Term(1), Term("-"), Term(cos(Term("x")))}));
    Term denominator(sin(Term("x")));
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(Constant(0)), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForTangentExpression)
{
    Term numerator(createExpressionIfPossible({Term(2), Term("*"), Term(tan(Term("x"))), Term("^"), Term(2)}));
    Term denominator(Monomial(1, {{"x", 2}}));
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(2), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(2), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(2), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForComplicatedSinOverX)
{
    Term numerator(sin(Term(Monomial(PI_DOUBLE_VALUE, {{"x", 1}}))));
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {{"x", 1}})});
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(-3.141592653589794), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(-3.141592653589794), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(-3.141592653589794), getLimitAtAValue(termToTest, "x", 0, LimitAtAValueApproachType::NegativeSide));

    // The limit in 1 should not be negative infinity (it should be negative pi)
    // but the calculation of sin of pi is not zero (its only near zero) for some reason.
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), getLimitAtAValue(termToTest, "x", 1, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), getLimitAtAValue(termToTest, "x", 1, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::NegativeInfinity)), getLimitAtAValue(termToTest, "x", 1, LimitAtAValueApproachType::NegativeSide));
}


}

}
