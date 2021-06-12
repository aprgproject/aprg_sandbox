#pragma once

#include <BaseTermData.hpp>
#include <BaseTermPointers.hpp>
#include <OperatorLevel.hpp>
#include <Polynomial.hpp>
#include <TermsWithPriorityAndAssociation.hpp>
#include <TermType.hpp>

#include <functional>
#include <string>

namespace alba
{

namespace equation
{

class Expression : public BaseTermData
{
public:
    using ConditionFunctionForTermsWithDetails = std::function<bool(TermsWithPriorityAndAssociation::TermWithDetails const&)>;
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
    TermsWithPriorityAndAssociation const& getTerms() const;
    TermsWithPriorityAndAssociation getTermsWithDetailsThatSatisfiesCondition(
            ConditionFunctionForTermsWithDetails const& conditionFunction) const;
    std::string getDisplayableString() const;
    std::string getDebugString() const;

    void clear();
    void clearAndPutTermInTermsWithAssociation(BaseTerm const& baseTerm);

    void putTermWithAddition(BaseTerm const& baseTerm);
    void putTermWithSubtraction(BaseTerm const& baseTerm);
    void putTermWithMultiplication(BaseTerm const& baseTerm);
    void putTermWithDivision(BaseTerm const& baseTerm);
    void putTermWithRaiseToPower(BaseTerm const& baseTerm);
    void putPolynomialFirstWithMultiplication(Polynomial const& polynomial);
    void putPolynomialSecondWithMultiplication(Polynomial const& polynomial);
    void putExpressionWithMultiplication(Expression const& expression);

    void reverseTheAssociationOfTheTerms();
    void set(OperatorLevel const operatorLevel, TermsWithPriorityAndAssociation const& termsWithPriorityAndAssociation);
    void setTerm(BaseTerm const& baseTerm);
    void setCommonOperatorLevel(OperatorLevel const operatorLevel);

    void simplify();
    void sort();

private:

    //simplify functions
    void simplifyAndCopyTerms(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToUpdate,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSegregate);
    void simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToUpdate,
            Expression const& expression,
            TermsWithPriorityAndAssociation::AssociationType const association);
    void simplifyFurtherIfNeeded(Expression const& beforeSimplify, Expression const& afterSimplify);

    //process functions
    void processTermsBaseOnOperatorLevel(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForAdditionAndSubtraction(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForMultiplicationAndDivision(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForRaiseToPower(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToProcess);

    //accumulate functions
    void accumulateTermsForAdditionAndSubtraction(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToCombine) const;
    void accumulateTermsForMultiplicationAndDivision(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToCombine) const;
    void accumulateTermsForRaiseToPower(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToCombine) const;

    //segregate functions
    void segregateNonExpressionsAndExpressions(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsWithNonExpressions,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsWithExpressions,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSegregate) const;
    void segregateNumeratorAndDenominatorForMultiplicationAndDivision(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsForNumerator,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsForDenominator,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSegregate) const;

    //put functions
    void putTermsWithDetails(TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSave);
    void putTermWithAdditionForNonEmptyTerms(BaseTerm const& baseTerm);
    void putTermWithSubtractionForNonEmptyTerms(BaseTerm const& baseTerm);
    void putTermWithMultiplicationForNonEmptyTerms(BaseTerm const& baseTerm);
    void putTermWithDivisionForNonEmptyTerms(BaseTerm const& baseTerm);
    void putTermWithRaiseToPowerForNonEmptyTerms(BaseTerm const& baseTerm);
    void putTermForExpressionAndNonExpressions(
            BaseTerm const& baseTerm,
            TermsWithPriorityAndAssociation::AssociationType const overallAssociation);
    void putTerm(
            BaseTerm const& baseTerm,
            TermsWithPriorityAndAssociation::AssociationType const overallAssociation);
    void putTermsWithAssociation(
            TermsWithPriorityAndAssociation const& termsWithAssociation,
            TermsWithPriorityAndAssociation::AssociationType const overallAssociation);

    //functions for addition
    void accumulateTermsForAdditionAndSubtractionForTermsWithExpressions(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsWithExpressions) const;
    bool mergeForAdditionAndSubtractionAndReturnIfMerged(
            TermsWithPriorityAndAssociation::TermWithDetails & termExpressionWithDetails1,
            TermsWithPriorityAndAssociation::TermWithDetails & termExpressionWithDetails2) const;
    void retrieveUniqueExpressionsAndMergeTerms(
            Expression & uniqueExpression1,
            Expression & uniqueExpression2,
            BaseTerm & mergeTerm1,
            BaseTerm & mergeTerm2,
            TermsWithPriorityAndAssociation::TermWithDetails const& termExpressionWithDetails1,
            TermsWithPriorityAndAssociation::TermWithDetails const& termExpressionWithDetails2) const;
    Expression getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression) const;
    void accumulateMergeTermForAdditionOrSubtractionMergeChecking(BaseTerm & combinedBaseTerm, Expression const& expression) const;
    bool canBeMergedForAdditionAndSubtraction(
            Expression const& uniqueExpression1,
            Expression const& uniqueExpression2,
            BaseTerm const& mergeTerm1,
            BaseTerm const& mergeTerm2) const;

    //functions for multiplication
    void processNonExpressionsForMultiplicationAndDivision(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& nonExpressionsForNumerator,
            TermsWithPriorityAndAssociation::TermsWithDetails const& nonExpressionsForDenominator) const;
    void processExpressionForMultiplicationAndDivision(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& expressionsForNumerator,
            TermsWithPriorityAndAssociation::TermsWithDetails const& expressionsForDenominator) const;
    void removeSameTermsInNumeratorAndDenominatorForMultiplicationAndDivision(
            TermsWithPriorityAndAssociation::TermsWithDetails & expressionsForNumerator,
            TermsWithPriorityAndAssociation::TermsWithDetails & expressionsForDenominator) const;
    void multiplyThenAddTermIfTrueAndSubtractIfFalse(
            Expression const& multiplicand,
            BaseTerm const& multiplier,
            bool const isAdd);
    OperatorLevel m_commonOperatorLevel;
    TermsWithPriorityAndAssociation m_termsWithPriorityAndAssociation;
};

}

}
