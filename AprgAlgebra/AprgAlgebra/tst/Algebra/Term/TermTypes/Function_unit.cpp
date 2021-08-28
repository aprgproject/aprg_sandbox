#include <Algebra/Term/TermTypes/Function.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(FunctionTest, ConstructionWorks)
{
    Function();
    Function("functionName", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
}

TEST(FunctionTest, GetFunctionNameWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_TRUE(function1.getFunctionName().empty());
    EXPECT_EQ("functionName", function2.getFunctionName());
}

TEST(FunctionTest, EqualityWorks)
{
    Function function1;
    Function function2("functionName1", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", Term(10), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_TRUE(function1==function1);
    EXPECT_FALSE(function1==function2);
    EXPECT_TRUE(function2==function2);
    EXPECT_FALSE(function2==function3);
    EXPECT_FALSE(function2==function4);
}

TEST(FunctionTest, InequalityOperatorWorks)
{
    Function function1;
    Function function2("functionName1", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", Term(10), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_FALSE(function1!=function1);
    EXPECT_TRUE(function1!=function2);
    EXPECT_FALSE(function2!=function2);
    EXPECT_TRUE(function2!=function3);
    EXPECT_TRUE(function2!=function4);
}

TEST(FunctionTest, LessThanOperatorWorks)
{
    Function function1;
    Function function2("functionName1", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", Term(10), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    EXPECT_FALSE(function1 < function1);
    EXPECT_FALSE(function2 < function2);
    EXPECT_TRUE(function1 < function2);
    EXPECT_TRUE(function2 < function3);
    EXPECT_TRUE(function3 < function4);
}

TEST(FunctionTest, IsInputExpressionAConstantWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName", Term("x"), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_FALSE(function1.isInputAConstant());
    EXPECT_TRUE(function2.isInputAConstant());
    EXPECT_FALSE(function3.isInputAConstant());
}

TEST(FunctionTest, PerformFunctionAndReturnResultIfPossibleWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName", Term("x"), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ(Constant(), function1.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ(Constant(5), function2.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ(Constant(), function3.performFunctionAndReturnResultIfPossible());
}

TEST(FunctionTest, GetInputExpressionConstReferenceWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ(Term(), getTermConstReferenceFromBaseTerm(function1.getInputTermConstReference()));
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(function2.getInputTermConstReference()));
}

TEST(FunctionTest, GetInputExpressionReferenceWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ(Term(), getTermConstReferenceFromBaseTerm(function1.getInputTermConstReference()));
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(function2.getInputTermConstReference()));
}

TEST(FunctionTest, SimplifyWorks)
{
    Function functionObject("functionName", Term(createExpressionIfPossible({Term(5), Term("+"), Term(5)})), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    functionObject.simplify();

    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
}

TEST(FunctionTest, GetDisplayableStringWorks)
{
    Function functionObject("functionName", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ("functionName(5)", functionObject.getDisplayableString());
}

TEST(FunctionTest, GetDebugStringWorks)
{
    Function functionObject("functionName", Term(5), [](AlbaNumber const&  number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ("functionName(5{Constant})", functionObject.getDebugString());
}

}

}
