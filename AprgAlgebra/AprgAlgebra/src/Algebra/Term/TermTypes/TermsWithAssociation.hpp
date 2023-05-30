#pragma once

#include <Algebra/Term/TermTypes/TermWithDetails.hpp>

namespace alba {

namespace algebra {

class TermsWithAssociation {
public:
    friend class Expression;

    TermsWithAssociation() = default;
    TermsWithAssociation(TermsWithDetails const& termsWithDetails);
    TermsWithAssociation(std::initializer_list<TermWithDetails> const& termsWithDetails);

    // rule of zero

    bool operator==(TermsWithAssociation const& second) const;
    bool operator!=(TermsWithAssociation const& second) const;
    bool operator<(TermsWithAssociation const& second) const;
    bool isEmpty() const;

    int getSize() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermAssociationType getFirstAssociationType() const;
    TermsWithDetails const& getTermsWithDetails() const;
    TermsWithDetails& getTermsWithDetailsReference();

    void clear();
    void sort(bool const dontSortFirstItem);
    void putTermWithDetails(TermWithDetails const& termWithDetails);
    void putTermsWithDetails(std::initializer_list<TermWithDetails> const& termsWithDetails);
    void putTermsWithDetails(TermsWithDetails const& termsWithDetails);
    void putTermWithAssociation(BaseTerm const& baseTerm, TermAssociationType const associationType);
    void putTermWithPositiveAssociation(BaseTerm const& baseTerm);
    void putTermWithNegativeAssociation(BaseTerm const& baseTerm);
    void reverseTheAssociationOfTheTerms();

private:
    TermsWithDetails m_termsWithDetails;
};

}  // namespace algebra

}  // namespace alba
