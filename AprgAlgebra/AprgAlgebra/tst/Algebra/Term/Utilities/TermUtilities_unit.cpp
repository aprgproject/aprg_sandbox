#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <string/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

TEST(TermUtilitiesTest, IsOperatorWorks)
{
    EXPECT_FALSE(isOperator(""));
    EXPECT_TRUE(isOperator("+"));
    EXPECT_TRUE(isOperator("-"));
    EXPECT_TRUE(isOperator("*"));
    EXPECT_TRUE(isOperator("/"));
    EXPECT_TRUE(isOperator("^"));
    EXPECT_TRUE(isOperator("("));
    EXPECT_TRUE(isOperator(")"));
    EXPECT_FALSE(isOperator("notAnOperator"));
}

TEST(TermUtilitiesTest, IsFunctionWorks)
{
    EXPECT_FALSE(isFunction(""));
    EXPECT_TRUE(isFunction("abs"));
    EXPECT_FALSE(isFunction("notAnFunction"));
}

TEST(TermUtilitiesTest, CanBeMergedByAdditionOrSubtractionForTermsWorks)
{
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(73), Term(84)));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Variable("x")), Term(Variable("x"))));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Variable("x"))));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Variable("x")), Term(Monomial(96, {{"x", 1}}))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Variable("x")), Term(Variable("y"))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}})), Term(Monomial(96, {{"x", 5}}))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Monomial(96, {{"a", 1}})), Term(Variable("x"))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Variable("x")), Term(Monomial(96, {{"a", 1}}))));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Term(Expression()), Term(Expression())));
}

TEST(TermUtilitiesTest, CanBeMergedByAdditionOrSubtractionForBothMonomialsWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(100, {{"x", 6}, {"y", -1.25}});
    Monomial monomial4(100, {{"x", 5}, {"y", -1}});
    Monomial monomial5(645, {{"i", 20}, {"y", 30}});

    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial1, monomial1));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, monomial2));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial3, monomial3));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial4, monomial4));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial5, monomial5));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial1, monomial2));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, monomial3));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, monomial4));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, monomial5));
}

TEST(TermUtilitiesTest, CanBeMergedByAdditionOrSubtractionForMonomialAndVariableWorks)
{
    Monomial monomial1;
    Monomial monomial2(12, {{"x", 1}});
    Monomial monomial3(34, {{"x", 1.25}});
    Monomial monomial4(56, {{"x", 1}, {"y", 1}});
    Variable variable("x");

    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial1, variable));
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial2, variable));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial3, variable));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(monomial4, variable));
}

TEST(TermUtilitiesTest, CanBeMergedByAdditionOrSubtractionForBothVariablesWorks)
{
    EXPECT_TRUE(canBeMergedInAMonomialByAdditionOrSubtraction(Variable("x"), Variable("x")));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Variable("x"), Variable("w")));
    EXPECT_FALSE(canBeMergedInAMonomialByAdditionOrSubtraction(Variable("w"), Variable("x")));
}

TEST(TermUtilitiesTest, WillHaveNoEffectOnAdditionOrSubtractionWorks)
{
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term()));
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term(Constant(0))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(15)));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Variable("x"))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(createExpressionIfPossible({Term(254)}))));
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term(Expression())));
}

TEST(TermUtilitiesTest, WillHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPowerWorks)
{
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term()));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Constant(0))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(15)));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(1)));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Variable("x"))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Monomial(1, {}))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(createExpressionIfPossible({Term(254)}))));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Expression())));
}

TEST(TermUtilitiesTest, IsNotANumberWorksForTerm)
{
    EXPECT_TRUE(isNotANumber(Term(NAN)));
    EXPECT_TRUE(isNotANumber(Term(createExpressionIfPossible({Term(NAN)}))));
    EXPECT_FALSE(isNotANumber(Term(15)));
    EXPECT_FALSE(isNotANumber(Term("x")));
}

TEST(TermUtilitiesTest, IsNotANumberWorksForExpression)
{
    EXPECT_TRUE(isNotANumber(createExpressionIfPossible({Term(NAN)})));
    EXPECT_FALSE(isNotANumber(createExpressionIfPossible({Term(67)})));
}

