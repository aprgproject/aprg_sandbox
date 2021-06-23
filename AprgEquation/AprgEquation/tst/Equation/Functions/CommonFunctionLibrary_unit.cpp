#include <Equation/Functions/CommonFunctionLibrary.hpp>

#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

namespace Functions
{

TEST(CommonFunctionLibraryTest, AbsoluteValueWorks)
{
    Function absoluteValueFunction(abs(createOrCopyExpressionFromATerm(Term(-5))));

    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(-5)));
    Constant constantToExpect(5);
    EXPECT_EQ("abs", absoluteValueFunction.getFunctionName());
    EXPECT_EQ(expressionToExpect, absoluteValueFunction.getExpression());
    EXPECT_EQ(constantToExpect, absoluteValueFunction.performFunctionAndReturnResultIfPossible());
}

}

}

}
