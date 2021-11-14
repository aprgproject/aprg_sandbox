#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Vector/MathVectorOfTerms.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(MathVectorOfTermsTest, GettingMagnitudeWorks)
{
    Term t("t");
    Term x(createExpressionIfPossible({Term(2), Term("*"), Term(cos(t))}));
    Term y(createExpressionIfPossible({Term(2), Term("*"), Term(sin(t))}));
    MathVectorOfTwoTerms termVector{x, y};

    Term magnitude(termVector.getMagnitude());
    magnitude.simplify();

    string stringToExpect("((((2*cos(t))^2)+((2*sin(t))^2))^(1/2))");
    EXPECT_EQ(stringToExpect, magnitude.getDisplayableString());
}
}

}