TEST(TermUtilitiesTest, GetOperatorLevelValueWorks)
{
    EXPECT_EQ(1u, getOperatorPriority("("));
    EXPECT_EQ(2u, getOperatorPriority(")"));
    EXPECT_EQ(3u, getOperatorPriority("+"));
    EXPECT_EQ(4u, getOperatorPriority("-"));
    EXPECT_EQ(5u, getOperatorPriority("*"));
    EXPECT_EQ(6u, getOperatorPriority("/"));
    EXPECT_EQ(7u, getOperatorPriority("^"));
    EXPECT_EQ(0u, getOperatorPriority("operator"));
}

TEST(TermUtilitiesTest, GetAssociationPriorityWorks)
{
    EXPECT_EQ(1u, getAssociationPriority(TermAssociationType::Positive));
    EXPECT_EQ(2u, getAssociationPriority(TermAssociationType::Negative));
}

TEST(TermUtilitiesTest, GetOperatorLevelInversePriorityWorks)
{
    EXPECT_EQ(0u, getOperatorLevelInversePriority(OperatorLevel::Unknown));
    EXPECT_EQ(3u, getOperatorLevelInversePriority(OperatorLevel::AdditionAndSubtraction));
    EXPECT_EQ(2u, getOperatorLevelInversePriority(OperatorLevel::MultiplicationAndDivision));
    EXPECT_EQ(1u, getOperatorLevelInversePriority(OperatorLevel::RaiseToPower));
}

TEST(TermUtilitiesTest, GetTermPriorityValueWorks)
{
    EXPECT_EQ(0u, getTermTypePriorityValue(TermType::Empty));
    EXPECT_EQ(1u, getTermTypePriorityValue(TermType::Operator));
    EXPECT_EQ(2u, getTermTypePriorityValue(TermType::Constant));
    EXPECT_EQ(3u, getTermTypePriorityValue(TermType::Variable));
    EXPECT_EQ(4u, getTermTypePriorityValue(TermType::Monomial));
    EXPECT_EQ(5u, getTermTypePriorityValue(TermType::Polynomial));
    EXPECT_EQ(6u, getTermTypePriorityValue(TermType::Expression));
}

TEST(TermUtilitiesTest, GetRootsWorksAndRootsIsEmptyWhenConstantIsGiven)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(-16, {})}));

    EXPECT_TRUE(roots.empty());
}

TEST(TermUtilitiesTest, GetRootsWorksAndRootsIsEmptyWhenMultipleVariablesAreGiven)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"y", 3}}), Monomial(-16, {})}));

    EXPECT_TRUE(roots.empty());
}

TEST(TermUtilitiesTest, GetRootsWorksAndFactorizesAPolynomial)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-16, {})}));

    ASSERT_EQ(2u, roots.size());
    EXPECT_EQ(AlbaNumber(-4), roots.at(0));
    EXPECT_EQ(AlbaNumber(4), roots.at(1));
}

TEST(TermUtilitiesTest, GetRootsWorksAndRootIsZeroWhenExponentIsPositive)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", AlbaNumber(4)/3}})}));

    ASSERT_EQ(1u, roots.size());
    EXPECT_EQ(AlbaNumber(0), roots.at(0));
}

TEST(TermUtilitiesTest, GetRootsWorksAndZeroIsNotIncludedWhenExponentIsNegative)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", AlbaNumber(-4)/3}})}));

    EXPECT_TRUE(roots.empty());
}

TEST(TermUtilitiesTest, GetRootsWorksAndWhenPolynomialIsNotSorted)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(-16, {}), Monomial(1, {{"x", 1}})}));

    ASSERT_EQ(1u, roots.size());
    EXPECT_EQ(AlbaNumber(16), roots.at(0));
}

TEST(TermUtilitiesTest, GetRootsWorksAndRootIsCorrectlyCalculatedWhenExponentIsNotAnInteger)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", AlbaNumber(4)/3}}), Monomial(-16, {})}));

    ASSERT_EQ(1u, roots.size());
    EXPECT_EQ(AlbaNumber(8), roots.at(0));
}

