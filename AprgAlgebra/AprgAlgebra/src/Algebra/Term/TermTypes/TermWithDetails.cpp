#include "TermWithDetails.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>

using namespace std;

namespace alba {

namespace algebra {

TermWithDetails::TermWithDetails(BaseTerm const& baseTerm, TermAssociationType const associationParameter)
    : baseTermPointer(createBasePointer(baseTerm)), association(associationParameter) {}

TermWithDetails::TermWithDetails(BaseTerm&& baseTerm, TermAssociationType const associationParameter)
    : baseTermPointer(createBasePointer(baseTerm)), association(associationParameter) {}

TermWithDetails::TermWithDetails(TermWithDetails const& termWithDetails)
    : baseTermPointer(duplicateUniquePointer(termWithDetails.baseTermPointer)),
      association(termWithDetails.association) {}

TermWithDetails& TermWithDetails::operator=(TermWithDetails const& termWithDetails) {
    baseTermPointer = duplicateUniquePointer(termWithDetails.baseTermPointer);
    association = termWithDetails.association;
    return *this;
}

bool TermWithDetails::operator==(TermWithDetails const& second) const {
    Term const& term1(getTermConstReferenceFromUniquePointer(baseTermPointer));
    Term const& term2(getTermConstReferenceFromUniquePointer(second.baseTermPointer));
    return term1 == term2 && association == second.association;
}

bool TermWithDetails::operator!=(TermWithDetails const& second) const { return !(operator==(second)); }

bool TermWithDetails::operator<(TermWithDetails const& second) const {
    bool result(false);
    if (association == second.association) {
        Term const& term1(getTermConstReferenceFromUniquePointer(baseTermPointer));
        Term const& term2(getTermConstReferenceFromUniquePointer(second.baseTermPointer));
        result = term1 < term2;
    } else {
        result = getAssociationPriority() < second.getAssociationPriority();
    }
    return result;
}

bool TermWithDetails::hasPositiveAssociation() const { return TermAssociationType::Positive == association; }

bool TermWithDetails::hasNegativeAssociation() const { return TermAssociationType::Negative == association; }
int TermWithDetails::getAssociationPriority() const { return algebra::getAssociationPriority(association); }

void TermWithDetails::clear() {
    baseTermPointer.reset();    association = TermAssociationType::Positive;
}

void TermWithDetails::reverseAssociation() { association = getReversedAssociationType(association); }
}  // namespace algebra

}  // namespace alba
