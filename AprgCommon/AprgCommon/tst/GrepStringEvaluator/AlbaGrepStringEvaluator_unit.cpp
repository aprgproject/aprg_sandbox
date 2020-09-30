#include "../src/GrepStringEvaluator/AlbaGrepStringEvaluator.hpp"

#include "gtest/gtest.h"
#include <string>

using namespace alba;

TEST(AlbaGrepStringEvaluatorTest, FalseIsReturnedWhenconditionIsEmpty)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator("");
    EXPECT_TRUE(AlbaGrepStringEvaluator.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator.evaluate("TestString"));
}

TEST(AlbaGrepStringEvaluatorTest, FalseIsReturnedWhenThereAreNoConvertedTerms)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator("TestString");
    EXPECT_TRUE(AlbaGrepStringEvaluator.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator.evaluate("TestString"));
}

TEST(AlbaGrepStringEvaluatorTest, FalseIsReturnedWhenEvaluateStringIsEmpty)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator("[TestString123]");
    EXPECT_FALSE(AlbaGrepStringEvaluator.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator.evaluate(""));
}

TEST(AlbaGrepStringEvaluatorTest, TrueIsReturnedWhenStringIsFound)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator("[TestString123]");
    EXPECT_FALSE(AlbaGrepStringEvaluator.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator.evaluate("TestString123"));
}

TEST(AlbaGrepStringEvaluatorTest, TrueIsReturnedWhenStringIsFoundWithDifferentCase)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator("[tESTsTRING123]");
    EXPECT_FALSE(AlbaGrepStringEvaluator.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator.evaluate("TestString123"));
}

TEST(AlbaGrepStringEvaluatorTest, NotOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("![StringDoesNotExist1]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("![hungry]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, NotOperatorCombinationWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("!!!![StringDoesNotExist1]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("!~!~!~~[hungry]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, AndOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[StringDoesNotExist1] & [StringDoesNotExist2]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm] & [StringDoesNotExist]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator3("[StringDoesNotExist] & [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator3.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator4("[I'm] & [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator4.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, AndOperatorCombinationWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[StringDoesNotExist1] && [StringDoesNotExist2]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm] &&& [StringDoesNotExist]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator3("[StringDoesNotExist] &&&&&& [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator3.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator4("[I'm] &&&&&&&&&&&& [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator4.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, OrOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[StringDoesNotExist1] | [StringDoesNotExist2]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm] | [StringDoesNotExist]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator3("[StringDoesNotExist] | [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator3.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator4("[I'm] | [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator4.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, OrOperatorCombinationWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[StringDoesNotExist1] || [StringDoesNotExist2]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm] ||| [StringDoesNotExist]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator3("[StringDoesNotExist] |||||| [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator3.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator4("[I'm] |||||||| [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator4.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, XorOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[StringDoesNotExist1] ^ [StringDoesNotExist2]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm] ^ [StringDoesNotExist]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator3("[StringDoesNotExist] ^ [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator3.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator4("[I'm] ^ [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator4.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, XnorOperatorWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[StringDoesNotExist1] !^ [StringDoesNotExist2]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm] !^ [StringDoesNotExist]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator3("[StringDoesNotExist] !^ [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator3.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator4("[I'm] !^ [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator4.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, XnorOperatorCombinationWorksAsIntended)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[StringDoesNotExist1] !^ [StringDoesNotExist2]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm] ^! [StringDoesNotExist]");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator3("[StringDoesNotExist] ~^ [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator3.isInvalid());
    EXPECT_FALSE(AlbaGrepStringEvaluator3.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator4("[I'm] ^~ [moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator4.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator4.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, InvalidCombinationsAreDetected)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[StringDoesNotExist1] ^^ [StringDoesNotExist2]");
    EXPECT_TRUE(AlbaGrepStringEvaluator1.isInvalid());

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[StringDoesNotExist1] &| [StringDoesNotExist2]");
    EXPECT_TRUE(AlbaGrepStringEvaluator2.isInvalid());

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator3("[StringDoesNotExist1] ^& [StringDoesNotExist2]");
    EXPECT_TRUE(AlbaGrepStringEvaluator3.isInvalid());

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator4("[StringDoesNotExist1] ||||||& [StringDoesNotExist2]");
    EXPECT_TRUE(AlbaGrepStringEvaluator4.isInvalid());

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator5("[StringDoesNotExist1] !^^ [StringDoesNotExist2]");
    EXPECT_TRUE(AlbaGrepStringEvaluator5.isInvalid());

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator6("[StringDoesNotExist1] ^!& [StringDoesNotExist2]");
    EXPECT_TRUE(AlbaGrepStringEvaluator6.isInvalid());

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator7("[StringDoesNotExist1] !& [StringDoesNotExist2]");
    EXPECT_TRUE(AlbaGrepStringEvaluator7.isInvalid());
}

TEST(AlbaGrepStringEvaluatorTest, NotOperationIsPrioritized)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("![I'm]&![hungry]|![at]^!![this moment]");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, ParenthesesArePrioritized)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("[I'm]&(![hungry]|[at])&(![this]^!![moment])");
    EXPECT_FALSE(AlbaGrepStringEvaluator1.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator1.evaluate("I'm hungry at this moment."));

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm]&(![hungry]|([at]&(![this]^!![moment])))");
    EXPECT_FALSE(AlbaGrepStringEvaluator2.isInvalid());
    EXPECT_TRUE(AlbaGrepStringEvaluator2.evaluate("I'm hungry at this moment."));
}

TEST(AlbaGrepStringEvaluatorTest, EvaluatorIsInvalidWhenNumberOfOpeningAndClosingParenthesisDoesNotMatch)
{
    AlbaGrepStringEvaluator AlbaGrepStringEvaluator1("([I'm]&(![hungry]|([at]&(![this]^!![moment])))");
    EXPECT_TRUE(AlbaGrepStringEvaluator1.isInvalid());

    AlbaGrepStringEvaluator AlbaGrepStringEvaluator2("[I'm]&(![hungry])|([at]&(![this]^!![moment])))");
    EXPECT_TRUE(AlbaGrepStringEvaluator2.isInvalid());
}

/// parenthesis incomplete

