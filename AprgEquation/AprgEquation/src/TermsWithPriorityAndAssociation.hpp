#pragma once

#include <BaseTermPointers.hpp>

#include <functional>
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
        TermWithDetails(BaseTermSharedPointer const& baseTermSharedPointerParameter, AssociationType const associationParameter);
        TermWithDetails(TermWithDetails const& termWithDetails);
        bool operator==(TermWithDetails const& second) const;
        bool hasPositiveAssociation() const;
        bool hasNegativeAssociation() const;
        unsigned int getAssociationPriority() const;
        BaseTermSharedPointer baseTermSharedPointer;
        AssociationType association;
    };
    using TermsWithDetails=std::vector<TermWithDetails>;
    using TermsWithDetailsFunction = std::function<void(TermWithDetails const&)>;

    TermsWithPriorityAndAssociation();
    ~TermsWithPriorityAndAssociation();

    bool operator==(TermsWithPriorityAndAssociation const& second) const;

    unsigned int getSize() const;
    BaseTermSharedPointer const& getFirstTermConstReference() const;
    TermsWithDetails const& getTermsWithDetails() const;

    void clear();
    void putTermWithDetails(TermWithDetails const& termWithDetails);
    void putTermWithPositiveAssociation(BaseTermSharedPointer const& baseTermSharedPointer);
    void putTermWithNegativeAssociation(BaseTermSharedPointer const& baseTermSharedPointer);
    void reverseTheAssociationOfTheTerms();

private:
    TermsWithDetails m_termsWithDetails;};

}

}
