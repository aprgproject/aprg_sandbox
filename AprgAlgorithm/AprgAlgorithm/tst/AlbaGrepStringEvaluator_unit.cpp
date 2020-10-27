#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba;

TEST(AlbaGrepStringEvaluatorTest, FalseIsReturnedWhenconditionIsEmpty)
{
    AlbaGrepStringEvaluator evaluator("");
    EXPECT_TRUE(evaluator.isInvalid());
    EXPECT_FALSE(evaluator.evaluate("TestString"));
}

TEST(AlbaGrepStringEvaluatorTest, FalseIsReturnedWhenThereAreNoConvertedTerms)
{
    AlbaGrepStringEvaluator evaluator("TestString");
    EXPECT_TRUE(evaluator.isInvalid());
    EXPECT_FALSE(evaluator.evaluate("TestString"));
}

TEST(AlbaGrepStringEvaluatorTest, EvaluatorIsInvalidWhenOperandIsMissingForPrefixOperator)
{
    AlbaGrepStringEvaluator evaluator(" ! ");
    EXPECT_TRUE(evaluator.isInvalid());
}

TEST(AlbaGrepStringEvaluatorTest, EvaluatorIsInvalidWhen1OperandIsMissingForBiDirectionalOperator)
{
    AlbaGrepStringEvaluator evaluator("[TestString] || ");
    EXPECT_TRUE(evaluator.isInvalid());
}

TEST(AlbaGrepStringEvaluatorTest, EvaluatorIsInvalidWhenOperandsAreMissingForBiDirectionalOperator)
{
    AlbaGrepStringEvaluator evaluator(" || ");
    EXPECT_TRUE(evaluator.isInvalid());
}

TEST(AlbaGrepStringEvaluatorTest, FalseIsReturnedWhenEvaluateStringIsEmpty)
{
    AlbaGrepStringEvaluator evaluator("[TestString123]");
    EXPECT_FALSE(evaluator.isInvalid());
    EXPECT_FALSE(evaluator.evaluate(""));
}

TEST(AlbaGrepStringEvaluatorTest, TrueIsReturnedWhenStringIsFound)
{
    AlbaGrepStringEvaluator evaluator("[TestString123]");
    EXPECT_FALSE(evaluator.isInvalid());
    EXPECT_TRUE(evaluator.evaluate("TestString123"));
}

TEST(AlbaGrepStringEvaluatorTest, TrueIsReturnedWhenStringIsFoundWithDifferentCase)
{
    AlbaGrepStringEvaluator evaluator("[tESTsTRING123]");
    EXPECT_FALSE(evaluator.isInvalid());
    EXPECT_TRUE(evaluator.evaluate("TestString123"));
}