TEST(TermUtilitiesTest, GetEnumShortStringForTermTypeWorks)
{
    EXPECT_EQ("Empty", getEnumShortString(TermType::Empty));
    EXPECT_EQ("Constant", getEnumShortString(TermType::Constant));
    EXPECT_EQ("Variable", getEnumShortString(TermType::Variable));
    EXPECT_EQ("Operator", getEnumShortString(TermType::Operator));
    EXPECT_EQ("Monomial", getEnumShortString(TermType::Monomial));
    EXPECT_EQ("Polynomial", getEnumShortString(TermType::Polynomial));
    EXPECT_EQ("Expression", getEnumShortString(TermType::Expression));
    EXPECT_EQ("Function", getEnumShortString(TermType::Function));
}

TEST(TermUtilitiesTest, GetEnumShortStringForTermAssociationTypeWorks)
{
    EXPECT_EQ("{POS}", getEnumShortString(TermAssociationType::Positive));
    EXPECT_EQ("{NEG}", getEnumShortString(TermAssociationType::Negative));
}

TEST(TermUtilitiesTest, GetEnumShortStringForOperatorLevelWorks)
{
    EXPECT_EQ("{?}", getEnumShortString(OperatorLevel::Unknown));
    EXPECT_EQ("{+-}", getEnumShortString(OperatorLevel::AdditionAndSubtraction));
    EXPECT_EQ("{*/}", getEnumShortString(OperatorLevel::MultiplicationAndDivision));
    EXPECT_EQ("{^}", getEnumShortString(OperatorLevel::RaiseToPower));
}

TEST(TermUtilitiesTest, GetOperatingStringWorks)
{
    EXPECT_TRUE(getOperatingString(OperatorLevel::Unknown, TermAssociationType::Positive).empty());
    EXPECT_TRUE(getOperatingString(OperatorLevel::Unknown, TermAssociationType::Negative).empty());
    EXPECT_EQ("+", getOperatingString(OperatorLevel::AdditionAndSubtraction, TermAssociationType::Positive));
    EXPECT_EQ("-", getOperatingString(OperatorLevel::AdditionAndSubtraction, TermAssociationType::Negative));
    EXPECT_EQ("*", getOperatingString(OperatorLevel::MultiplicationAndDivision, TermAssociationType::Positive));
    EXPECT_EQ("/", getOperatingString(OperatorLevel::MultiplicationAndDivision, TermAssociationType::Negative));
    EXPECT_EQ("^", getOperatingString(OperatorLevel::RaiseToPower, TermAssociationType::Positive));
    EXPECT_TRUE(getOperatingString(OperatorLevel::RaiseToPower, TermAssociationType::Negative).empty());
}

TEST(TermUtilitiesTest, GetFirstStringIfNegativeAssociationWorks)
{
    EXPECT_TRUE(getFirstStringIfNegativeAssociation(OperatorLevel::Unknown, TermAssociationType::Positive).empty());
    EXPECT_TRUE(getFirstStringIfNegativeAssociation(OperatorLevel::Unknown, TermAssociationType::Negative).empty());
    EXPECT_TRUE(getFirstStringIfNegativeAssociation(OperatorLevel::AdditionAndSubtraction, TermAssociationType::Positive).empty());
    EXPECT_EQ("-", getFirstStringIfNegativeAssociation(OperatorLevel::AdditionAndSubtraction, TermAssociationType::Negative));
    EXPECT_TRUE(getFirstStringIfNegativeAssociation(OperatorLevel::MultiplicationAndDivision, TermAssociationType::Positive).empty());
    EXPECT_EQ("1/", getFirstStringIfNegativeAssociation(OperatorLevel::MultiplicationAndDivision, TermAssociationType::Negative));
    EXPECT_TRUE(getFirstStringIfNegativeAssociation(OperatorLevel::RaiseToPower, TermAssociationType::Positive).empty());
    EXPECT_TRUE(getFirstStringIfNegativeAssociation(OperatorLevel::RaiseToPower, TermAssociationType::Negative).empty());
}

TEST(TermUtilitiesTest, GetStringForTermWithDetailsWorks)
{
    TermWithDetails termWithDetails(Term(10), TermAssociationType::Negative);

    EXPECT_EQ("{10}{{NEG}}", getString(termWithDetails));
}

