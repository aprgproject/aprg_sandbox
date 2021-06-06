#pragma once

#include <BaseTermData.hpp>
#include <BaseTermPointers.hpp>
#include <OperatorLevel.hpp>
#include <TermsWithPriorityAndAssociation.hpp>
#include <TermType.hpp>

#include <string>

namespace alba
{

namespace equation
{

class Expression : public BaseTermData
{
public:
    Expression();
    Expression(BaseTerm const& baseTerm);
    ~Expression();

    bool operator==(Expression const& second) const;
    bool isEmpty() const;
    bool containsOnlyOneTerm() const;

    OperatorLevel getCommonOperatorLevel() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermsWithPriorityAndAssociation const& getTerms() const;
    std::string getDisplayableString() const;

    void simplify();
    void clearAndSetTerm(BaseTerm const& baseTerm);
    void addTerm(BaseTerm const& baseTerm);
    void subtractTerm(BaseTerm const& baseTerm);
    void multiplyTerm(BaseTerm const& baseTerm);
    void divideTerm(BaseTerm const& baseTerm);
    void raiseToPowerTerm(BaseTerm const& baseTerm);
    void setCommonOperatorLevel(OperatorLevel const operatorLevel);
    void reverseTheAssociationOfTheTerms();

private:
    void putTermForExpressionAndNonExpressions(
            BaseTerm const& baseTerm,
            TermsWithPriorityAndAssociation::AssociationType const overallAssociation);
    void putTerm(BaseTerm const& baseTerm,
                 TermsWithPriorityAndAssociation::AssociationType const overallAssociation);
    void putTermsWithAssociation(
            TermsWithPriorityAndAssociation const& termsWithAssociation,
            TermsWithPriorityAndAssociation::AssociationType const overallAssociation);
    void simplifyAndCopyTerms(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToUpdate,
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSegregate);
    void simplifyAndCopyTermsFromAnExpression(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToUpdate,
            Expression const& expression,
            TermsWithPriorityAndAssociation::AssociationType const association);
    void combineTermAndSave(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine);
    void combineTermAndSaveBaseOnOperatorLevel(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine);
    void processAndSaveTermsForAdditionAndSubtraction(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine);
    void sortTermsForAdditionAndSubtraction(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine);
    void accumulateTermsForAdditionAndSubtraction(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine);
    void accumulateTermsForMultiplicationAndDivision(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine);
    void accumulateTermsForRaiseToPower(
            BaseTerm & combinedBaseTerm,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine);
    void saveCombinedTerm(BaseTerm const& combinedBaseTerm);
    void saveTerms(TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSave);

    OperatorLevel m_commonOperatorLevel;    TermsWithPriorityAndAssociation m_termsWithPriorityAndAssociation;
};

}

}
