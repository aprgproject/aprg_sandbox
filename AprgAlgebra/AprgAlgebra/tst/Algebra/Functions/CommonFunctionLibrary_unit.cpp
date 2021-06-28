#include <Algebra/Functions/CommonFunctionLibrary.hpp>

#include <Algebra/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Functions
{

TEST(CommonFunctionLibraryTest, AbsoluteValueWorks)
{
    Function absoluteValueFunction(abs(createOrCopyExpressionFromATerm(Term(-5))));

    Expression expressionToExpect(createOrCopyExpressionFromATerm(Term(-5)));
    Constant constantToExpect(5);
    EXPECT_EQ("abs", absoluteValueFunction.getFunctionName());
    EXPECT_EQ(expressionToExpect, absoluteValueFunction.getInputExpressionConstReference());
    EXPECT_EQ(constantToExpect, absoluteValueFunction.performFunctionAndReturnResultIfPossible());
}

}

}

}