TEST(TermUtilitiesTest, GetStringForTermsWithDetailsWorks)
{
    TermsWithDetails termsWithDetails;
    termsWithDetails.emplace_back(Term(10), TermAssociationType::Negative);
    termsWithDetails.emplace_back(Term(20), TermAssociationType::Positive);

    EXPECT_EQ("{10}{{NEG}}, {20}{{POS}}", getString(termsWithDetails));
}

TEST(TermUtilitiesTest, CreateVariableNameForSubstitutionWorks)
{
    Polynomial polynomial{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    EXPECT_EQ("{(6 + -7[x^2][y^3][z^4])}", createVariableNameForSubstitution(polynomial));
}

TEST(TermUtilitiesTest, GetNumbersForTermWorks)
{
    AlbaNumbersSet numbersSet(getNumbers(Term(Constant(1.234))));

    ASSERT_EQ(1u, numbersSet.size());
    EXPECT_EQ(AlbaNumber(1.234), *(numbersSet.cbegin()));
}

TEST(TermUtilitiesTest, RetrieveNumbersForTermWorks)
{
    AlbaNumbersSet numbersSet1;
    AlbaNumbersSet numbersSet2;
    AlbaNumbersSet numbersSet3;
    AlbaNumbersSet numbersSet4;
    AlbaNumbersSet numbersSet5;
    Function functionTerm(
                "functionName",
                createExpressionIfPossible({Term("x"), Term("^"), Term(68)}),
                [](Constant const&  constant) -> Constant
    {
        return constant;
    });

    retrieveNumbers(Term(Constant(1.234)), numbersSet1);
    retrieveNumbers(Term(Monomial(34, {{"x", 1}, {"y", 1}})), numbersSet2);
    retrieveNumbers(Term(Polynomial({Monomial(1, {{"x", 56}}), Monomial(1, {{"y", 1}})})), numbersSet3);
    retrieveNumbers(Term(createExpressionIfPossible({Term("x"), Term("^"), Term(68)})), numbersSet4);
    retrieveNumbers(Term(functionTerm), numbersSet5);

    ASSERT_EQ(1u, numbersSet1.size());
    EXPECT_EQ(AlbaNumber(1.234), *(numbersSet1.cbegin()));
    ASSERT_EQ(2u, numbersSet2.size());
    AlbaNumbersSet::const_iterator it2 = numbersSet2.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it2++));
    EXPECT_EQ(AlbaNumber(34), *(it2++));
    ASSERT_EQ(2u, numbersSet3.size());
    AlbaNumbersSet::const_iterator it3 = numbersSet3.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it3++));
    EXPECT_EQ(AlbaNumber(56), *(it3++));
    ASSERT_EQ(1u, numbersSet4.size());
    AlbaNumbersSet::const_iterator it4 = numbersSet4.cbegin();
    EXPECT_EQ(AlbaNumber(68), *(it4++));
    ASSERT_EQ(1u, numbersSet5.size());
    AlbaNumbersSet::const_iterator it5 = numbersSet5.cbegin();
    EXPECT_EQ(AlbaNumber(68), *(it5++));
}

TEST(TermUtilitiesTest, RetrieveNumbersForVariableWorks)
{
    AlbaNumbersSet numbersSet;

    retrieveNumbers(Constant(1.234), numbersSet);

    ASSERT_EQ(1u, numbersSet.size());
    EXPECT_EQ(AlbaNumber(1.234), *(numbersSet.cbegin()));
}

TEST(TermUtilitiesTest, RetrieveNumbersForMonomialWorks)
{
    AlbaNumbersSet numbersSet;

    retrieveNumbers(Monomial(34, {{"x", 1}, {"y", 1}}), numbersSet);

    ASSERT_EQ(2u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it++));
    EXPECT_EQ(AlbaNumber(34), *(it++));
}

TEST(TermUtilitiesTest, RetrieveNumbersForPolynomialWorks)
{
    AlbaNumbersSet numbersSet;

    retrieveNumbers(Polynomial({Monomial(1, {{"x", 56}}), Monomial(1, {{"y", 1}})}), numbersSet);

    ASSERT_EQ(2u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(1), *(it++));
    EXPECT_EQ(AlbaNumber(56), *(it++));
}

