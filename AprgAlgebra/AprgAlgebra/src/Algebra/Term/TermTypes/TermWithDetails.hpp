#pragma once

#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Algebra/Term/TermTypes/TermAssociationType.hpp>

#include <string>
#include <vector>

namespace alba {

namespace algebra {

struct TermWithDetails {
    TermWithDetails(BaseTerm const& baseTerm, TermAssociationType const associationParameter);
    TermWithDetails(BaseTerm&& baseTerm, TermAssociationType const associationParameter);

    // rule of five or six
    ~TermWithDetails() = default;
    TermWithDetails(TermWithDetails const& termWithDetails);
    TermWithDetails& operator=(TermWithDetails const& termWithDetails);
    TermWithDetails(TermWithDetails&& termWithDetails) = default;
    TermWithDetails& operator=(TermWithDetails&& termWithDetails) = default;

    bool operator==(TermWithDetails const& second) const;
    bool operator!=(TermWithDetails const& second) const;
    bool operator<(TermWithDetails const& second) const;
    bool hasPositiveAssociation() const;
    bool hasNegativeAssociation() const;
    unsigned int getAssociationPriority() const;
    void clear();
    void reverseAssociation();
    BaseTermUniquePointer baseTermPointer;
    TermAssociationType association;
};

using TermsWithDetails = std::vector<TermWithDetails>;

}  // namespace algebra

}  // namespace alba
