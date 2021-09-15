#pragma once

#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Algebra/Term/TermTypes/TermAssociationType.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace algebra
{

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
    std::string getDisplayableString() const;
    void clear();
    BaseTermSharedPointer baseTermSharedPointer;
    TermAssociationType association;
};

using TermsWithDetails=std::vector<TermWithDetails>;

std::ostream & operator<<(std::ostream & out, TermWithDetails const& termWithDetails);

}

}