TEST(TermUtilitiesTest, RetrieveNumbersForExpressionWorks)
{
    AlbaNumbersSet numbersSet;

    retrieveNumbers(createExpressionIfPossible({Term("x"), Term("^"), Term(68)}), numbersSet);

    ASSERT_EQ(1u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(68), *(it++));
}

TEST(TermUtilitiesTest, RetrieveNumbersForFunctionWorks)
{
    AlbaNumbersSet numbersSet;
    Function functionTerm(
                "functionName",
                createExpressionIfPossible({Term("x"), Term("^"), Term(68)}),
                [](Constant const&  constant) -> Constant
    {
        return constant;
    });

    retrieveNumbers(functionTerm, numbersSet);

    ASSERT_EQ(1u, numbersSet.size());
    AlbaNumbersSet::const_iterator it = numbersSet.cbegin();
    EXPECT_EQ(AlbaNumber(68), *(it++));
}

TEST(TermUtilitiesTest, GetVariableNamesForTermWorks)
{
    VariableNamesSet variableNamesSet(getVariableNames(Term(Variable("VariableName"))));

    ASSERT_EQ(1u, variableNamesSet.size());
    EXPECT_EQ("VariableName", *(variableNamesSet.cbegin()));
}

TEST(TermUtilitiesTest, RetrieveVariableNamesForTermWorks)
{
    VariableNamesSet variableNamesSet1;
    VariableNamesSet variableNamesSet2;
    VariableNamesSet variableNamesSet3;
    VariableNamesSet variableNamesSet4;
    VariableNamesSet variableNamesSet5;
    Function functionTerm(
                "functionName",
                createExpressionIfPossible({Term("x"), Term("^"), Term("y")}),
                [](Constant const&  constant) -> Constant
    {
        return constant;
    });

    retrieveVariableNames(Term(Variable("VariableName")), variableNamesSet1);
    retrieveVariableNames(Term(Monomial(1, {{"x", 1}, {"y", 1}})), variableNamesSet2);
    retrieveVariableNames(Term(Polynomial({Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})})), variableNamesSet3);
    retrieveVariableNames(Term(createExpressionIfPossible({Term("x"), Term("^"), Term("y")})), variableNamesSet4);
    retrieveVariableNames(Term(functionTerm), variableNamesSet5);

    ASSERT_EQ(1u, variableNamesSet1.size());
    EXPECT_EQ("VariableName", *(variableNamesSet1.cbegin()));
    ASSERT_EQ(2u, variableNamesSet2.size());
    VariableNamesSet::const_iterator it2 = variableNamesSet2.cbegin();
    EXPECT_EQ("x", *(it2++));
    EXPECT_EQ("y", *(it2++));
    ASSERT_EQ(2u, variableNamesSet3.size());
    VariableNamesSet::const_iterator it3 = variableNamesSet3.cbegin();
    EXPECT_EQ("x", *(it3++));
    EXPECT_EQ("y", *(it3++));
    ASSERT_EQ(2u, variableNamesSet4.size());
    VariableNamesSet::const_iterator it4 = variableNamesSet4.cbegin();
    EXPECT_EQ("x", *(it4++));
    EXPECT_EQ("y", *(it4++));
    ASSERT_EQ(2u, variableNamesSet5.size());
    VariableNamesSet::const_iterator it5 = variableNamesSet5.cbegin();
    EXPECT_EQ("x", *(it5++));
    EXPECT_EQ("y", *(it5++));
}

TEST(TermUtilitiesTest, RetrieveVariableNamesForVariableWorks)
{
    VariableNamesSet variableNamesSet;

    retrieveVariableNames(Variable("VariableName"), variableNamesSet);

    ASSERT_EQ(1u, variableNamesSet.size());
    EXPECT_EQ("VariableName", *(variableNamesSet.cbegin()));
}

