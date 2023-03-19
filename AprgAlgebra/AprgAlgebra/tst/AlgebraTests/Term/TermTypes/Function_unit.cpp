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
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_TRUE(function1.getFunctionName().empty());
    EXPECT_EQ(Term(), getTermConstReferenceFromBaseTerm(function1.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(), function1.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ("functionName", function2.getFunctionName());
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(function2.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(5), function2.performFunctionAndReturnResultIfPossible());
}

TEST(FunctionTest, FunctionThatIsDefaultConstructedHasIsSimplifiedFlagNotSet)
{
    Function function;

    EXPECT_FALSE(function.isSimplified());
}

TEST(FunctionTest, FunctionThatIsCopyConstructedHasIsSimplifiedFlagCopied)
{
    Function functionWithSimplifiedNotSet;
    Function functionWithSimplifiedSet;
    functionWithSimplifiedSet.setAsSimplified();

    EXPECT_FALSE(functionWithSimplifiedNotSet.isSimplified());
    EXPECT_TRUE(functionWithSimplifiedSet.isSimplified());
}

TEST(FunctionTest, IsSimplifiedWorks)
{
    Function function1;
    Function function2;
    function2.setAsSimplified();

    EXPECT_FALSE(function1.isSimplified());
    EXPECT_TRUE(function2.isSimplified());
}

TEST(FunctionTest, EqualityWorks)
{
    Function function1;
    Function function2("functionName1", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", Term(10), [](AlbaNumber const& number) -> AlbaNumber
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
    Function function2("functionName1", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", Term(10), [](AlbaNumber const& number) -> AlbaNumber
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
    Function function2("functionName1", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName2", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function4("functionName2", Term(10), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    EXPECT_FALSE(function1 < function1);
    EXPECT_FALSE(function2 < function2);
    EXPECT_TRUE(function1 < function2);
    EXPECT_TRUE(function2 < function3);
    EXPECT_TRUE(function3 < function4);
}

TEST(FunctionTest, GetFunctionNameWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_TRUE(function1.getFunctionName().empty());
    EXPECT_EQ("functionName", function2.getFunctionName());
}

TEST(FunctionTest, GetDebugStringWorks)
{
    Function functionObject("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ("functionName(5{Constant})", functionObject.getDebugString());
}

TEST(FunctionTest, PerformFunctionAndReturnResultIfPossibleWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName", Term("x"), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ(AlbaNumber(), function1.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ(AlbaNumber(5), function2.performFunctionAndReturnResultIfPossible());
    EXPECT_EQ(AlbaNumber(), function3.performFunctionAndReturnResultIfPossible());
}

TEST(FunctionTest, GetInputTermConstReferenceWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });

    EXPECT_EQ(Term(), getTermConstReferenceFromBaseTerm(function1.getInputTermConstReference()));
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(function2.getInputTermConstReference()));
}

TEST(FunctionTest, GetEvaluationFunctionWorks)
{
    Function::EvaluationFunction evaluationFunction =  [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    };
    Function functionObject("functionName", Term(5), evaluationFunction);

    Function::EvaluationFunction const& evaluationFunctionToVerify(functionObject.getEvaluationFunction());
    EXPECT_EQ(AlbaNumber(100), evaluationFunctionToVerify(100));
}

TEST(FunctionTest, GetInputTermReferenceWorks)
{
    Function functionObject;

    Term & inputTermToChange(getTermReferenceFromBaseTerm(functionObject.getInputTermReference()));
    inputTermToChange = Term(10);

    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
}

TEST(FunctionTest, SimplifyWorks)
{
    Function::EvaluationFunction evaluationFunction =  [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    };
    Function functionObject("functionName", Term(createExpressionIfPossible({5, "+", 5})), evaluationFunction);

    functionObject.simplify();

    EXPECT_EQ("functionName", functionObject.getFunctionName());
    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    Function::EvaluationFunction const& evaluationFunctionToVerify(functionObject.getEvaluationFunction());
    EXPECT_EQ(AlbaNumber(100), evaluationFunctionToVerify(100));
}

TEST(FunctionTest, SimplifyWorksWhenIsSimplifiedIsNotSet)
{
    Function::EvaluationFunction evaluationFunction =  [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    };
    Function functionObject("functionName", Term(createExpressionIfPossible({5, "+", 5})), evaluationFunction);

    functionObject.simplify();

    EXPECT_EQ("functionName", functionObject.getFunctionName());
    EXPECT_EQ(Term(10), getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    Function::EvaluationFunction const& evaluationFunctionToVerify(functionObject.getEvaluationFunction());
    EXPECT_EQ(AlbaNumber(100), evaluationFunctionToVerify(100));
}

TEST(FunctionTest, SimplifyWorksAsSkippedWhenIsSimplifiedIsSet)
{
    Function::EvaluationFunction evaluationFunction =  [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    };
    Function functionObject("functionName", Term(createExpressionIfPossible({5, "+", 5})), evaluationFunction);
    functionObject.setAsSimplified();

    functionObject.simplify();

    Term inputTermToExpect(createExpressionIfPossible({5, "+", 5}));
    EXPECT_EQ("functionName", functionObject.getFunctionName());
    EXPECT_EQ(inputTermToExpect, getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    Function::EvaluationFunction const& evaluationFunctionToVerify(functionObject.getEvaluationFunction());
    EXPECT_EQ(AlbaNumber(100), evaluationFunctionToVerify(100));
}

TEST(FunctionTest, SetAsSimplifiedWorks)
{
    Function functionObject;

    functionObject.setAsSimplified();

    EXPECT_TRUE(functionObject.isSimplified());
}

TEST(FunctionTest, ClearSimplifiedFlagWorks)
{
    Function functionObject;
    functionObject.setAsSimplified();

    functionObject.clearSimplifiedFlag();

    EXPECT_FALSE(functionObject.isSimplified());
}

TEST(FunctionTest, ClearAllInnerSimplifiedFlagsWorks)
{
    Term inputTerm;
    inputTerm.setAsSimplified();
    Function functionObject("functionName1", inputTerm, [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    functionObject.setAsSimplified();
    EXPECT_TRUE(functionObject.isSimplified());
    EXPECT_TRUE(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()).isSimplified());

    functionObject.clearAllInnerSimplifiedFlags();

    EXPECT_FALSE(functionObject.isSimplified());
    EXPECT_FALSE(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()).isSimplified());
}

TEST(FunctionTest, OutputStreamOperatorWorks)
{
    stringstream ss;
    Function functionObject("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });

    ss << functionObject;

    EXPECT_EQ("functionName(5)", ss.str());
}

}

}
