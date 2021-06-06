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
    Expression(BaseTermSharedPointer const& sharedPointer);
    ~Expression();

    bool operator==(Expression const& second) const;
    bool containsOnlyOneTerm() const;

    OperatorLevel getCommonOperatorLevel() const;
    unsigned int getNumberOfTerms() const;
    BaseTermSharedPointer const& getFirstTermConstReference() const;
    TermsWithPriorityAndAssociation const& getTerms() const;
    std::string getDisplayableString() const;

    void simplify();
    void clearAndSetTerm(BaseTermSharedPointer const& sharedPointer);
    void addTerm(BaseTermSharedPointer const& sharedPointer);
    void subtractTerm(BaseTermSharedPointer const& sharedPointer);    void multiplyTerm(BaseTermSharedPointer const& sharedPointer);
    void divideTerm(BaseTermSharedPointer const& sharedPointer);
    void raiseToPowerTerm(BaseTermSharedPointer const& sharedPointer);

private:
    OperatorLevel m_commonOperatorLevel;
    TermsWithPriorityAndAssociation m_termsWithPriorityAndAssociation;};

}

}
