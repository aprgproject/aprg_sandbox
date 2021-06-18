#pragma once

#include <BaseTermData.hpp>
#include <BaseTermPointers.hpp>
#include <OperatorLevel.hpp>
#include <Polynomial.hpp>
#include <TermsWithAssociation.hpp>
#include <TermType.hpp>
#include <VariablesToValuesTypes.hpp>

#include <functional>
#include <string>

namespace alba
{

namespace equation
{

class Expression : public BaseTermData
{
public:
    using ConditionFunctionForTermsWithDetails = std::function<bool(TermsWithAssociation::TermWithDetails const&)>;
    Expression();
    Expression(BaseTerm const& baseTerm);
    ~Expression();

    bool operator==(Expression const& second) const;
    bool operator!=(Expression const& second) const;
    bool operator<(Expression const& second) const;
    bool isEmpty() const;
    bool containsOnlyOneTerm() const;

    OperatorLevel getCommonOperatorLevel() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermsWithAssociation const& getTerms() const;
    TermsWithAssociation getTermsWithDetailsThatSatisfiesCondition(
            ConditionFunctionForTermsWithDetails const& conditionFunction) const;
    std::string getDisplayableString() const;
    std::string getDebugString() const;

    void clear();
    void clearAndPutTermInTermsWithAssociation(BaseTerm const& baseTerm);

    void putTermWithAdditionIfNeeded(BaseTerm const& baseTerm);
    void putTermWithSubtractionIfNeeded(BaseTerm const& baseTerm);
    void putTermWithMultiplicationIfNeeded(BaseTerm const& baseTerm);
    void putTermWithDivisionIfNeeded(BaseTerm const& baseTerm);
    void putTermWithRaiseToPowerIfNeeded(BaseTerm const& baseTerm);
    void putPolynomialFirstWithMultiplication(Polynomial const& polynomial);
    void putPolynomialSecondWithMultiplication(Polynomial const& polynomial);
    void putExpressionWithMultiplication(Expression const& expression);

    void reverseTheAssociationOfTheTerms();
    void set(OperatorLevel const operatorLevel, TermsWithAssociation const& termsWithPriorityAndAssociation);
    void setTerm(BaseTerm const& baseTerm);
    void setCommonOperatorLevel(OperatorLevel const operatorLevel);

    void simplify();
    void simplifyToCommonDenominators();
    void sort();
    void substituteVariablesToValues(VariablesToValuesMap const& variableValueMap);

private:

    //simplify functions
    void simplifyAndCopyTerms(
            TermsWithAssociation::TermsWithDetails & termsToUpdate,
            TermsWithAssociation::TermsWithDetails const& termsToCheck);
    void simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(
            TermsWithAssociation::TermsWithDetails & termsToUpdate,
            Expression const& expression,
            TermAssociationType const association);
    void simplifyFurtherIfNeeded(Expression const& beforeSimplify, Expression const& afterSimplify);

    //process functions
    void processTermsBaseOnOperatorLevel(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForAdditionAndSubtraction(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForMultiplicationAndDivision(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForRaiseToPower(
            TermsWithAssociation::TermsWithDetails const& termsToProcess);

    //put functions
    void putTermsWithDetails(TermsWithAssociation::TermsWithDetails const& termsToSave);
    void putTermWithAddition(BaseTerm const& baseTerm);
    void putTermWithSubtraction(BaseTerm const& baseTerm);
    void putTermWithMultiplication(BaseTerm const& baseTerm);
    void putTermWithDivision(BaseTerm const& baseTerm);
    void putTermWithRaiseToPower(BaseTerm const& baseTerm);
    void putTermForExpressionAndNonExpressions(
            BaseTerm const& baseTerm,
            TermAssociationType const overallAssociation);
    void putTerm(
            BaseTerm const& baseTerm,
            TermAssociationType const overallAssociation);
    void putTermsWithAssociation(
            TermsWithAssociation const& termsWithAssociation,
            TermAssociationType const overallAssociation);

    //functions for addition
    void addOrSubtractTermsWithExpressions(
            BaseTerm & combinedBaseTerm,
            TermsWithAssociation::TermsWithDetails const& termsWithExpressions) const;

    //functions for multiplication
    void processNonExpressionsForMultiplicationAndDivision(
            BaseTerm & combinedBaseTerm,
            TermsWithAssociation::TermsWithDetails const& nonExpressionsForNumerator,
            TermsWithAssociation::TermsWithDetails const& nonExpressionsForDenominator) const;
    void processExpressionForMultiplicationAndDivision(
            BaseTerm & combinedBaseTerm,
            TermsWithAssociation::TermsWithDetails const& expressionsForNumerator,
            TermsWithAssociation::TermsWithDetails const& expressionsForDenominator) const;

    void multiplyThenPutTermAsAddIfTrueAndAsSubtractIfFalse(
            Expression const& multiplicand,
            BaseTerm const& multiplier,
            bool const isAdd);
    OperatorLevel m_commonOperatorLevel;
    TermsWithAssociation m_termsWithPriorityAndAssociation;
};

}

}
