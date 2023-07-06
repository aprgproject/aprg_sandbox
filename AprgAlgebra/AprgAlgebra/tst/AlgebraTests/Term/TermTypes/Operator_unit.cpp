#include <Algebra/Term/TermTypes/Operator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

TEST(OperatorTest, OperatorsAreConstructedCorrectly) {
    Operator operator1;
    Operator operator2("test");

    EXPECT_EQ("", operator1.getOperatorString());
    EXPECT_EQ("test", operator2.getOperatorString());
}

TEST(OperatorTest, EqualityOperatorWorks) {
    Operator operator1;
    Operator operator2("+");
    Operator operator3("-");
    Operator operator4("+");

    EXPECT_TRUE(operator1 == operator1);
    EXPECT_FALSE(operator1 == operator2);
    EXPECT_TRUE(operator2 == operator2);
    EXPECT_FALSE(operator2 == operator3);
    EXPECT_TRUE(operator2 == operator4);
}

TEST(OperatorTest, InequalityOperatorWorks) {
    Operator operator1;
    Operator operator2("+");
    Operator operator3("-");
    Operator operator4("+");

    EXPECT_FALSE(operator1 != operator1);
    EXPECT_TRUE(operator1 != operator2);
    EXPECT_FALSE(operator2 != operator2);
    EXPECT_TRUE(operator2 != operator3);
    EXPECT_FALSE(operator2 != operator4);
}

TEST(OperatorTest, LessThanOperatorWorks) {
    EXPECT_FALSE(Operator() < Operator());
    EXPECT_FALSE(Operator("*") < Operator("*"));
    EXPECT_FALSE(Operator("*") < Operator("+"));
    EXPECT_TRUE(Operator("*") < Operator("/"));
}

TEST(OperatorTest, IsAdditionWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isAddition());
    EXPECT_TRUE(addOperator.isAddition());
    EXPECT_FALSE(subtractOperator.isAddition());
    EXPECT_FALSE(multiplyOperator.isAddition());
    EXPECT_FALSE(divideOperator.isAddition());
    EXPECT_FALSE(raiseToPowerOperator.isAddition());
    EXPECT_FALSE(openingGroupOperator.isAddition());
    EXPECT_FALSE(closingGroupOperator.isAddition());
    EXPECT_FALSE(invalidOperator.isAddition());
}

TEST(OperatorTest, IsSubtractionWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isSubtraction());
    EXPECT_FALSE(addOperator.isSubtraction());
    EXPECT_TRUE(subtractOperator.isSubtraction());
    EXPECT_FALSE(multiplyOperator.isSubtraction());
    EXPECT_FALSE(divideOperator.isSubtraction());
    EXPECT_FALSE(raiseToPowerOperator.isSubtraction());
    EXPECT_FALSE(openingGroupOperator.isSubtraction());
    EXPECT_FALSE(closingGroupOperator.isSubtraction());
    EXPECT_FALSE(invalidOperator.isSubtraction());
}

TEST(OperatorTest, IsMultiplicationWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isMultiplication());
    EXPECT_FALSE(addOperator.isMultiplication());
    EXPECT_FALSE(subtractOperator.isMultiplication());
    EXPECT_TRUE(multiplyOperator.isMultiplication());
    EXPECT_FALSE(divideOperator.isMultiplication());
    EXPECT_FALSE(raiseToPowerOperator.isMultiplication());
    EXPECT_FALSE(openingGroupOperator.isMultiplication());
    EXPECT_FALSE(closingGroupOperator.isMultiplication());
    EXPECT_FALSE(invalidOperator.isMultiplication());
}

TEST(OperatorTest, IsDivisionWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isDivision());
    EXPECT_FALSE(addOperator.isDivision());
    EXPECT_FALSE(subtractOperator.isDivision());
    EXPECT_FALSE(multiplyOperator.isDivision());
    EXPECT_TRUE(divideOperator.isDivision());
    EXPECT_FALSE(raiseToPowerOperator.isDivision());
    EXPECT_FALSE(openingGroupOperator.isDivision());
    EXPECT_FALSE(closingGroupOperator.isDivision());
    EXPECT_FALSE(invalidOperator.isDivision());
}

TEST(OperatorTest, IsRaiseToPowerWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isRaiseToPower());
    EXPECT_FALSE(addOperator.isRaiseToPower());
    EXPECT_FALSE(subtractOperator.isRaiseToPower());
    EXPECT_FALSE(multiplyOperator.isRaiseToPower());
    EXPECT_FALSE(divideOperator.isRaiseToPower());
    EXPECT_TRUE(raiseToPowerOperator.isRaiseToPower());
    EXPECT_FALSE(openingGroupOperator.isRaiseToPower());
    EXPECT_FALSE(closingGroupOperator.isRaiseToPower());
    EXPECT_FALSE(invalidOperator.isRaiseToPower());
}

