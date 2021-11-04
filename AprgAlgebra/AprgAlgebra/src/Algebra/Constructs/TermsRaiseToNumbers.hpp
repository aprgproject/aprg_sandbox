#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <functional>
#include <map>

namespace alba
{

namespace algebra
{

class TermsRaiseToNumbers
{
public:
    using BaseToExponentMap = std::map<Term, AlbaNumber>;
    using BaseExponentPair = std::pair<Term, AlbaNumber>;

    TermsRaiseToNumbers();
    TermsRaiseToNumbers(BaseToExponentMap const& baseToExponentMap);

    BaseToExponentMap const& getBaseToExponentMap() const;
    AlbaNumber getExponentOfBase(Term const& base) const;
    Terms getTermsInMultiplicationOperation() const;
    TermsWithDetails getTermWithDetailsInMultiplicationAndDivisionOperation() const;
    Term getCombinedTerm() const;

    void addExponents(TermsRaiseToNumbers const& termsRaiseToNumbers);
    void subtractExponents(TermsRaiseToNumbers const& termsRaiseToNumbers);
    void multiplyToExponents(AlbaNumber const& number);
    void putTerm(Term const& term, TermAssociationType const association);
    void putTerms(Terms const& terms, TermAssociationType const association);

    void setBaseAndExponent(Term const& base, AlbaNumber const& exponent);
    void removeItemWithBase(Term const& base);

    void clear();
    void simplify();

private:

    void removeItemsWithExponentsZero();
    Term convertToTerm(Term const& base, AlbaNumber const& exponent) const;

    BaseToExponentMap m_baseToExponentMap;
};

}

}
