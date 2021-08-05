#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

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
    Function absoluteValueFunction(abs(Term(-5)));

    EXPECT_EQ("abs", absoluteValueFunction.getFunctionName());
    EXPECT_EQ(Term(-5), getTermConstReferenceFromBaseTerm(absoluteValueFunction.getInputTermConstReference()));
    EXPECT_EQ(Constant(5), absoluteValueFunction.performFunctionAndReturnResultIfPossible());
}

}

}

}
