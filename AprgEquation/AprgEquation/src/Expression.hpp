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

    OperatorLevel getCommonOperatorLevel() const;    BaseTerm const& getFirstTermConstReference() const;
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
    void segregateTerms(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsNotToCombine,            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToSegregate);
    void segregateTermsInExpression(
            TermsWithPriorityAndAssociation::TermsWithDetails & termsToCombine,
            TermsWithPriorityAndAssociation::TermsWithDetails & termsNotToCombine,
            Expression const& expression,
            TermsWithPriorityAndAssociation::AssociationType const association);
    void processTermsToCombine(
            TermsWithPriorityAndAssociation::TermsWithDetails const& termsToCombine);
    void processTermsNotToCombine(TermsWithPriorityAndAssociation::TermsWithDetails const& termsNotToCombine);
    void combineTerms(BaseTerm & combinedTerm, TermsWithPriorityAndAssociation::TermsWithDetails const& termsToCombine);
    OperatorLevel m_commonOperatorLevel;
    TermsWithPriorityAndAssociation m_termsWithPriorityAndAssociation;
};

}

}
