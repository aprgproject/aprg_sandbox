#pragma once

#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Algebra/Term/TermTypes/TermAssociationType.hpp>

#include <functional>
#include <list>
#include <vector>

namespace alba
{

namespace algebra
{

class TermsWithAssociation
{
public:
    friend class Expression;
    struct TermWithDetails
    {
        TermWithDetails(BaseTerm const& baseTerm, TermAssociationType const associationParameter);
        TermWithDetails(TermWithDetails const& termWithDetails);
        bool operator==(TermWithDetails const& second) const;
        bool operator!=(TermWithDetails const& second) const;
        bool operator<(TermWithDetails const& second) const;
        bool hasPositiveAssociation() const;
        bool hasNegativeAssociation() const;
        unsigned int getAssociationPriority() const;
        void clear();
        BaseTermSharedPointer baseTermSharedPointer;
        TermAssociationType association;
    };
    using TermsWithDetails=std::vector<TermWithDetails>;

    TermsWithAssociation();
    ~TermsWithAssociation();

    bool operator==(TermsWithAssociation const& second) const;
    bool operator!=(TermsWithAssociation const& second) const;
    bool operator<(TermsWithAssociation const& second) const;
    bool isEmpty() const;

    unsigned int getSize() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermsWithDetails const& getTermsWithDetails() const;
    TermsWithDetails & getTermsWithDetailsReference();

    void clear();
    void sort();
    void putTermWithDetails(TermWithDetails const& termWithDetails);
    void putTermWithPositiveAssociation(BaseTerm const& baseTerm);
    void putTermWithNegativeAssociation(BaseTerm const& baseTerm);
    void reverseTheAssociationOfTheTerms();

private:
    TermsWithDetails m_termsWithDetails;
};

}

}
