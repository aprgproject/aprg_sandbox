#include <BooleanAlgebra/Term/TermTypes/Term.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace booleanAlgebra
{

TEST(TermTest, TermsAsConstantsWorks)
{
    Term constantTerm1(false);
    Term constantTerm2(true);
    Term constantTerm3("tRue");
    Term constantTerm4("0");
    Term constantTerm5("5");

    ASSERT_EQ(TermType::Constant, constantTerm1.getTermType());
    EXPECT_FALSE(constantTerm1.getConstantConstReference().getBooleanValue());

    ASSERT_EQ(TermType::Constant, constantTerm2.getTermType());
    EXPECT_TRUE(constantTerm2.getConstantConstReference().getBooleanValue());

    ASSERT_EQ(TermType::Constant, constantTerm3.getTermType());
    EXPECT_TRUE(constantTerm3.getConstantConstReference().getBooleanValue());

    ASSERT_EQ(TermType::Constant, constantTerm4.getTermType());
    EXPECT_FALSE(constantTerm4.getConstantConstReference().getBooleanValue());

    ASSERT_EQ(TermType::Constant, constantTerm5.getTermType());
    EXPECT_TRUE(constantTerm5.getConstantConstReference().getBooleanValue());
}

TEST(TermTest, TermsAsVariableTermsWorks)
{
    Term variableTerm1("x");
    Term variableTerm2("power");

    ASSERT_EQ(TermType::VariableTerm, variableTerm1.getTermType());
    EXPECT_EQ("x", variableTerm1.getVariableTermConstReference().getVariableTermName());

    ASSERT_EQ(TermType::VariableTerm, variableTerm2.getTermType());
    EXPECT_EQ("power", variableTerm2.getVariableTermConstReference().getVariableTermName());
}

TEST(TermTest, TermsAsOperatorsWorks)
{
    Term operatorTerm1("~");
    Term operatorTerm2("&");
    Term operatorTerm3("|");

    ASSERT_EQ(TermType::Operator, operatorTerm1.getTermType());
    EXPECT_EQ("~", operatorTerm1.getOperatorConstReference().getOperatorString());

    ASSERT_EQ(TermType::Operator, operatorTerm2.getTermType());
    EXPECT_EQ("&", operatorTerm2.getOperatorConstReference().getOperatorString());

    ASSERT_EQ(TermType::Operator, operatorTerm3.getTermType());
    EXPECT_EQ("|", operatorTerm3.getOperatorConstReference().getOperatorString());
}

TEST(TermTest, TermsAsExpressionsWorks)
{
    Term expressionTerm1(Expression{});
    Term expressionTerm2(createExpressionIfPossible({true, "&", "x"}));

    //For expression1
    ASSERT_EQ(TermType::Expression, expressionTerm1.getTermType());
    Expression const& expression1(expressionTerm1.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify1(expression1.getWrappedTerms());
    ASSERT_TRUE(termsToVerify1.empty());

    //For expression2
    ASSERT_EQ(TermType::Expression, expressionTerm2.getTermType());
    Expression const& expression2(expressionTerm2.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expression2.getCommonOperatorLevel());
    WrappedTerms const& termsToVerify2(expression2.getWrappedTerms());
    ASSERT_EQ(1U, termsToVerify2.size());
    EXPECT_EQ(Term("x"), getTermConstReferenceFromUniquePointer(termsToVerify2.at(0).baseTermPointer));
}

TEST(TermTest, TermsAsConstructedAsStringWorks){
    Term term1("");
    Term term2("true");
    Term term3("&");    Term term4("power");
    Term term5("x1");

    ASSERT_EQ(TermType::Empty, term1.getTermType());

    ASSERT_EQ(TermType::Constant, term2.getTermType());
    EXPECT_TRUE(term2.getConstantConstReference().getBooleanValue());

    ASSERT_EQ(TermType::Operator, term3.getTermType());
    EXPECT_EQ("&", term3.getOperatorConstReference().getOperatorString());

    ASSERT_EQ(TermType::VariableTerm, term4.getTermType());
    EXPECT_EQ("power", term4.getVariableTermConstReference().getVariableTermName());

    ASSERT_EQ(TermType::VariableTerm, term5.getTermType());
    EXPECT_EQ("x1", term5.getVariableTermConstReference().getVariableTermName());
}

TEST(TermTest, TermThatIsDefaultConstructedHasIsSimplifiedFlagNotSet)
{
    Term term;

    EXPECT_FALSE(term.isSimplified());
}

TEST(TermTest, TermThatIsCopyConstructedHasIsSimplifiedFlagCopied)
{
    Term termWithSimplifiedNotSet;
    Term termWithSimplifiedSet;
    termWithSimplifiedSet.setAsSimplified();

    Term term1(termWithSimplifiedNotSet);
    Term term2(termWithSimplifiedSet);

    EXPECT_FALSE(term1.isSimplified());
    EXPECT_TRUE(term2.isSimplified());
}

TEST(TermTest, TermThatIsConstructedWithTermTypeHasIsSimplifiedFlagNotSet)
{
    Term constantTerm(true);
    Term variableTerm("");
    Term operatorTerm("&");
    Term expressionTerm(Expression{});

    EXPECT_FALSE(constantTerm.isSimplified());
    EXPECT_FALSE(variableTerm.isSimplified());
    EXPECT_FALSE(operatorTerm.isSimplified());
    EXPECT_FALSE(expressionTerm.isSimplified());
}

TEST(TermTest, GetBooleanValueWorks)
{
    Term constantTerm1(false);
    Term constantTerm2(true);

    ASSERT_EQ(TermType::Constant, constantTerm1.getTermType());
    EXPECT_FALSE(constantTerm1.getBooleanValue());

    ASSERT_EQ(TermType::Constant, constantTerm2.getTermType());
    EXPECT_TRUE(constantTerm2.getBooleanValue());
}

TEST(TermTest, TermsAsConstantsCanBeChanged)
{
    Term term(Constant{});

    term.getConstantReference().setValue(true);

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_TRUE(term.getBooleanValue());
}

TEST(TermTest, TermsAsVariableTermsCanBeChanged)
{
    Term term(VariableTerm{});

    term.getVariableTermReference().setVariableTermName("time");

    ASSERT_EQ(TermType::VariableTerm, term.getTermType());
    EXPECT_EQ("time", term.getVariableTermConstReference().getVariableTermName());
}

TEST(TermTest, TermsAsOperatorsCanBeChanged)
{
    Term term(Operator{});

    term.getOperatorReference().setOperatorString("&");

    ASSERT_EQ(TermType::Operator, term.getTermType());
    EXPECT_EQ("&", term.getOperatorConstReference().getOperatorString());
}

TEST(TermTest, TermsAsExpressionsCanBeChanged)
{
    Term term(Expression{});

    term.getExpressionReference().setCommonOperatorLevel(OperatorLevel::And);

    ASSERT_EQ(TermType::Expression, term.getTermType());
    EXPECT_EQ(OperatorLevel::And, term.getExpressionConstReference().getCommonOperatorLevel());
}

TEST(TermTest, AssignmentOperatorWorks)
{
    Term term1 = false;
    Term term2(true);
    term2 = false;
    Term term3(false);
    term3 = term3;

    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_FALSE(term1.getBooleanValue());
    ASSERT_EQ(TermType::Constant, term2.getTermType());
    EXPECT_FALSE(term1.getBooleanValue());
    ASSERT_EQ(TermType::Constant, term3.getTermType());
    EXPECT_FALSE(term1.getBooleanValue());
}

TEST(TermTest, TermThatIsAssignedHasIsSimplifiedFlagCopied)
{
    Term termWithSimplifiedNotSet;
    Term termWithSimplifiedSet;
    termWithSimplifiedSet.setAsSimplified();
    Term term1(true);
    Term term2(true);

    term1 = termWithSimplifiedNotSet;
    term2 = termWithSimplifiedSet;

    EXPECT_FALSE(term1.isSimplified());
    EXPECT_TRUE(term2.isSimplified());
}

TEST(TermTest, EqualityOperatorWorks)
{
    Term term1;
    Term term2(Constant(false));
    Term term3(Constant(true));
    Term term4(VariableTerm("x"));
    Term term5(Constant(false));

    EXPECT_TRUE(term1==term1);
    EXPECT_FALSE(term1==term2);
    EXPECT_TRUE(term2==term2);
    EXPECT_FALSE(term2==term3);
    EXPECT_FALSE(term2==term4);
    EXPECT_TRUE(term2==term5);
}

TEST(TermTest, InequalityOperatorWorks)
{
    Term term1;
    Term term2(Constant(false));
    Term term3(Constant(true));
    Term term4(VariableTerm("x"));
    Term term5(Constant(false));

    EXPECT_FALSE(term1!=term1);
    EXPECT_TRUE(term1!=term2);
    EXPECT_FALSE(term2!=term2);
    EXPECT_TRUE(term2!=term3);
    EXPECT_TRUE(term2!=term4);
    EXPECT_FALSE(term2!=term5);
}

TEST(TermTest, LessThanOperatorWorks)
{
    Term term1;
    Term term2(Constant(false));
    Term term3(Constant(false));
    Term term4(Constant(true));
    Term term5(Operator("&"));
    Term term6(VariableTerm("x"));

    EXPECT_FALSE(term1<term1);
    EXPECT_FALSE(term2<term2);
    EXPECT_FALSE(term2<term3);
    EXPECT_TRUE(term2<term4);
    EXPECT_FALSE(term2<term5);
    EXPECT_TRUE(term2<term6);
}

TEST(TermTest, IsEmptyWorks)
{
    Term term1;
    Term term2(false);
    Term term3(true);
    Term term4(VariableTerm("x"));
    Term term5(Operator("&"));
    Term term6(Expression{});

    EXPECT_TRUE(term1.isEmpty());
    EXPECT_FALSE(term2.isEmpty());
    EXPECT_FALSE(term3.isEmpty());
    EXPECT_FALSE(term4.isEmpty());
    EXPECT_FALSE(term5.isEmpty());
    EXPECT_TRUE(term6.isEmpty());
}

TEST(TermTest, IsConstantWorks)
{
    Term term1;
    Term term2(1);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(Expression{});

    EXPECT_FALSE(term1.isConstant());
    EXPECT_TRUE(term2.isConstant());
    EXPECT_FALSE(term3.isConstant());
    EXPECT_FALSE(term4.isConstant());
    EXPECT_FALSE(term5.isConstant());
}

TEST(TermTest, IsVariableTermWorks)
{
    Term term1;
    Term term2(1);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(Expression{});

    EXPECT_FALSE(term1.isVariableTerm());
    EXPECT_FALSE(term2.isVariableTerm());
    EXPECT_TRUE(term3.isVariableTerm());
    EXPECT_FALSE(term4.isVariableTerm());
    EXPECT_FALSE(term5.isVariableTerm());
}

TEST(TermTest, IsOperatorWorks)
{
    Term term1;
    Term term2(1);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(Expression{});

    EXPECT_FALSE(term1.isOperator());
    EXPECT_FALSE(term2.isOperator());
    EXPECT_FALSE(term3.isOperator());
    EXPECT_TRUE(term4.isOperator());
    EXPECT_FALSE(term5.isOperator());
}

TEST(TermTest, IsExpressionWorks)
{
    Term term1;
    Term term2(1);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(Expression{});

    EXPECT_FALSE(term1.isExpression());
    EXPECT_FALSE(term2.isExpression());
    EXPECT_FALSE(term3.isExpression());
    EXPECT_FALSE(term4.isExpression());
    EXPECT_TRUE(term5.isExpression());
}

TEST(TermTest, IsSimplifiedWorks)
{
    Term term1;
    Term term2;
    term2.setAsSimplified();

    EXPECT_FALSE(term1.isSimplified());
    EXPECT_TRUE(term2.isSimplified());
}

TEST(TermTest, GetTermTypeWorks)
{
    Term term1;
    Term term2(false);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(Expression{});

    EXPECT_EQ(TermType::Empty, term1.getTermType());
    EXPECT_EQ(TermType::Constant, term2.getTermType());
    EXPECT_EQ(TermType::VariableTerm, term3.getTermType());
    EXPECT_EQ(TermType::Operator, term4.getTermType());
    EXPECT_EQ(TermType::Expression, term5.getTermType());
}

TEST(TermTest, GetDebugStringWorks)
{
    Term term1;
    Term term2(false);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(createExpressionIfPossible({true, "&", "x"}));

    EXPECT_EQ("{EmptyTerm}{Empty}", term1.getDebugString());
    EXPECT_EQ("[false]{Constant}", term2.getDebugString());
    EXPECT_EQ("x{VariableTerm}", term3.getDebugString());
    EXPECT_EQ("&{Operator}", term4.getDebugString());
    EXPECT_EQ("( {?}||x{VariableTerm} ){Expression}", term5.getDebugString());
}

TEST(TermTest, ClearWorks)
{
    Term constantTerm(true);
    Term variableTerm("x");
    Term expressionTerm(Expression{createExpressionIfPossible({true})});

    constantTerm.clear();
    variableTerm.clear();
    expressionTerm.clear();

    EXPECT_EQ(Term(), constantTerm);
    EXPECT_EQ(Term(), variableTerm);
    EXPECT_EQ(Term(), expressionTerm);
}

TEST(TermTest, SimplifyWorks)
{
    Term constantTerm(true);
    Term variableTerm("x");
    Term expressionTerm(createExpressionIfPossible({true, "&", false}));

    constantTerm.simplify();
    variableTerm.simplify();
    expressionTerm.simplify();

    EXPECT_EQ(Term(true), constantTerm);
    EXPECT_EQ(Term("x"), variableTerm);
    EXPECT_EQ(Term(false), expressionTerm);
}

TEST(TermTest, SimplifyWorksWhenIsSimplifiedIsNotSet)
{
    Term term(createExpressionIfPossible({true, "&", false}));

    term.simplify();

    EXPECT_EQ(Term(false), term);
}

TEST(TermTest, SimplifyWorksAsSkippedWhenIsSimplifiedIsSet)
{
    Term term(createExpressionIfPossible({true, "&", false}));
    term.setAsSimplified();

    term.simplify();

    Term expectedTerm(createExpressionIfPossible({true, "&", false}));
    EXPECT_EQ(expectedTerm, term);
}

TEST(TermTest, SortWorks)
{
    Term term1;
    Term term2(Expression{});
    Term term3(createExpressionIfPossible({"d", "&", "c", "&", "b", "&", "a"}));

    term1.sort();
    term2.sort();
    term3.sort();

    Term expectTerm1;
    Term expectTerm2(Expression{});
    Term expectTerm3(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d"}));
    EXPECT_EQ(expectTerm1, term1);
    EXPECT_EQ(expectTerm2, term2);
    EXPECT_EQ(expectTerm3, term3);
}

TEST(TermTest, NegateWorks)
{
    Term term1;
    Term term2(Expression{});
    Term term3(createExpressionIfPossible(
    {"x", "&", "x'", "&", "y", "&", "z"}));

    term1.negate();
    term2.negate();
    term3.negate();

    Term expectTerm1;
    Term expectTerm2(Expression{});
    Term expectTerm3(createExpressionIfPossible(
    {"x'", "|", "x", "|", "y'", "|", "z'"}));
    EXPECT_EQ(expectTerm1, term1);
    EXPECT_EQ(expectTerm2, term2);
    EXPECT_EQ(expectTerm3, term3);
}

TEST(TermTest, SetAsSimplifiedWorks)
{
    Term term;

    term.setAsSimplified();

    EXPECT_TRUE(term.isSimplified());
}

TEST(TermTest, ClearSimplifiedFlagWorks)
{
    Term term;
    term.setAsSimplified();

    term.clearSimplifiedFlag();

    EXPECT_FALSE(term.isSimplified());
}

TEST(TermTest, ClearAllInnerSimplifiedFlagsWorks)
{
    Expression innerExpression(createExpressionIfPossible({"x", "&", "y", "|", "z"}));
    Term term(innerExpression);
    term.setAsSimplified();
    EXPECT_TRUE(term.isSimplified());
    EXPECT_FALSE(term.getExpressionConstReference().isSimplified());

    term.clearAllInnerSimplifiedFlags();

    EXPECT_FALSE(term.isSimplified());
    EXPECT_FALSE(term.getExpressionConstReference().isSimplified());
}

TEST(TermTest, OutputStreamOperatorWorks)
{
    stringstream ss;
    Term term1;
    Term term2(false);
    Term term3(VariableTerm("x"));
    Term term4(Operator("&"));
    Term term5(createExpressionIfPossible({true, "&", "x"}));

    ss << term1 << "," << term2 << "," << term3 << "," << term4 << "," << term5;

    EXPECT_EQ("{EmptyTerm},[false],x,&,(x)", ss.str());
}

}

}
