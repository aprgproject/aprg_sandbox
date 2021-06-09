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
    bool canBeMergedForAdditionAndSubtraction() const;

    OperatorLevel getCommonOperatorLevel() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermsWithPriorityAndAssociation const& getTerms() const;
    TermsWithPriorityAndAssociation getTermsWithDetailsThatSatisfiesCondition(
            ConditionFunctionForTermsWithDetails const& conditionFunction) const;
    std::string getDisplayableString() const;
    std::string getDebugString() const;

    void simplify();
    void sort();

    void addTerm(BaseTerm const& baseTerm);
    void subtractTerm(BaseTerm const& baseTerm);
    void multiplyTerm(BaseTerm const& baseTerm);
    void divideTerm(BaseTerm const& baseTerm);
    void raiseToPowerTerm(BaseTerm const& baseTerm);
    void multiplyPolynomialFirst(Polynomial const& polynomial);
    void multiplyPolynomialSecond(Polynomial const& polynomial);
    void multiplyExpression(Expression const& expression);

    void set(OperatorLevel const operatorLevel, TermsWithPriorityAndAssociation termsWithPriorityAndAssociation);
    void setTerm(BaseTerm const& baseTerm);
    void setCommonOperatorLevel(OperatorLevel const operatorLevel);
    void reverseTheAssociationOfTheTerms();
    void clear();
    void clearAndPutTermInTermsWithAssociation(BaseTerm const& baseTerm);

private:
    void simplifyFurtherIfNeeded(Expression const& beforeSimplify, Expression const& afterSimplify);
    void simplifyAndCopyTerms(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToUpdate,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSegregate);
    void simplifyAndCopyTermsFromAnExpression(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToUpdate,
            Expression const& expression,
            TermsWithPriorityAndAssociation::AssociationType const association);
    void processTermsBaseOnOperatorLevel(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForAdditionAndSubtraction(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForMultiplicationAndDivision(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToProcess);
    void processAndSaveTermsForRaiseToPower(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToProcess);
    void segregateNonExpressionsAndExpressions(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsWithNonExpressions,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsWithExpressions,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSegregate);
    void segregateNumeratorAndDenominatorForMultiplicationAndDivision(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsForNumerator,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsForDenominator,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSegregate);
    void accumulateTermsForAdditionAndSubtraction(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToCombine);
    void accumulateTermsForMultiplicationAndDivision(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToCombine);
    void accumulateTermsForRaiseToPower(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToCombine);
    void putCombinedTerm(BaseTerm const& combinedBaseTerm);
    void putTermsWithDetails(TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSave);
    void addTermForNonEmptyTerms(BaseTerm const& baseTerm);
    void subtractTermForNonEmptyTerms(BaseTerm const& baseTerm);
    void multiplyTermForNonEmptyTerms(BaseTerm const& baseTerm);
    void divideTermForNonEmptyTerms(BaseTerm const& baseTerm);
    void raiseToPowerTermForNonEmptyTerms(BaseTerm const& baseTerm);
    void putTermForExpressionAndNonExpressions(
            BaseTerm const& baseTerm,
            TermsWithPriorityAndAssociation::AssociationType const overallAssociation);
    void putTerm(
            BaseTerm const& baseTerm,
            TermsWithPriorityAndAssociation::AssociationType const overallAssociation);
    void putTermsWithAssociation(
            TermsWithPriorityAndAssociation const& termsWithAssociation,
            TermsWithPriorityAndAssociation::AssociationType const overallAssociation);
    void accumulateTermsForAdditionAndSubtractionForTermsWithExpressions(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsWithExpressions);
    bool mergeForAdditionAndSubtractionAndReturnIfMerged(
            TermsWithPriorityAndAssociation::TermWithDetails & termExpressionWithDetails1,
            TermsWithPriorityAndAssociation::TermWithDetails & termExpressionWithDetails2);
    bool canBeMergedForAdditionAndSubtraction(
            Expression const& uniqueExpression1,
            Expression const& uniqueExpression2,
            BaseTerm const& mergeTerm1,
            BaseTerm const& mergeTerm2) const;
    Expression getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression);
    void accumulateMergeTermForAdditionOrSubtractionMergeChecking(BaseTerm & combinedBaseTerm, Expression const& expression);
    void removeSameTermsInNumeratorAndDenominatorForMultiplicationAndDivision(
            TermsWithPriorityAndAssociation::TermsWithDetails & expressionsForNumerator,
            TermsWithPriorityAndAssociation::TermsWithDetails & expressionsForDenominator);
    void multiplyThenAddTermIfTrueAndSubtractIfFalse(
            Expression const& multiplicand,
            BaseTerm const& term,
            bool const isAdd);
    OperatorLevel m_commonOperatorLevel;
    TermsWithPriorityAndAssociation m_termsWithPriorityAndAssociation;
};

}

}
