#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <map>

namespace alba {

namespace algebra {

template <typename ExponentType, typename BaseRaiseToExponentType>
class TermsRaiseToExponents {
public:
    using BaseToExponentMap = std::map<Term, ExponentType>;
    using BaseExponentPair = std::pair<Term, ExponentType>;

    TermsRaiseToExponents();
    TermsRaiseToExponents(BaseToExponentMap const& baseToExponentMap);

    BaseToExponentMap const& getBaseToExponentMap() const;
    ExponentType getExponentOfBase(Term const& base) const;
    Terms getTermsInMultiplicationOperation() const;
    TermsWithDetails getTermWithDetailsInMultiplicationAndDivisionOperation() const;
    Term getCombinedTerm() const;

    void addExponents(TermsRaiseToExponents const& termsRaiseToNumbers);
    void subtractExponents(TermsRaiseToExponents const& termsRaiseToNumbers);
    void multiplyToExponents(ExponentType const& exponent);
    void putTerm(Term const& term, TermAssociationType const association);
    void putTerms(Terms const& terms, TermAssociationType const association);

    void setBaseAndExponent(Term const& base, ExponentType const& exponent);
    void removeItemWithBase(Term const& base);

    void clear();
    void simplify();

protected:
    void removeItemsWithExponentsZero();
    Term convertToTerm(Term const& base, ExponentType const& exponent) const;
    void putTermUsingBaseToExponentType(Term const& term, int const sign);
    bool isNegative(ExponentType const& exponent) const;

    BaseToExponentMap m_baseToExponentMap;
};

}  // namespace algebra

}  // namespace alba
