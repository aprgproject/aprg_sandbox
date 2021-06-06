#pragma once

#include <BaseTermPointers.hpp>

#include <functional>
#include <list>
#include <vector>

namespace alba
{

namespace equation
{

class TermsWithPriorityAndAssociation
{
public:
    enum class AssociationType
    {
        Positive,
        Negative
    };
    struct TermWithDetails
    {
        TermWithDetails(BaseTerm const& baseTerm, AssociationType const associationParameter);
        TermWithDetails(TermWithDetails const& termWithDetails);
        bool operator==(TermWithDetails const& second) const;
        bool operator!=(TermWithDetails const& second) const;
        bool operator<(TermWithDetails const& second) const;
        bool hasPositiveAssociation() const;
        bool hasNegativeAssociation() const;
        unsigned int getAssociationPriority() const;
        void clear();
        BaseTermSharedPointer baseTermSharedPointer;
        AssociationType association;
    };
    using TermsWithDetails=std::vector<TermWithDetails>;
    using ListOfTermsWithDetails=std::list<TermWithDetails>;
    using TermsWithDetailsFunction = std::function<void(TermWithDetails const&)>;

    TermsWithPriorityAndAssociation();
    ~TermsWithPriorityAndAssociation();

    bool operator==(TermsWithPriorityAndAssociation const& second) const;
    bool operator!=(TermsWithPriorityAndAssociation const& second) const;
    bool operator<(TermsWithPriorityAndAssociation const& second) const;
    bool isEmpty() const;

    unsigned int getSize() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermsWithDetails const& getTermsWithDetails() const;

    void clear();
    void putTermWithDetails(TermWithDetails const& termWithDetails);
    void putTermWithPositiveAssociation(BaseTerm const& baseTerm);
    void putTermWithNegativeAssociation(BaseTerm const& baseTerm);
    void reverseTheAssociationOfTheTerms();

private:
    TermsWithDetails m_termsWithDetails;
};

}

}