TEST(AlbaGrepStringEvaluatorTest, NotOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("![StringDoesNotExist1]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_TRUE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("![hungry]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_FALSE(evaluator2.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, NotOperatorCombinationWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("!!!![StringDoesNotExist1]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_FALSE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("!~!~!~~[hungry]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_FALSE(evaluator2.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, AndOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("[StringDoesNotExist1] & [StringDoesNotExist2]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_FALSE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("[I'm] & [StringDoesNotExist]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_FALSE(evaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator3("[StringDoesNotExist] & [moment]");
    EXPECT_FALSE(evaluator3.isInvalid());
    EXPECT_FALSE(evaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator4("[I'm] & [moment]");
    EXPECT_FALSE(evaluator4.isInvalid());
    EXPECT_TRUE(evaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, AndOperatorCombinationWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("[StringDoesNotExist1] && [StringDoesNotExist2]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_FALSE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("[I'm] &&& [StringDoesNotExist]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_FALSE(evaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator3("[StringDoesNotExist] &&&&&& [moment]");
    EXPECT_FALSE(evaluator3.isInvalid());
    EXPECT_FALSE(evaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator4("[I'm] &&&&&&&&&&&& [moment]");
    EXPECT_FALSE(evaluator4.isInvalid());
    EXPECT_TRUE(evaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, OrOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("[StringDoesNotExist1] | [StringDoesNotExist2]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_FALSE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("[I'm] | [StringDoesNotExist]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_TRUE(evaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator3("[StringDoesNotExist] | [moment]");
    EXPECT_FALSE(evaluator3.isInvalid());
    EXPECT_TRUE(evaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator4("[I'm] | [moment]");
    EXPECT_FALSE(evaluator4.isInvalid());
    EXPECT_TRUE(evaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, OrOperatorCombinationWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("[StringDoesNotExist1] || [StringDoesNotExist2]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_FALSE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("[I'm] ||| [StringDoesNotExist]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_TRUE(evaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator3("[StringDoesNotExist] |||||| [moment]");
    EXPECT_FALSE(evaluator3.isInvalid());
    EXPECT_TRUE(evaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator4("[I'm] |||||||| [moment]");
    EXPECT_FALSE(evaluator4.isInvalid());
    EXPECT_TRUE(evaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, XorOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("[StringDoesNotExist1] ^ [StringDoesNotExist2]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_FALSE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("[I'm] ^ [StringDoesNotExist]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_TRUE(evaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator3("[StringDoesNotExist] ^ [moment]");
    EXPECT_FALSE(evaluator3.isInvalid());
    EXPECT_TRUE(evaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator4("[I'm] ^ [moment]");
    EXPECT_FALSE(evaluator4.isInvalid());
    EXPECT_FALSE(evaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, XnorOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("[StringDoesNotExist1] !^ [StringDoesNotExist2]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_TRUE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("[I'm] !^ [StringDoesNotExist]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_FALSE(evaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator3("[StringDoesNotExist] !^ [moment]");
    EXPECT_FALSE(evaluator3.isInvalid());
    EXPECT_FALSE(evaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator4("[I'm] !^ [moment]");
    EXPECT_FALSE(evaluator4.isInvalid());
    EXPECT_TRUE(evaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, XnorOperatorCombinationWorksAsIntended)
{
    AlbaGrepStringEvaluator evaluator1("[StringDoesNotExist1] !^ [StringDoesNotExist2]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_TRUE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("[I'm] ^! [StringDoesNotExist]");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_FALSE(evaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator3("[StringDoesNotExist] ~^ [moment]");
    EXPECT_FALSE(evaluator3.isInvalid());
    EXPECT_FALSE(evaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator4("[I'm] ^~ [moment]");
    EXPECT_FALSE(evaluator4.isInvalid());
    EXPECT_TRUE(evaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, InvalidCombinationsAreDetected)
{
    AlbaGrepStringEvaluator evaluator1("[StringDoesNotExist1] ^^ [StringDoesNotExist2]");
    EXPECT_TRUE(evaluator1.isInvalid());

    AlbaGrepStringEvaluator evaluator2("[StringDoesNotExist1] &| [StringDoesNotExist2]");
    EXPECT_TRUE(evaluator2.isInvalid());

    AlbaGrepStringEvaluator evaluator3("[StringDoesNotExist1] ^& [StringDoesNotExist2]");
    EXPECT_TRUE(evaluator3.isInvalid());

    AlbaGrepStringEvaluator evaluator4("[StringDoesNotExist1] ||||||& [StringDoesNotExist2]");
    EXPECT_TRUE(evaluator4.isInvalid());

    AlbaGrepStringEvaluator evaluator5("[StringDoesNotExist1] !^^ [StringDoesNotExist2]");
    EXPECT_TRUE(evaluator5.isInvalid());

    AlbaGrepStringEvaluator evaluator6("[StringDoesNotExist1] ^!& [StringDoesNotExist2]");
    EXPECT_TRUE(evaluator6.isInvalid());

    AlbaGrepStringEvaluator evaluator7("[StringDoesNotExist1] !& [StringDoesNotExist2]");
    EXPECT_TRUE(evaluator7.isInvalid());
}

TEST(AlbaGrepStringEvaluatorTest, NotOperationIsPrioritized)
{
    AlbaGrepStringEvaluator evaluator1("![I'm]&![hungry]|![at]^!![this moment]");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_TRUE(evaluator1.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, ParenthesesArePrioritized)
{
    AlbaGrepStringEvaluator evaluator1("[I'm]&(![hungry]|[at])&(![this]^!![moment])");
    EXPECT_FALSE(evaluator1.isInvalid());
    EXPECT_TRUE(evaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator evaluator2("[I'm]&(![hungry]|([at]&(![this]^!![moment])))");
    EXPECT_FALSE(evaluator2.isInvalid());
    EXPECT_TRUE(evaluator2.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, EvaluatorIsInvalidWhenNumberOfOpeningAndClosingParenthesisDoesNotMatch)
{
    AlbaGrepStringEvaluator evaluator1("([I'm]&(![hungry]|([at]&(![this]^!![moment])))");
    EXPECT_TRUE(evaluator1.isInvalid());

    AlbaGrepStringEvaluator evaluator2("[I'm]&(![hungry])|([at]&(![this]^!![moment])))");
    EXPECT_TRUE(evaluator2.isInvalid());
}

/// parenthesis incomplete
