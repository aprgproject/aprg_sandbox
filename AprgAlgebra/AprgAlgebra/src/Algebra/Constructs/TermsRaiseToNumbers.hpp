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

    unsigned int getSize() const;
    BaseToExponentMap const& getBaseToExponentMap() const;
    AlbaNumber getExponentOfBase(Term const& base) const;
    Terms getTermsInMultiplicationOperation() const;
    TermsWithDetails getTermWithDetailsInMultiplicationAndDivisionOperation() const;

    void addExponents(TermsRaiseToNumbers const& termsRaiseToNumbers);
    void addTerm(Term const& term, TermAssociationType const association);
    void addTerms(Terms const& terms, TermAssociationType const association);
    void subtractExponents(TermsRaiseToNumbers const& termsRaiseToNumbers);
    void multiplyNumberToExponents(AlbaNumber const& number);

    void setBaseAndExponent(Term const& base, AlbaNumber const& exponent);
    void removeItemWithBase(Term const& base);

    void simplify();

private:

    void removeItemsWithExponentsZero();
    Term convertToTerm(Term const& base, AlbaNumber const& exponent) const;

    BaseToExponentMap m_baseToExponentMap;
};

}

}