TEST(TermUtilitiesTest, RetrieveVariableNamesForMonomialWorks)
{
    VariableNamesSet variableNamesSet;

    retrieveVariableNames(Monomial(1, {{"x", 1}, {"y", 1}}), variableNamesSet);

    ASSERT_EQ(2u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(TermUtilitiesTest, RetrieveVariableNamesForPolynomialWorks)
{
    VariableNamesSet variableNamesSet;

    retrieveVariableNames(Polynomial({Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})}), variableNamesSet);

    ASSERT_EQ(2u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(TermUtilitiesTest, RetrieveVariableNamesForExpressionWorks)
{
    VariableNamesSet variableNamesSet;

    retrieveVariableNames(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}), variableNamesSet);

    ASSERT_EQ(2u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(TermUtilitiesTest, RetrieveVariableNamesForFunctionWorks)
{
    VariableNamesSet variableNamesSet;
    Function functionTerm(
                "functionName",
                createExpressionIfPossible({Term("x"), Term("^"), Term("y")}),
                [](Constant const&  constant) -> Constant
    {
        return constant;
    });

    retrieveVariableNames(functionTerm, variableNamesSet);

    ASSERT_EQ(2u, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
    EXPECT_EQ("y", *(it++));
}

TEST(TermUtilitiesTest, GetGcfMonomialInMonomialsWorks)
{
    Monomial monomialToVerify1(getGcfMonomialInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial monomialToVerify2(getGcfMonomialInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial monomialToVerify3(getGcfMonomialInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {{"x", 9}})}));
    Monomial monomialToVerify4(getGcfMonomialInMonomials({Monomial(AlbaNumber(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial monomialToVerify5(getGcfMonomialInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    Monomial monomialToVerify6(getGcfMonomialInMonomials({Monomial(6, {}), Monomial(9, {})}));
    Monomial monomialToVerify7(getGcfMonomialInMonomials({Monomial(-6, {}), Monomial(9, {})}));
    Monomial monomialToVerify8(getGcfMonomialInMonomials({Monomial(6, {}), Monomial(-9, {})}));
    Monomial monomialToVerify9(getGcfMonomialInMonomials({Monomial(1, {}), Monomial(1, {})}));
    Monomial monomialToVerify10(getGcfMonomialInMonomials({Monomial(1, {}), Monomial(-1, {})}));
    Monomial monomialToVerify11(getGcfMonomialInMonomials({Monomial(-1, {}), Monomial(1, {})}));
    Monomial monomialToVerify12(getGcfMonomialInMonomials({Monomial(-1, {}), Monomial(-11, {})}));

    Monomial monomialToExpect1(2, {{"x", 3}});
    Monomial monomialToExpect2(4, {});
    Monomial monomialToExpect3(1, {{"x", 1}});
    Monomial monomialToExpect4(AlbaNumber(1, 4), {});
    Monomial monomialToExpect5(5, {{"x", -1}});
    Monomial monomialToExpect6(3, {});
    Monomial monomialToExpect7(-3, {});
    Monomial monomialToExpect8(3, {});
    Monomial monomialToExpect9(1, {});
    Monomial monomialToExpect10(1, {});
    Monomial monomialToExpect11(1, {});
    Monomial monomialToExpect12(1, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
    EXPECT_EQ(monomialToExpect7, monomialToVerify7);
    EXPECT_EQ(monomialToExpect8, monomialToVerify8);
    EXPECT_EQ(monomialToExpect9, monomialToVerify9);
    EXPECT_EQ(monomialToExpect10, monomialToVerify10);
    EXPECT_EQ(monomialToExpect11, monomialToVerify11);
    EXPECT_EQ(monomialToExpect12, monomialToVerify12);
}

TEST(TermUtilitiesTest, GetLcmMonomialInMonomialsWorks)
{
    Monomial monomialToVerify1(getLcmMonomialInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial monomialToVerify2(getLcmMonomialInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial monomialToVerify3(getLcmMonomialInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {})}));
    Monomial monomialToVerify4(getLcmMonomialInMonomials({Monomial(AlbaNumber(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial monomialToVerify5(getLcmMonomialInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    Monomial monomialToVerify6(getLcmMonomialInMonomials({Monomial(6, {}), Monomial(9, {})}));

    Monomial monomialToExpect1(2, {{"x", 7}});
    Monomial monomialToExpect2(8, {{"x", 3}, {"y", 7}});
    Monomial monomialToExpect3(4, {{"x", 1}});
    Monomial monomialToExpect4(5, {{"x", 1}});
    Monomial monomialToExpect5(5, {{"x", 1}});
    Monomial monomialToExpect6(18, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
}

TEST(TermUtilitiesTest, CompareMonomialsAndSaveMinimumExponentsForEachVariableWorks)
{
    Monomial monomial1(85, {{"a", -5}, {"b", 10}, {"x", 3}, {"y", 4}});
    Monomial monomial2(356, {{"a", 10}, {"b", -5}, {"x", 5}, {"y", 2}});

    Monomial monomialToVerify(compareMonomialsAndSaveMinimumExponentsForEachVariable(monomial1, monomial2));

    EXPECT_DOUBLE_EQ(1, monomialToVerify.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMapToVerify(monomialToVerify.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(4u, variableMapToVerify.size());
    EXPECT_DOUBLE_EQ(-5, variableMapToVerify.at("a").getDouble());
    EXPECT_DOUBLE_EQ(-5, variableMapToVerify.at("b").getDouble());
    EXPECT_DOUBLE_EQ(3, variableMapToVerify.at("x").getDouble());
    EXPECT_DOUBLE_EQ(2, variableMapToVerify.at("y").getDouble());
}

TEST(TermUtilitiesTest, CompareMonomialsAndSaveMaximumExponentsForEachVariableWorks)
{
    Monomial monomial1(85, {{"a", -5}, {"b", 10}, {"x", 3}, {"y", 4}});
    Monomial monomial2(356, {{"a", 10}, {"b", -5}, {"x", 5}, {"y", 2}});

    Monomial monomialToVerify(compareMonomialsAndSaveMaximumExponentsForEachVariable(monomial1, monomial2));

    EXPECT_DOUBLE_EQ(1, monomialToVerify.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMapToVerify(monomialToVerify.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(4u, variableMapToVerify.size());
    EXPECT_DOUBLE_EQ(10, variableMapToVerify.at("a").getDouble());
    EXPECT_DOUBLE_EQ(10, variableMapToVerify.at("b").getDouble());
    EXPECT_DOUBLE_EQ(5, variableMapToVerify.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMapToVerify.at("y").getDouble());
}

TEST(TermUtilitiesTest, GetMonomialWithMinimumExponentsInMonomialsWorks)
{
    Monomial monomialToVerify1(getMonomialWithMinimumExponentsInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial monomialToVerify2(getMonomialWithMinimumExponentsInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial monomialToVerify3(getMonomialWithMinimumExponentsInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {{"x", 9}})}));
    Monomial monomialToVerify4(getMonomialWithMinimumExponentsInMonomials({Monomial(AlbaNumber(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial monomialToVerify5(getMonomialWithMinimumExponentsInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    Monomial monomialToVerify6(getMonomialWithMinimumExponentsInMonomials({Monomial(6, {}), Monomial(9, {})}));

    Monomial monomialToExpect1(1, {{"x", 3}});
    Monomial monomialToExpect2(1, {});
    Monomial monomialToExpect3(1, {{"x", 1}});
    Monomial monomialToExpect4(1, {});
    Monomial monomialToExpect5(1, {{"x", -1}});
    Monomial monomialToExpect6(1, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
}

TEST(TermUtilitiesTest, GetMonomialWithMaximumExponentsInMonomialsWorks)
{
    Monomial monomialToVerify1(getMonomialWithMaximumExponentsInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    Monomial monomialToVerify2(getMonomialWithMaximumExponentsInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    Monomial monomialToVerify3(getMonomialWithMaximumExponentsInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {})}));
    Monomial monomialToVerify4(getMonomialWithMaximumExponentsInMonomials({Monomial(AlbaNumber(1, 4), {{"x", 1}}), Monomial(5, {})}));
    Monomial monomialToVerify5(getMonomialWithMaximumExponentsInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    Monomial monomialToVerify6(getMonomialWithMaximumExponentsInMonomials({Monomial(6, {}), Monomial(9, {})}));

    Monomial monomialToExpect1(1, {{"x", 7}});
    Monomial monomialToExpect2(1, {{"x", 3}, {"y", 7}});
    Monomial monomialToExpect3(1, {{"x", 1}});
    Monomial monomialToExpect4(1, {{"x", 1}});
    Monomial monomialToExpect5(1, {{"x", 1}});
    Monomial monomialToExpect6(1, {});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
    EXPECT_EQ(monomialToExpect5, monomialToVerify5);
    EXPECT_EQ(monomialToExpect6, monomialToVerify6);
}

TEST(TermUtilitiesTest, GetGcfCoefficientInMonomialsWorks)
{
    EXPECT_EQ(AlbaNumber(2), getGcfCoefficientInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    EXPECT_EQ(AlbaNumber(4), getGcfCoefficientInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    EXPECT_EQ(AlbaNumber(1), getGcfCoefficientInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {{"x", 9}})}));
    EXPECT_EQ(AlbaNumber(1, 4), getGcfCoefficientInMonomials({Monomial(AlbaNumber(1, 4), {{"x", 1}}), Monomial(5, {})}));
    EXPECT_EQ(AlbaNumber(5), getGcfCoefficientInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    EXPECT_EQ(AlbaNumber(3), getGcfCoefficientInMonomials({Monomial(6, {}), Monomial(9, {})}));
}

TEST(TermUtilitiesTest, GetLcmCoefficientInMonomialsWorks)
{
    EXPECT_EQ(AlbaNumber(2), getLcmCoefficientInMonomials({Monomial(2, {{"x", 3}}), Monomial(2, {{"x", 7}})}));
    EXPECT_EQ(AlbaNumber(8), getLcmCoefficientInMonomials({Monomial(4, {{"x", 3}}), Monomial(8, {{"y", 7}})}));
    EXPECT_EQ(AlbaNumber(4), getLcmCoefficientInMonomials({Monomial(1, {{"x", 1}}), Monomial(4, {{"x", 9}})}));
    EXPECT_EQ(AlbaNumber(5), getLcmCoefficientInMonomials({Monomial(AlbaNumber(1, 4), {{"x", 1}}), Monomial(5, {})}));
    EXPECT_EQ(AlbaNumber(5), getLcmCoefficientInMonomials({Monomial(0.33, {{"x", 1}}), Monomial(5, {{"x", -1}})}));
    EXPECT_EQ(AlbaNumber(18), getLcmCoefficientInMonomials({Monomial(6, {}), Monomial(9, {})}));
}

TEST(TermUtilitiesTest, GetCommonSignInMonomialsWorks)
{
    EXPECT_EQ(AlbaNumber(1), getCommonSignInMonomials({}));
    EXPECT_EQ(AlbaNumber(1), getCommonSignInMonomials({Monomial(2, {}), Monomial(2, {}), Monomial(2, {})}));
    EXPECT_EQ(AlbaNumber(-1), getCommonSignInMonomials({Monomial(-2, {}), Monomial(-2, {}), Monomial(-2, {})}));
}

TEST(TermUtilitiesTest, TokenizeToTermsWorks)
{
    Terms termsToVerify1(tokenizeToTerms(" 5yyy + x1*y1^20.15"));

    ASSERT_EQ(7u, termsToVerify1.size());
    EXPECT_EQ(TermType::Constant, termsToVerify1.at(0).getTermType());
    EXPECT_DOUBLE_EQ(5, termsToVerify1.at(0).getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Operator, termsToVerify1.at(1).getTermType());
    EXPECT_EQ("+", termsToVerify1.at(1).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, termsToVerify1.at(2).getTermType());
    EXPECT_EQ("x1", termsToVerify1.at(2).getVariableConstReference().getVariableName());
    EXPECT_EQ(TermType::Operator, termsToVerify1.at(3).getTermType());
    EXPECT_EQ("*", termsToVerify1.at(3).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, termsToVerify1.at(4).getTermType());
    EXPECT_EQ("y1", termsToVerify1.at(4).getVariableConstReference().getVariableName());
    EXPECT_EQ(TermType::Operator, termsToVerify1.at(5).getTermType());
    EXPECT_EQ("^", termsToVerify1.at(5).getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Constant, termsToVerify1.at(6).getTermType());
    EXPECT_DOUBLE_EQ(20.15, termsToVerify1.at(6).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermUtilitiesTest, AddValueTermIfNotEmptyWorks)
{
    Terms termsToVerify1;

    addValueTermIfNotEmpty(termsToVerify1, "5");

    ASSERT_EQ(1u, termsToVerify1.size());
    EXPECT_EQ(TermType::Constant, termsToVerify1.at(0).getTermType());
    EXPECT_DOUBLE_EQ(5, termsToVerify1.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

}

}