TEST(OperatorTest, IsAnOperatorThatCanPerformedWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isAnOperatorThatCanPerformed());
    EXPECT_TRUE(addOperator.isAnOperatorThatCanPerformed());
    EXPECT_TRUE(subtractOperator.isAnOperatorThatCanPerformed());
    EXPECT_TRUE(multiplyOperator.isAnOperatorThatCanPerformed());
    EXPECT_TRUE(divideOperator.isAnOperatorThatCanPerformed());
    EXPECT_TRUE(raiseToPowerOperator.isAnOperatorThatCanPerformed());
    EXPECT_FALSE(openingGroupOperator.isAnOperatorThatCanPerformed());
    EXPECT_FALSE(closingGroupOperator.isAnOperatorThatCanPerformed());
    EXPECT_FALSE(invalidOperator.isAnOperatorThatCanPerformed());
}

TEST(OperatorTest, IsOpeningGroupOperatorWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isOpeningGroupOperator());
    EXPECT_FALSE(addOperator.isOpeningGroupOperator());
    EXPECT_FALSE(subtractOperator.isOpeningGroupOperator());
    EXPECT_FALSE(multiplyOperator.isOpeningGroupOperator());
    EXPECT_FALSE(divideOperator.isOpeningGroupOperator());
    EXPECT_FALSE(raiseToPowerOperator.isOpeningGroupOperator());
    EXPECT_TRUE(openingGroupOperator.isOpeningGroupOperator());
    EXPECT_FALSE(closingGroupOperator.isOpeningGroupOperator());
    EXPECT_FALSE(invalidOperator.isOpeningGroupOperator());
}

TEST(OperatorTest, IsClosingGroupOperatorWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_FALSE(nullOperator.isClosingGroupOperator());
    EXPECT_FALSE(addOperator.isClosingGroupOperator());
    EXPECT_FALSE(subtractOperator.isClosingGroupOperator());
    EXPECT_FALSE(multiplyOperator.isClosingGroupOperator());
    EXPECT_FALSE(divideOperator.isClosingGroupOperator());
    EXPECT_FALSE(raiseToPowerOperator.isClosingGroupOperator());
    EXPECT_FALSE(openingGroupOperator.isClosingGroupOperator());
    EXPECT_TRUE(closingGroupOperator.isClosingGroupOperator());
    EXPECT_FALSE(invalidOperator.isClosingGroupOperator());
}

TEST(OperatorTest, GetOperatorLevelWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_EQ(OperatorLevel::Unknown, nullOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, addOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, subtractOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, multiplyOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, divideOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::RaiseToPower, raiseToPowerOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::Unknown, openingGroupOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::Unknown, closingGroupOperator.getOperatorLevel());
    EXPECT_EQ(OperatorLevel::Unknown, invalidOperator.getOperatorLevel());
}

TEST(OperatorTest, GetOperatorStringValueWorks) {
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    EXPECT_TRUE(nullOperator.getOperatorString().empty());
    EXPECT_EQ("+", addOperator.getOperatorString());
    EXPECT_EQ("-", subtractOperator.getOperatorString());
    EXPECT_EQ("*", multiplyOperator.getOperatorString());
    EXPECT_EQ("/", divideOperator.getOperatorString());
    EXPECT_EQ("^", raiseToPowerOperator.getOperatorString());
    EXPECT_EQ("(", openingGroupOperator.getOperatorString());
    EXPECT_EQ(")", closingGroupOperator.getOperatorString());
    EXPECT_EQ("invalid", invalidOperator.getOperatorString());
}

TEST(OperatorTest, SettingANewOperatingStringWorks) {
    Operator operatorForTest1;
    Operator operatorForTest2;

    operatorForTest2.setOperatorString("multiply");

    EXPECT_EQ("", operatorForTest1.getOperatorString());
    EXPECT_EQ("multiply", operatorForTest2.getOperatorString());
}

TEST(OperatorTest, OutputStreamOperatorWorks) {
    stringstream ss;
    Operator nullOperator;
    Operator addOperator("+");
    Operator subtractOperator("-");
    Operator multiplyOperator("*");
    Operator divideOperator("/");
    Operator raiseToPowerOperator("^");
    Operator openingGroupOperator("(");
    Operator closingGroupOperator(")");
    Operator invalidOperator("invalid");

    ss << nullOperator << "," << addOperator << "," << subtractOperator << "," << multiplyOperator << ","
       << divideOperator << "," << raiseToPowerOperator << "," << openingGroupOperator << "," << closingGroupOperator
       << "," << invalidOperator;

    EXPECT_EQ(",+,-,*,/,^,(,),invalid", ss.str());
}

}  // namespace algebra

}  // namespace alba
